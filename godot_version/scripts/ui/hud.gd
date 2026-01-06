extends Control
## In-game HUD and UI management

signal cannon_selected(cannon_type: GameManager.CannonType)
signal upgrade_requested
signal sell_requested

# Top bar
@onready var cash_label: Label = $TopBar/CashLabel
@onready var hp_label: Label = $TopBar/HPLabel
@onready var wave_label: Label = $TopBar/WaveLabel
@onready var pause_button: Button = $TopBar/PauseButton
@onready var menu_button: Button = $TopBar/MenuButton
@onready var speed_button: Button = $TopBar/SpeedButton

# Cannon selection panel
@onready var cannon_panel: Control = $CannonPanel
@onready var cannon_grid: GridContainer = $CannonPanel/VBoxContainer/CannonGrid

# Cannon info panel
@onready var info_panel: Control = $InfoPanel
@onready var info_name: Label = $InfoPanel/VBoxContainer/NameLabel
@onready var info_stats: Label = $InfoPanel/VBoxContainer/StatsLabel
@onready var upgrade_button: Button = $InfoPanel/VBoxContainer/HBoxContainer/UpgradeButton
@onready var sell_button: Button = $InfoPanel/VBoxContainer/HBoxContainer/SellButton

# Game over panel
@onready var game_over_panel: Control = $GameOverPanel
@onready var result_label: Label = $GameOverPanel/VBoxContainer/ResultLabel
@onready var score_label: Label = $GameOverPanel/VBoxContainer/ScoreLabel
@onready var stars_container: HBoxContainer = $GameOverPanel/VBoxContainer/StarsContainer
@onready var continue_button: Button = $GameOverPanel/VBoxContainer/ContinueButton
@onready var retry_button: Button = $GameOverPanel/VBoxContainer/RetryButton

# Pause panel
@onready var pause_panel: Control = $PausePanel

# FPS counter
@onready var fps_label: Label = $FPSLabel

var cannon_buttons: Dictionary = {}
var current_selected_cell: Vector2i = Vector2i(-1, -1)
var current_cannon: CannonBase = null
var game_ref: Node2D = null


func _ready() -> void:
	# Connect to GameManager signals
	GameManager.cash_changed.connect(_on_cash_changed)
	GameManager.hp_changed.connect(_on_hp_changed)
	GameManager.wave_changed.connect(_on_wave_changed)

	# Connect button signals
	pause_button.pressed.connect(_on_pause_pressed)
	menu_button.pressed.connect(_on_menu_pressed)
	speed_button.pressed.connect(_on_speed_pressed)
	upgrade_button.pressed.connect(_on_upgrade_pressed)
	sell_button.pressed.connect(_on_sell_pressed)
	continue_button.pressed.connect(_on_continue_pressed)
	retry_button.pressed.connect(_on_retry_pressed)

	# Setup cannon selection buttons
	_setup_cannon_buttons()

	# Hide panels initially
	hide_panels()
	if game_over_panel:
		game_over_panel.visible = false
	if pause_panel:
		pause_panel.visible = false

	# Initial update
	_on_cash_changed(GameManager.cash)
	_on_hp_changed(GameManager.player_hp)
	_on_wave_changed(0, GameManager.total_waves)

	# Get game reference
	game_ref = get_parent().get_parent()


func _process(_delta: float) -> void:
	# Update FPS display
	if Settings.debug_show_fps and fps_label:
		fps_label.text = "FPS: %d" % Engine.get_frames_per_second()
		fps_label.visible = true
	elif fps_label:
		fps_label.visible = false

	# Handle pause input
	if Input.is_action_just_pressed("pause"):
		if GameManager.current_state == GameManager.GameState.PLAYING:
			_on_pause_pressed()
		elif GameManager.current_state == GameManager.GameState.PAUSED:
			_on_resume_pressed()


func _setup_cannon_buttons() -> void:
	var cannon_types = [
		GameManager.CannonType.GUN,
		GameManager.CannonType.SNIPER,
		GameManager.CannonType.RAPID,
		GameManager.CannonType.FIRE,
		GameManager.CannonType.ICE,
		GameManager.CannonType.ACID,
		GameManager.CannonType.LASER,
		GameManager.CannonType.TESLA,
		GameManager.CannonType.MINER
	]

	for cannon_type in cannon_types:
		var button = Button.new()
		var type_name = GameManager.CannonType.keys()[cannon_type]
		var cost = GameManager.CANNON_COSTS[cannon_type]

		button.text = "%s\n$%d" % [type_name, cost]
		button.custom_minimum_size = Vector2(80, 60)
		button.pressed.connect(_on_cannon_button_pressed.bind(cannon_type))

		cannon_grid.add_child(button)
		cannon_buttons[cannon_type] = button


func _update_cannon_buttons() -> void:
	for cannon_type in cannon_buttons:
		var button = cannon_buttons[cannon_type]
		var cost = GameManager.CANNON_COSTS[cannon_type]
		var unlocked = GameManager.is_cannon_unlocked(cannon_type)
		var affordable = GameManager.can_afford(cost)

		button.disabled = not unlocked or not affordable

		if not unlocked:
			button.modulate = Color(0.5, 0.5, 0.5)
		elif not affordable:
			button.modulate = Color(1.0, 0.5, 0.5)
		else:
			button.modulate = Color.WHITE


# Signal handlers
func _on_cash_changed(amount: int) -> void:
	if cash_label:
		cash_label.text = "$%d" % amount
	_update_cannon_buttons()


func _on_hp_changed(amount: int) -> void:
	if hp_label:
		hp_label.text = "HP: %d" % amount


func _on_wave_changed(current: int, total: int) -> void:
	if wave_label:
		wave_label.text = "Wave: %d/%d" % [current, total]


# Panel management
func show_cannon_selection(cell: Vector2i) -> void:
	current_selected_cell = cell
	current_cannon = null
	_update_cannon_buttons()
	cannon_panel.visible = true
	info_panel.visible = false


func show_cannon_info(cannon: CannonBase) -> void:
	current_cannon = cannon
	info_panel.visible = true
	cannon_panel.visible = false

	# Update info display
	info_name.text = cannon.cannon_name
	info_stats.text = "HP: %d/%d\nDamage: %d\nRange: %d" % [
		int(cannon.current_hp),
		int(cannon.max_hp),
		int(cannon.damage),
		int(cannon.attack_range)
	]

	# Update button states
	var upgrade_cost = cannon.get_upgrade_cost()
	if upgrade_cost > 0:
		upgrade_button.text = "Upgrade $%d" % upgrade_cost
		upgrade_button.disabled = not cannon.can_upgrade()
	else:
		upgrade_button.text = "MAX"
		upgrade_button.disabled = true

	sell_button.text = "Sell $%d" % cannon.get_sell_value()


func hide_panels() -> void:
	if cannon_panel:
		cannon_panel.visible = false
	if info_panel:
		info_panel.visible = false


func show_game_over(won: bool) -> void:
	game_over_panel.visible = true

	if won:
		result_label.text = "VICTORY!"
		result_label.modulate = Color.GREEN
	else:
		result_label.text = "DEFEAT"
		result_label.modulate = Color.RED

	score_label.text = "Score: %d" % (GameManager.player_hp * 100 + GameManager.cash)

	# Show stars
	var stars = GameManager._calculate_stars(GameManager._calculate_score())
	for i in range(3):
		var star_label = stars_container.get_child(i) if i < stars_container.get_child_count() else null
		if star_label:
			star_label.text = "*" if i < stars else " "


# Button handlers
func _on_cannon_button_pressed(cannon_type: GameManager.CannonType) -> void:
	if current_selected_cell == Vector2i(-1, -1):
		return

	AudioManager.play_button_click()
	cannon_selected.emit(cannon_type)

	if game_ref and game_ref.has_method("place_cannon"):
		game_ref.place_cannon(current_selected_cell, cannon_type)


func _on_upgrade_pressed() -> void:
	AudioManager.play_button_click()
	upgrade_requested.emit()

	if current_cannon:
		current_cannon.upgrade()
		show_cannon_info(current_cannon)


func _on_sell_pressed() -> void:
	AudioManager.play_button_click()
	sell_requested.emit()

	if current_cannon and game_ref:
		var cell = current_cannon.get_grid_position()
		if game_ref.has_method("sell_cannon"):
			game_ref.sell_cannon(cell)


func _on_pause_pressed() -> void:
	AudioManager.play_button_click()
	GameManager.pause_game()
	pause_panel.visible = true


func _on_resume_pressed() -> void:
	AudioManager.play_button_click()
	GameManager.resume_game()
	pause_panel.visible = false


func _on_menu_pressed() -> void:
	AudioManager.play_button_click()
	GameManager.return_to_level_select()


func _on_speed_pressed() -> void:
	AudioManager.play_button_click()
	var current_speed = GameManager.game_speed
	if current_speed < 2.0:
		GameManager.set_game_speed(2.0)
		speed_button.text = "2x"
	else:
		GameManager.set_game_speed(1.0)
		speed_button.text = "1x"


func _on_continue_pressed() -> void:
	AudioManager.play_button_click()
	GameManager.return_to_level_select()


func _on_retry_pressed() -> void:
	AudioManager.play_button_click()
	GameManager.start_level(GameManager.current_level)
