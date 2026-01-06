extends CannonBase
class_name AcidCannon
## Cannon with splash damage

const SPLASH_RADIUS: float = 64.0
const SPLASH_DAMAGE_PERCENT: float = 0.5

func _ready() -> void:
	cannon_type = GameManager.CannonType.ACID
	cannon_name = "Acid"
	base_cost = 120
	max_hp = 100.0
	attack_range = 140.0
	fire_rate = 0.6
	damage = 20.0
	crit_chance = 0.0

	super._ready()


func _deal_damage_instant() -> void:
	if target and is_instance_valid(target):
		var final_damage = _calculate_damage()

		# Direct damage to primary target
		if target.has_method("take_damage"):
			target.take_damage(final_damage, self)

		# Splash damage to nearby enemies
		var splash_pos = target.global_position
		var enemies = get_tree().get_nodes_in_group("enemies")

		for enemy in enemies:
			if enemy == target:
				continue
			if not is_instance_valid(enemy):
				continue

			var dist = splash_pos.distance_to(enemy.global_position)
			if dist <= SPLASH_RADIUS * _get_upgrade_multiplier():
				var splash_damage = final_damage * SPLASH_DAMAGE_PERCENT
				if enemy.has_method("take_damage"):
					enemy.take_damage(splash_damage, self)
