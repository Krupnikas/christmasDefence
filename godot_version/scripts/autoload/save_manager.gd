extends Node
## Handles saving and loading game progress

const SAVE_PATH = "user://save_data.json"
const MAX_LEVELS = 15

var level_data: Dictionary = {}


func _ready() -> void:
	load_game()


func save_game() -> void:
	var file = FileAccess.open(SAVE_PATH, FileAccess.WRITE)
	if file:
		file.store_string(JSON.stringify(level_data, "\t"))
		file.close()


func load_game() -> void:
	if not FileAccess.file_exists(SAVE_PATH):
		_initialize_save_data()
		return

	var file = FileAccess.open(SAVE_PATH, FileAccess.READ)
	if file:
		var json = JSON.new()
		var parse_result = json.parse(file.get_as_text())
		file.close()

		if parse_result == OK:
			level_data = json.data
		else:
			_initialize_save_data()
	else:
		_initialize_save_data()


func _initialize_save_data() -> void:
	level_data = {
		"levels": {},
		"total_stars": 0,
		"highest_level_unlocked": 1
	}

	for i in range(1, MAX_LEVELS + 1):
		level_data.levels[str(i)] = {
			"unlocked": i == 1,
			"completed": false,
			"stars": 0,
			"high_score": 0
		}

	save_game()


func save_level_progress(level: int, stars: int, score: int) -> void:
	var level_key = str(level)

	if not level_data.levels.has(level_key):
		level_data.levels[level_key] = {
			"unlocked": true,
			"completed": false,
			"stars": 0,
			"high_score": 0
		}

	var current_data = level_data.levels[level_key]

	# Update if better
	if stars > current_data.stars:
		level_data.total_stars += (stars - current_data.stars)
		current_data.stars = stars

	if score > current_data.high_score:
		current_data.high_score = score

	current_data.completed = true

	# Unlock next level
	if level < MAX_LEVELS:
		var next_level_key = str(level + 1)
		if level_data.levels.has(next_level_key):
			level_data.levels[next_level_key].unlocked = true
		else:
			level_data.levels[next_level_key] = {
				"unlocked": true,
				"completed": false,
				"stars": 0,
				"high_score": 0
			}

		if level + 1 > level_data.highest_level_unlocked:
			level_data.highest_level_unlocked = level + 1

	save_game()


func is_level_unlocked(level: int) -> bool:
	var level_key = str(level)
	if level_data.levels.has(level_key):
		return level_data.levels[level_key].unlocked
	return level == 1


func is_level_completed(level: int) -> bool:
	var level_key = str(level)
	if level_data.levels.has(level_key):
		return level_data.levels[level_key].completed
	return false


func get_level_stars(level: int) -> int:
	var level_key = str(level)
	if level_data.levels.has(level_key):
		return level_data.levels[level_key].stars
	return 0


func get_level_high_score(level: int) -> int:
	var level_key = str(level)
	if level_data.levels.has(level_key):
		return level_data.levels[level_key].high_score
	return 0


func get_total_stars() -> int:
	return level_data.get("total_stars", 0)


func get_highest_level_unlocked() -> int:
	return level_data.get("highest_level_unlocked", 1)


func reset_progress() -> void:
	_initialize_save_data()
