extends CannonBase
class_name FireCannon
## Cannon that applies burn damage over time

const BURN_DURATION: float = 3.0
const BURN_DPS: float = 5.0

func _ready() -> void:
	cannon_type = GameManager.CannonType.FIRE
	cannon_name = "Fire"
	base_cost = 80
	max_hp = 80.0
	attack_range = 130.0
	fire_rate = 0.8
	damage = 10.0
	crit_chance = 0.0

	super._ready()


func _deal_damage_instant() -> void:
	if target and is_instance_valid(target):
		var final_damage = _calculate_damage()
		if target.has_method("take_damage"):
			target.take_damage(final_damage, self)
		if target.has_method("apply_burn"):
			target.apply_burn(BURN_DURATION * _get_upgrade_multiplier(), BURN_DPS * _get_upgrade_multiplier())
