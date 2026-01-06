extends CannonBase
class_name TeslaCannon
## Cannon with chain lightning that jumps between enemies

const MAX_CHAINS: int = 3
const CHAIN_RANGE: float = 80.0
const CHAIN_DECAY: float = 0.5  # Each chain does 50% of previous

func _ready() -> void:
	cannon_type = GameManager.CannonType.TESLA
	cannon_name = "Tesla"
	base_cost = 200
	max_hp = 90.0
	attack_range = 160.0
	fire_rate = 0.5
	damage = 30.0
	crit_chance = 0.0

	super._ready()


func _fire() -> void:
	if not target or not is_instance_valid(target):
		return

	var final_damage = _calculate_damage()
	var chain_targets: Array = [target]
	var current_damage = final_damage

	# Hit primary target
	if target.has_method("take_damage"):
		target.take_damage(current_damage, self)

	# Chain to additional targets
	var last_target = target
	var max_chains = MAX_CHAINS + upgrade_level

	for i in range(max_chains):
		current_damage *= CHAIN_DECAY
		var next_target = _find_chain_target(last_target, chain_targets)

		if next_target:
			chain_targets.append(next_target)
			if next_target.has_method("take_damage"):
				next_target.take_damage(current_damage, self)
			_show_chain_effect(last_target.global_position, next_target.global_position)
			last_target = next_target
		else:
			break

	fire_cooldown = 1.0 / fire_rate
	AudioManager.play_cannon_shoot()
	fired.emit(null)

	# Show initial arc from cannon to first target
	_show_chain_effect(muzzle.global_position, target.global_position)


func _find_chain_target(from_enemy: Node2D, exclude: Array) -> Node2D:
	var enemies = get_tree().get_nodes_in_group("enemies")
	var closest_dist = CHAIN_RANGE * _get_upgrade_multiplier()
	var closest_enemy: Node2D = null

	for enemy in enemies:
		if enemy in exclude:
			continue
		if not is_instance_valid(enemy):
			continue

		var dist = from_enemy.global_position.distance_to(enemy.global_position)
		if dist < closest_dist:
			closest_dist = dist
			closest_enemy = enemy

	return closest_enemy


func _show_chain_effect(from: Vector2, to: Vector2) -> void:
	# Create lightning arc visual
	var arc = Line2D.new()
	arc.width = 3.0
	arc.default_color = Color(1.0, 1.0, 0.0, 0.9)  # Yellow

	# Add jagged points for lightning effect
	var num_points = 5
	var direction = (to - from)
	var length = direction.length()
	direction = direction.normalized()
	var perpendicular = Vector2(-direction.y, direction.x)

	arc.add_point(from)
	for i in range(1, num_points):
		var t = float(i) / num_points
		var pos = from + direction * length * t
		pos += perpendicular * randf_range(-10, 10)
		arc.add_point(pos)
	arc.add_point(to)

	get_tree().current_scene.add_child(arc)

	# Fade out
	var tween = create_tween()
	tween.tween_property(arc, "modulate:a", 0.0, 0.15)
	tween.tween_callback(arc.queue_free)
