extends EnemyBase
class_name RegularEnemy
## Standard enemy with balanced stats

func _ready() -> void:
	enemy_name = "Regular"
	bounty = 10
	max_hp = 100.0
	speed = 80.0
	physical_resist = 0.0
	dodge_chance = 0.0
	status_immune = false
	is_flying = false
	attack_damage = 10.0
	attack_range = 32.0
	attack_speed = 1.0

	super._ready()
