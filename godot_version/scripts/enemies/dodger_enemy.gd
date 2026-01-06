extends EnemyBase
class_name DodgerEnemy
## Enemy with high dodge chance

func _ready() -> void:
	enemy_name = "Dodger"
	bounty = 8
	max_hp = 70.0
	speed = 110.0
	physical_resist = 0.0
	dodge_chance = 0.4
	status_immune = false
	is_flying = false
	attack_damage = 8.0
	attack_range = 28.0
	attack_speed = 1.5

	super._ready()
