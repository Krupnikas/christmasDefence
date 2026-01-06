extends CannonBase
class_name GunCannon
## Balanced starter cannon with reliable damage

func _ready() -> void:
	cannon_type = GameManager.CannonType.GUN
	cannon_name = "Gun"
	base_cost = 50
	max_hp = 100.0
	attack_range = 150.0
	fire_rate = 1.0
	damage = 15.0
	crit_chance = 0.0

	super._ready()
