extends CannonBase
class_name IceCannon
## Cannon that slows enemies

const SLOW_DURATION: float = 3.0
const SLOW_AMOUNT: float = 0.5  # 50% speed reduction

func _ready() -> void:
	cannon_type = GameManager.CannonType.ICE
	cannon_name = "Ice"
	base_cost = 80
	max_hp = 80.0
	attack_range = 140.0
	fire_rate = 0.7
	damage = 5.0  # Low direct damage
	crit_chance = 0.0

	super._ready()


func _deal_damage_instant() -> void:
	if target and is_instance_valid(target):
		var final_damage = _calculate_damage()
		if target.has_method("take_damage"):
			target.take_damage(final_damage, self)
		if target.has_method("apply_slow"):
			target.apply_slow(SLOW_DURATION * _get_upgrade_multiplier(), SLOW_AMOUNT)
