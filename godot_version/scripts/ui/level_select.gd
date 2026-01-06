extends Control
## Level selection screen with 5x3 grid of levels

const LEVELS_PER_ROW = 5
const ROWS = 3
const TOTAL_LEVELS = 15

@onready var grid_container: GridContainer = $VBoxContainer/LevelGrid
@onready var back_button: Button = $VBoxContainer/BackButton
@onready var stars_label: Label = $VBoxContainer/StarsLabel

var level_buttons: Array[Button] = []


func _ready() -> void:
	back_button.pressed.connect(_on_back_pressed)
	_create_level_buttons()
	_update_display()
	AudioManager.play_music("menu")


func _create_level_buttons() -> void:
	grid_container.columns = LEVELS_PER_ROW

	for i in range(TOTAL_LEVELS):
		var level = i + 1
		var button = Button.new()
		button.custom_minimum_size = Vector2(100, 100)
		button.pressed.connect(_on_level_pressed.bind(level))

		grid_container.add_child(button)
		level_buttons.append(button)


func _update_display() -> void:
	var total_stars = SaveManager.get_total_stars()
	stars_label.text = "Total Stars: %d / %d" % [total_stars, TOTAL_LEVELS * 3]

	for i in range(level_buttons.size()):
		var level = i + 1
		var button = level_buttons[i]
		var unlocked = SaveManager.is_level_unlocked(level)
		var stars = SaveManager.get_level_stars(level)

		button.disabled = not unlocked

		if unlocked:
			var star_text = ""
			for s in range(3):
				if s < stars:
					star_text += "*"
				else:
					star_text += " "
			button.text = "%d\n%s" % [level, star_text]
		else:
			button.text = "LOCKED"


func _on_level_pressed(level: int) -> void:
	AudioManager.play_button_click()
	GameManager.start_level(level)


func _on_back_pressed() -> void:
	AudioManager.play_button_click()
	get_tree().change_scene_to_file("res://scenes/ui/main_menu.tscn")
