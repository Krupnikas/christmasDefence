extends Node2D
class_name CannonBase
## Base class for all cannon types

signal destroyed
signal fired(bullet: Node2D)
signal upgraded

# Cannon identity
@export var cannon_type: GameManager.CannonType = GameManager.CannonType.GUN
@export var cannon_name: String = "Cannon"

# Stats
@export var base_cost: int = 50
@export var max_hp: float = 100.0
@export var attack_range: float = 150.0
@export var fire_rate: float = 1.0  # Shots per second
@export var damage: float = 15.0
@export var crit_chance: float = 0.0
@export var crit_multiplier: float = 2.0

# Upgrade tracking
var upgrade_level: int = 0  # 0 = base, 1 = medium, 2 = big
var total_invested: int = 0

# Runtime state
var current_hp: float
var target: Node2D = null
var fire_cooldown: float = 0.0
var is_active: bool = true

# Visual components
@onready var sprite: Sprite2D = $Sprite2D
@onready var range_indicator: Node2D = $RangeIndicator
@onready var hp_bar: ProgressBar = $HPBar
@onready var muzzle: Marker2D = $Muzzle

# Bullet scene to spawn
var bullet_scene: PackedScene


func _ready() -> void:
	current_hp = max_hp
	total_invested = base_cost
	_update_hp_bar()
	hide_range()

	# Load bullet scene if it exists
	var bullet_path = "res://scenes/bullets/%s_bullet.tscn" % cannon_name.to_lower()
	if ResourceLoader.exists(bullet_path):
		bullet_scene = load(bullet_path)


func _process(delta: float) -> void:
	if not is_active:
		return

	fire_cooldown = max(0, fire_cooldown - delta)

	_find_target()
	_rotate_towards_target(delta)

	if target and fire_cooldown <= 0:
		_fire()


func _find_target() -> void:
	# Find closest enemy in range
	var enemies = get_tree().get_nodes_in_group("enemies")
	var closest_dist = attack_range
	target = null

	for enemy in enemies:
		if not is_instance_valid(enemy):
			continue

		var dist = global_position.distance_to(enemy.global_position)
		if dist < closest_dist:
			closest_dist = dist
			target = enemy


func _rotate_towards_target(delta: float) -> void:
	if target:
		var target_angle = global_position.angle_to_point(target.global_position)
		rotation = lerp_angle(rotation, target_angle + PI/2, delta * 10.0)


func _fire() -> void:
	if not bullet_scene:
		# No bullet scene, just do instant damage
		_deal_damage_instant()
	else:
		_spawn_bullet()

	fire_cooldown = 1.0 / fire_rate
	AudioManager.play_cannon_shoot()
	fired.emit(null)


func _deal_damage_instant() -> void:
	if target and is_instance_valid(target) and target.has_method("take_damage"):
		var final_damage = _calculate_damage()
		target.take_damage(final_damage, self)


func _spawn_bullet() -> void:
	var bullet = bullet_scene.instantiate()
	bullet.global_position = muzzle.global_position
	bullet.direction = (target.global_position - muzzle.global_position).normalized()
	bullet.damage = _calculate_damage()
	bullet.source_cannon = self
	get_tree().current_scene.add_child(bullet)
	fired.emit(bullet)


func _calculate_damage() -> float:
	var final_damage = damage * _get_upgrade_multiplier()

	# Critical hit check
	if randf() < crit_chance:
		final_damage *= crit_multiplier
		# TODO: Show crit feedback

	return final_damage


func _get_upgrade_multiplier() -> float:
	match upgrade_level:
		0: return 1.0
		1: return 1.5
		2: return 2.0
		_: return 1.0


func take_damage(amount: float) -> void:
	if not Settings.enable_cannon_hp:
		return

	if Settings.debug_invincible_cannons:
		return

	current_hp -= amount
	_update_hp_bar()

	if current_hp <= 0:
		_on_destroyed()


func _update_hp_bar() -> void:
	if hp_bar:
		hp_bar.value = (current_hp / max_hp) * 100
		hp_bar.visible = current_hp < max_hp


func _on_destroyed() -> void:
	is_active = false
	destroyed.emit()
	# Play destruction effect
	queue_free()


func get_upgrade_cost() -> int:
	if upgrade_level >= 2:
		return 0  # Max level
	return int(base_cost * (0.75 if upgrade_level == 0 else 1.0))


func can_upgrade() -> bool:
	return upgrade_level < 2 and GameManager.can_afford(get_upgrade_cost())


func upgrade() -> bool:
	if not can_upgrade():
		return false

	var cost = get_upgrade_cost()
	if GameManager.spend_cash(cost):
		upgrade_level += 1
		total_invested += cost

		# Increase stats
		max_hp *= 1.5
		current_hp = max_hp
		attack_range *= 1.15
		damage *= 1.5

		_update_hp_bar()
		upgraded.emit()
		return true

	return false


func get_sell_value() -> int:
	return int(total_invested * Settings.sell_refund_percent)


func sell() -> void:
	var refund = get_sell_value()
	GameManager.earn_cash(refund)
	AudioManager.play_cannon_sell()
	GameManager.cannon_sold.emit(self)
	queue_free()


func show_range() -> void:
	if range_indicator:
		range_indicator.visible = true


func hide_range() -> void:
	if range_indicator:
		range_indicator.visible = false


func get_grid_position() -> Vector2i:
	return Vector2i(
		int(global_position.x / GameManager.cell_size),
		int(global_position.y / GameManager.cell_size)
	)
