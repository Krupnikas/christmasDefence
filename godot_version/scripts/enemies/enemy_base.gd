extends Node2D
class_name EnemyBase
## Base class for all enemy types

signal died(bounty: int)
signal reached_exit

# Enemy identity
@export var enemy_name: String = "Enemy"
@export var bounty: int = 10

# Stats
@export var max_hp: float = 100.0
@export var speed: float = 100.0
@export var physical_resist: float = 0.0
@export var dodge_chance: float = 0.0
@export var status_immune: bool = false
@export var is_flying: bool = false

# Combat
@export var attack_damage: float = 10.0
@export var attack_range: float = 32.0
@export var attack_speed: float = 1.0

# Runtime state
var current_hp: float
var is_dead: bool = false
var path: Array[Vector2] = []
var path_index: int = 0
var current_speed_multiplier: float = 1.0

# Status effects
var is_burning: bool = false
var burn_timer: float = 0.0
var burn_dps: float = 0.0

var is_slowed: bool = false
var slow_timer: float = 0.0
var slow_amount: float = 0.0

# Attack
var attack_cooldown: float = 0.0
var current_target_cannon: Node2D = null

# Visual components
@onready var sprite: Sprite2D = $Sprite2D
@onready var hp_bar: ProgressBar = $HPBar
@onready var status_indicator: Node2D = $StatusIndicator


func _ready() -> void:
	add_to_group("enemies")
	current_hp = max_hp
	_update_hp_bar()


func _process(delta: float) -> void:
	if is_dead:
		return

	_process_status_effects(delta)
	_move(delta)
	_process_attack(delta)


func _move(delta: float) -> void:
	if path.is_empty() or path_index >= path.size():
		return

	var target_pos = path[path_index]
	var direction = (target_pos - global_position).normalized()
	var move_speed = speed * current_speed_multiplier * delta

	# Apply flying wave motion
	var offset = Vector2.ZERO
	if is_flying:
		offset.y = sin(Time.get_ticks_msec() * 0.005) * 5.0

	global_position += direction * move_speed + offset * delta

	# Rotate sprite to face movement direction
	if direction.length() > 0.1:
		sprite.rotation = direction.angle() + PI/2

	# Check if reached current waypoint
	if global_position.distance_to(target_pos) < 5.0:
		path_index += 1
		if path_index >= path.size():
			_on_reached_exit()


func _process_status_effects(delta: float) -> void:
	if status_immune:
		is_burning = false
		is_slowed = false
		return

	# Burn effect
	if is_burning:
		burn_timer -= delta
		take_damage(burn_dps * delta, null, true)

		if burn_timer <= 0:
			is_burning = false
			burn_dps = 0.0
			_update_status_visuals()

	# Slow effect
	if is_slowed:
		slow_timer -= delta
		current_speed_multiplier = 1.0 - slow_amount

		if slow_timer <= 0:
			is_slowed = false
			slow_amount = 0.0
			current_speed_multiplier = 1.0
			_update_status_visuals()
	else:
		current_speed_multiplier = 1.0


func _process_attack(delta: float) -> void:
	if not Settings.enable_enemy_attacks:
		return

	attack_cooldown = max(0, attack_cooldown - delta)

	if attack_cooldown > 0:
		return

	# Find cannon to attack
	_find_attack_target()

	if current_target_cannon and is_instance_valid(current_target_cannon):
		_attack_cannon()


func _find_attack_target() -> void:
	var cannons = get_tree().get_nodes_in_group("cannons")
	var closest_dist = attack_range
	current_target_cannon = null

	for cannon in cannons:
		if not is_instance_valid(cannon):
			continue

		var dist = global_position.distance_to(cannon.global_position)
		if dist < closest_dist:
			closest_dist = dist
			current_target_cannon = cannon


func _attack_cannon() -> void:
	if current_target_cannon.has_method("take_damage"):
		current_target_cannon.take_damage(attack_damage)

	attack_cooldown = 1.0 / attack_speed


func take_damage(amount: float, source: Node2D = null, is_dot: bool = false) -> void:
	if is_dead:
		return

	# Dodge check (not for DoT)
	if not is_dot and randf() < dodge_chance:
		_show_feedback("DODGE!")
		return

	# Physical resistance
	if source and source is CannonBase:
		var cannon = source as CannonBase
		if cannon.cannon_type in [GameManager.CannonType.GUN, GameManager.CannonType.SNIPER,
								   GameManager.CannonType.RAPID, GameManager.CannonType.ACID]:
			amount *= (1.0 - physical_resist)

	current_hp -= amount
	_update_hp_bar()

	if not is_dot:
		AudioManager.play_enemy_hit()

	if current_hp <= 0:
		_on_death()


func apply_burn(duration: float, dps: float) -> void:
	if status_immune:
		return

	# Fire + Ice interaction
	if is_slowed:
		is_slowed = false
		slow_timer = 0.0
		slow_amount = 0.0
		current_speed_multiplier = 1.0
		_show_feedback("THAW!")
		_update_status_visuals()
		return

	is_burning = true
	burn_timer = max(burn_timer, duration)
	burn_dps = max(burn_dps, dps)
	_update_status_visuals()


func apply_slow(duration: float, amount: float) -> void:
	if status_immune:
		return

	# Ice + Fire interaction
	if is_burning:
		is_burning = false
		burn_timer = 0.0
		burn_dps = 0.0
		_show_feedback("DOUSED!")
		_update_status_visuals()
		return

	is_slowed = true
	slow_timer = max(slow_timer, duration)
	slow_amount = max(slow_amount, amount)
	_update_status_visuals()


func _update_status_visuals() -> void:
	if not status_indicator:
		return

	# Update visual indicators based on status
	if is_burning:
		modulate = Color(1.0, 0.7, 0.5)  # Orange tint
	elif is_slowed:
		modulate = Color(0.7, 0.9, 1.0)  # Blue tint
	else:
		modulate = Color.WHITE


func _update_hp_bar() -> void:
	if hp_bar:
		hp_bar.value = (current_hp / max_hp) * 100
		hp_bar.visible = current_hp < max_hp

		# Color based on HP
		var hp_percent = current_hp / max_hp
		if hp_percent > 0.6:
			hp_bar.modulate = Color.GREEN
		elif hp_percent > 0.3:
			hp_bar.modulate = Color.YELLOW
		else:
			hp_bar.modulate = Color.RED


func _show_feedback(text: String) -> void:
	var label = Label.new()
	label.text = text
	label.add_theme_color_override("font_color", Color.WHITE)
	label.position = Vector2(-20, -50)
	add_child(label)

	var tween = create_tween()
	tween.set_parallel(true)
	tween.tween_property(label, "position:y", label.position.y - 30, 0.5)
	tween.tween_property(label, "modulate:a", 0.0, 0.5)
	tween.chain().tween_callback(label.queue_free)


func _on_death() -> void:
	is_dead = true
	AudioManager.play_enemy_death()
	GameManager.on_enemy_killed(bounty)
	died.emit(bounty)

	# Death animation
	var tween = create_tween()
	tween.set_parallel(true)
	tween.tween_property(self, "scale", Vector2.ZERO, 0.2)
	tween.tween_property(self, "modulate:a", 0.0, 0.2)
	tween.chain().tween_callback(queue_free)


func _on_reached_exit() -> void:
	GameManager.on_enemy_reached_exit()
	reached_exit.emit()
	queue_free()


func set_path(new_path: Array[Vector2]) -> void:
	path = new_path
	path_index = 0


func get_distance_to_exit() -> float:
	if path.is_empty() or path_index >= path.size():
		return 0.0

	var total = 0.0
	var pos = global_position

	for i in range(path_index, path.size()):
		total += pos.distance_to(path[i])
		pos = path[i]

	return total
