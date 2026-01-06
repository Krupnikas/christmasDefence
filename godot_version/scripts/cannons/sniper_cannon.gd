extends CannonBase
class_name SniperCannon
## Long range cannon with critical hit chance

func _ready() -> void:
	cannon_type = GameManager.CannonType.SNIPER
	cannon_name = "Sniper"
	base_cost = 100
	max_hp = 60.0
	attack_range = 250.0
	fire_rate = 0.5
	damage = 40.0
	crit_chance = 0.2
	crit_multiplier = 2.0

	super._ready()
