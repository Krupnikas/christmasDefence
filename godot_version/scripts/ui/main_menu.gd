extends Control
## Main menu screen

@onready var campaign_button: Button = $VBoxContainer/CampaignButton
@onready var quick_play_button: Button = $VBoxContainer/QuickPlayButton
@onready var settings_button: Button = $VBoxContainer/SettingsButton
@onready var exit_button: Button = $VBoxContainer/ExitButton
@onready var settings_panel: Control = $SettingsPanel
@onready var version_label: Label = $VersionLabel


func _ready() -> void:
	campaign_button.pressed.connect(_on_campaign_pressed)
	quick_play_button.pressed.connect(_on_quick_play_pressed)
	settings_button.pressed.connect(_on_settings_pressed)
	exit_button.pressed.connect(_on_exit_pressed)

	# Hide settings panel initially
	if settings_panel:
		settings_panel.visible = false

	# Show version
	if version_label:
		version_label.text = "v1.0.0"

	AudioManager.play_music("menu")


func _on_campaign_pressed() -> void:
	AudioManager.play_button_click()
	get_tree().change_scene_to_file("res://scenes/ui/level_select.tscn")


func _on_quick_play_pressed() -> void:
	AudioManager.play_button_click()
	# Start random level or endless mode
	GameManager.start_level(1)


func _on_settings_pressed() -> void:
	AudioManager.play_button_click()
	if settings_panel:
		settings_panel.visible = true


func _on_exit_pressed() -> void:
	AudioManager.play_button_click()
	get_tree().quit()
