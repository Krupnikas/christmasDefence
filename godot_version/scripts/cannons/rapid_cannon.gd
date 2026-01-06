extends CannonBase
class_name RapidCannon
## Fast firing cannon with lower damage per shot

func _ready() -> void:
	cannon_type = GameManager.CannonType.RAPID
	cannon_name = "Rapid"
	base_cost = 75
	max_hp = 80.0
	attack_range = 120.0
	fire_rate = 3.0
	damage = 6.0
	crit_chance = 0.0

	super._ready()
