extends CannonBase
class_name LaserCannon
## Cannon that pierces through all enemies in a line

const LASER_WIDTH: float = 10.0

func _ready() -> void:
	cannon_type = GameManager.CannonType.LASER
	cannon_name = "Laser"
	base_cost = 150
	max_hp = 70.0
	attack_range = 200.0
	fire_rate = 0.4
	damage = 25.0
	crit_chance = 0.0

	super._ready()


func _fire() -> void:
	# Fire laser beam that hits all enemies in line
	if not target:
		return

	var direction = (target.global_position - global_position).normalized()
	var final_damage = _calculate_damage()

	# Cast ray and find all enemies in path
	var enemies = get_tree().get_nodes_in_group("enemies")
	var hit_enemies: Array = []

	for enemy in enemies:
		if not is_instance_valid(enemy):
			continue

		# Check if enemy is in laser path
		var to_enemy = enemy.global_position - global_position
		var distance = to_enemy.length()

		if distance > attack_range * _get_upgrade_multiplier():
			continue

		# Project enemy position onto laser direction
		var projection = to_enemy.dot(direction)
		if projection < 0:
			continue

		# Distance from laser line
		var perpendicular = to_enemy - direction * projection
		if perpendicular.length() <= LASER_WIDTH + 16:  # 16 = enemy half-size
			hit_enemies.append(enemy)

	# Apply damage to all hit enemies
	for enemy in hit_enemies:
		if enemy.has_method("take_damage"):
			enemy.take_damage(final_damage, self)

	fire_cooldown = 1.0 / fire_rate
	AudioManager.play_cannon_shoot()
	fired.emit(null)

	# Visual effect (spawn laser beam visual)
	_show_laser_effect(direction)


func _show_laser_effect(direction: Vector2) -> void:
	# Create temporary laser visual
	var laser = Line2D.new()
	laser.width = LASER_WIDTH
	laser.default_color = Color(1.0, 0.0, 1.0, 0.8)  # Purple
	laser.add_point(Vector2.ZERO)
	laser.add_point(direction * attack_range * _get_upgrade_multiplier())
	add_child(laser)

	# Fade out
	var tween = create_tween()
	tween.tween_property(laser, "modulate:a", 0.0, 0.2)
	tween.tween_callback(laser.queue_free)
