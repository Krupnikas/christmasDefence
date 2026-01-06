extends EnemyBase
class_name FlyingEnemy
## Flying enemy that ignores ground obstacles

func _ready() -> void:
	enemy_name = "Flying"
	bounty = 12
	max_hp = 80.0
	speed = 100.0
	physical_resist = 0.5
	dodge_chance = 0.0
	status_immune = false
	is_flying = true
	attack_damage = 8.0
	attack_range = 32.0
	attack_speed = 1.0

	super._ready()


# Flying enemies take direct path to exit
func set_path(new_path: Array[Vector2]) -> void:
	if new_path.is_empty():
		return

	# Just go directly to the exit
	path = [new_path[new_path.size() - 1]]
	path_index = 0
