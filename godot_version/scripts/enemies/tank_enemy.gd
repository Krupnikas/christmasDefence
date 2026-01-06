extends EnemyBase
class_name TankEnemy
## Slow, high HP enemy with physical resistance

func _ready() -> void:
	enemy_name = "Tank"
	bounty = 20
	max_hp = 300.0
	speed = 40.0
	physical_resist = 0.5
	dodge_chance = 0.0
	status_immune = false
	is_flying = false
	attack_damage = 20.0
	attack_range = 48.0
	attack_speed = 0.5

	super._ready()
