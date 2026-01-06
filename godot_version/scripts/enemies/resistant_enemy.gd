extends EnemyBase
class_name ResistantEnemy
## Enemy immune to status effects

func _ready() -> void:
	enemy_name = "Resistant"
	bounty = 15
	max_hp = 120.0
	speed = 70.0
	physical_resist = 0.0
	dodge_chance = 0.0
	status_immune = true
	is_flying = false
	attack_damage = 15.0
	attack_range = 40.0
	attack_speed = 0.8

	super._ready()

	# Visual indicator for resistance
	modulate = Color(0.8, 1.0, 0.8)  # Slight green tint
