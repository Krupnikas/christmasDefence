extends Node
## Global game state manager
## Handles game flow, level management, and shared state

signal cash_changed(new_amount: int)
signal hp_changed(new_amount: int)
signal wave_changed(current: int, total: int)
signal game_over(won: bool)
signal cannon_placed(cannon: Node2D)
signal cannon_sold(cannon: Node2D)
signal enemy_killed(enemy: Node2D, bounty: int)

# Game state
enum GameState { MENU, PLAYING, PAUSED, GAME_OVER }
var current_state: GameState = GameState.MENU
var current_level: int = 1
var game_speed: float = 1.0

# Player resources
var cash: int = 0:
	set(value):
		cash = max(0, value)
		cash_changed.emit(cash)

var player_hp: int = 20:
	set(value):
		player_hp = max(0, value)
		hp_changed.emit(player_hp)
		if player_hp <= 0:
			_on_game_over(false)

# Wave tracking
var current_wave: int = 0
var total_waves: int = 0
var enemies_remaining: int = 0
var wave_in_progress: bool = false

# Level data
var grid_width: int = 10
var grid_height: int = 6
var cell_size: int = 64

# Cannon unlocks (bitflags)
enum CannonType { GUN, SNIPER, RAPID, FIRE, ICE, ACID, LASER, TESLA, MINER }
var unlocked_cannons: int = 0b111111111  # All unlocked for testing

# References
var game_scene: Node2D = null
var pathfinding: Node = null

# Cannon costs
const CANNON_COSTS = {
	CannonType.GUN: 50,
	CannonType.SNIPER: 100,
	CannonType.RAPID: 75,
	CannonType.FIRE: 80,
	CannonType.ICE: 80,
	CannonType.ACID: 120,
	CannonType.LASER: 150,
	CannonType.TESLA: 200,
	CannonType.MINER: 150
}

# Cannon unlock levels
const CANNON_UNLOCK_LEVELS = {
	CannonType.GUN: 1,
	CannonType.SNIPER: 2,
	CannonType.RAPID: 3,
	CannonType.FIRE: 4,
	CannonType.ICE: 5,
	CannonType.ACID: 6,
	CannonType.MINER: 7,
	CannonType.LASER: 8,
	CannonType.TESLA: 10
}


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_ALWAYS


func start_level(level: int) -> void:
	current_level = level
	current_state = GameState.PLAYING
	current_wave = 0
	wave_in_progress = false
	game_speed = 1.0

	# Load level data
	var level_data = _load_level_data(level)
	if level_data:
		grid_width = level_data.get("grid_width", 10)
		grid_height = level_data.get("grid_height", 6)
		cash = level_data.get("starting_cash", 200)
		player_hp = level_data.get("starting_hp", 20)
		total_waves = level_data.get("wave_count", 10)
		unlocked_cannons = _get_unlocked_cannons_for_level(level)

	# Load game scene
	get_tree().change_scene_to_file("res://scenes/game/game.tscn")


func _load_level_data(level: int) -> Dictionary:
	var path = "res://levels/level_%d.tres" % level
	if ResourceLoader.exists(path):
		var data = load(path)
		return data.get_data() if data else {}

	# Default level data
	return {
		"grid_width": 8 + (level - 1) % 3 * 2,
		"grid_height": 5 + (level - 1) / 5,
		"starting_cash": 150 + level * 25,
		"starting_hp": max(10, 25 - level),
		"wave_count": 5 + level * 2
	}


func _get_unlocked_cannons_for_level(level: int) -> int:
	var unlocked = 0
	for cannon_type in CANNON_UNLOCK_LEVELS:
		if CANNON_UNLOCK_LEVELS[cannon_type] <= level:
			unlocked |= (1 << cannon_type)
	return unlocked


func is_cannon_unlocked(cannon_type: CannonType) -> bool:
	return (unlocked_cannons & (1 << cannon_type)) != 0


func can_afford(cost: int) -> bool:
	return cash >= cost


func spend_cash(amount: int) -> bool:
	if can_afford(amount):
		cash -= amount
		return true
	return false


func earn_cash(amount: int) -> void:
	cash += amount


func take_damage(amount: int) -> void:
	player_hp -= amount


func start_wave() -> void:
	if wave_in_progress:
		return

	current_wave += 1
	wave_in_progress = true
	wave_changed.emit(current_wave, total_waves)


func on_wave_complete() -> void:
	wave_in_progress = false

	# Wave completion bonus (30% of average cannon cost)
	var bonus = int(100 * 0.3)
	earn_cash(bonus)

	if current_wave >= total_waves:
		_on_game_over(true)


func on_enemy_killed(bounty: int) -> void:
	earn_cash(bounty)
	enemies_remaining -= 1

	if enemies_remaining <= 0 and wave_in_progress:
		on_wave_complete()


func on_enemy_reached_exit() -> void:
	take_damage(1)
	enemies_remaining -= 1

	if enemies_remaining <= 0 and wave_in_progress:
		on_wave_complete()


func _on_game_over(won: bool) -> void:
	current_state = GameState.GAME_OVER
	game_over.emit(won)

	if won:
		var score = _calculate_score()
		var stars = _calculate_stars(score)
		SaveManager.save_level_progress(current_level, stars, score)


func _calculate_score() -> int:
	return player_hp * 100 + cash


func _calculate_stars(score: int) -> int:
	# Thresholds vary by level
	var base_threshold = 500 + current_level * 100
	if score >= base_threshold * 2:
		return 3
	elif score >= base_threshold * 1.5:
		return 2
	elif score >= base_threshold:
		return 1
	return 0


func pause_game() -> void:
	if current_state == GameState.PLAYING:
		current_state = GameState.PAUSED
		get_tree().paused = true


func resume_game() -> void:
	if current_state == GameState.PAUSED:
		current_state = GameState.PLAYING
		get_tree().paused = false


func set_game_speed(speed: float) -> void:
	game_speed = clamp(speed, 0.5, 3.0)
	Engine.time_scale = game_speed


func return_to_menu() -> void:
	current_state = GameState.MENU
	get_tree().paused = false
	Engine.time_scale = 1.0
	get_tree().change_scene_to_file("res://scenes/ui/main_menu.tscn")


func return_to_level_select() -> void:
	current_state = GameState.MENU
	get_tree().paused = false
	Engine.time_scale = 1.0
	get_tree().change_scene_to_file("res://scenes/ui/level_select.tscn")
