extends Node
## Global settings and feature flags manager

# Gameplay Features
var enable_camera_controls: bool = true
var enable_pathfinding: bool = true
var enable_cannon_hp: bool = true
var enable_enemy_attacks: bool = true
var enable_miner_cannon: bool = true
var enable_sell_confirmation: bool = false

# Debug Options
var debug_show_paths: bool = false
var debug_show_ranges: bool = false
var debug_infinite_money: bool = false
var debug_invincible_cannons: bool = false
var debug_show_fps: bool = true
var debug_show_grid: bool = false

# Audio
var music_volume: float = 0.5:
	set(value):
		music_volume = clamp(value, 0.0, 1.0)
		_apply_audio_settings()

var sfx_volume: float = 0.7:
	set(value):
		sfx_volume = clamp(value, 0.0, 1.0)
		_apply_audio_settings()

var music_enabled: bool = true
var sfx_enabled: bool = true

# Graphics
var enable_particles: bool = true
var enable_screen_shake: bool = true
var fullscreen: bool = false:
	set(value):
		fullscreen = value
		_apply_fullscreen()

# Camera
var camera_zoom_min: float = 0.5
var camera_zoom_max: float = 2.0
var camera_pan_speed: float = 500.0

# Economy
var sell_refund_percent: float = 0.70
var miner_coins_per_second: float = 2.5
var wave_bonus_percent: float = 0.30

# Balance
var difficulty_multiplier: float = 1.0

const SETTINGS_PATH = "user://settings.cfg"


func _ready() -> void:
	load_settings()


func _apply_audio_settings() -> void:
	var music_bus = AudioServer.get_bus_index("Music")
	var sfx_bus = AudioServer.get_bus_index("SFX")

	if music_bus >= 0:
		AudioServer.set_bus_volume_db(music_bus, linear_to_db(music_volume if music_enabled else 0.0))
	if sfx_bus >= 0:
		AudioServer.set_bus_volume_db(sfx_bus, linear_to_db(sfx_volume if sfx_enabled else 0.0))


func _apply_fullscreen() -> void:
	if fullscreen:
		DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_FULLSCREEN)
	else:
		DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_WINDOWED)


func save_settings() -> void:
	var config = ConfigFile.new()

	# Gameplay
	config.set_value("gameplay", "enable_camera_controls", enable_camera_controls)
	config.set_value("gameplay", "enable_pathfinding", enable_pathfinding)
	config.set_value("gameplay", "enable_cannon_hp", enable_cannon_hp)
	config.set_value("gameplay", "enable_enemy_attacks", enable_enemy_attacks)
	config.set_value("gameplay", "enable_miner_cannon", enable_miner_cannon)
	config.set_value("gameplay", "enable_sell_confirmation", enable_sell_confirmation)

	# Audio
	config.set_value("audio", "music_volume", music_volume)
	config.set_value("audio", "sfx_volume", sfx_volume)
	config.set_value("audio", "music_enabled", music_enabled)
	config.set_value("audio", "sfx_enabled", sfx_enabled)

	# Graphics
	config.set_value("graphics", "enable_particles", enable_particles)
	config.set_value("graphics", "enable_screen_shake", enable_screen_shake)
	config.set_value("graphics", "fullscreen", fullscreen)

	# Debug
	config.set_value("debug", "show_fps", debug_show_fps)
	config.set_value("debug", "show_paths", debug_show_paths)
	config.set_value("debug", "show_ranges", debug_show_ranges)
	config.set_value("debug", "show_grid", debug_show_grid)

	config.save(SETTINGS_PATH)


func load_settings() -> void:
	var config = ConfigFile.new()
	var err = config.load(SETTINGS_PATH)

	if err != OK:
		# First run, use defaults
		return

	# Gameplay
	enable_camera_controls = config.get_value("gameplay", "enable_camera_controls", true)
	enable_pathfinding = config.get_value("gameplay", "enable_pathfinding", true)
	enable_cannon_hp = config.get_value("gameplay", "enable_cannon_hp", true)
	enable_enemy_attacks = config.get_value("gameplay", "enable_enemy_attacks", true)
	enable_miner_cannon = config.get_value("gameplay", "enable_miner_cannon", true)
	enable_sell_confirmation = config.get_value("gameplay", "enable_sell_confirmation", false)

	# Audio
	music_volume = config.get_value("audio", "music_volume", 0.5)
	sfx_volume = config.get_value("audio", "sfx_volume", 0.7)
	music_enabled = config.get_value("audio", "music_enabled", true)
	sfx_enabled = config.get_value("audio", "sfx_enabled", true)

	# Graphics
	enable_particles = config.get_value("graphics", "enable_particles", true)
	enable_screen_shake = config.get_value("graphics", "enable_screen_shake", true)
	fullscreen = config.get_value("graphics", "fullscreen", false)

	# Debug
	debug_show_fps = config.get_value("debug", "show_fps", true)
	debug_show_paths = config.get_value("debug", "show_paths", false)
	debug_show_ranges = config.get_value("debug", "show_ranges", false)
	debug_show_grid = config.get_value("debug", "show_grid", false)

	_apply_audio_settings()
	_apply_fullscreen()


func reset_to_defaults() -> void:
	enable_camera_controls = true
	enable_pathfinding = true
	enable_cannon_hp = true
	enable_enemy_attacks = true
	enable_miner_cannon = true
	enable_sell_confirmation = false

	music_volume = 0.5
	sfx_volume = 0.7
	music_enabled = true
	sfx_enabled = true

	enable_particles = true
	enable_screen_shake = true
	fullscreen = false

	debug_show_fps = true
	debug_show_paths = false
	debug_show_ranges = false
	debug_show_grid = false

	save_settings()
	_apply_audio_settings()
	_apply_fullscreen()
