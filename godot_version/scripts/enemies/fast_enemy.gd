extends EnemyBase
class_name FastEnemy
## Fast moving enemy with low HP

func _ready() -> void:
	enemy_name = "Fast"
	bounty = 5
	max_hp = 50.0
	speed = 160.0
	physical_resist = 0.0
	dodge_chance = 0.0
	status_immune = false
	is_flying = false
	attack_damage = 5.0
	attack_range = 24.0
	attack_speed = 2.0

	super._ready()
