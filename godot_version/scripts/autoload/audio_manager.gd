extends Node
## Global audio manager for music and sound effects

var music_player: AudioStreamPlayer
var sfx_players: Array[AudioStreamPlayer] = []
const MAX_SFX_PLAYERS = 8

# Preloaded sounds (paths - will be loaded when available)
var sounds: Dictionary = {
	"button_click": "res://assets/sounds/button_click.wav",
	"cannon_place": "res://assets/sounds/cannon_place.wav",
	"cannon_sell": "res://assets/sounds/cannon_sell.wav",
	"cannon_shoot": "res://assets/sounds/cannon_shoot.wav",
	"enemy_hit": "res://assets/sounds/enemy_hit.wav",
	"enemy_death": "res://assets/sounds/enemy_death.wav",
	"wave_start": "res://assets/sounds/wave_start.wav",
	"wave_complete": "res://assets/sounds/wave_complete.wav",
	"game_over": "res://assets/sounds/game_over.wav",
	"victory": "res://assets/sounds/victory.wav",
	"coin": "res://assets/sounds/coin.wav",
	"error": "res://assets/sounds/error.wav"
}

var music_tracks: Dictionary = {
	"menu": "res://assets/sounds/music_menu.ogg",
	"game": "res://assets/sounds/music_game.ogg"
}


func _ready() -> void:
	# Create music player
	music_player = AudioStreamPlayer.new()
	music_player.bus = "Music"
	add_child(music_player)

	# Create SFX player pool
	for i in range(MAX_SFX_PLAYERS):
		var player = AudioStreamPlayer.new()
		player.bus = "SFX"
		add_child(player)
		sfx_players.append(player)


func play_sound(sound_name: String, volume_db: float = 0.0) -> void:
	if not Settings.sfx_enabled:
		return

	if not sounds.has(sound_name):
		push_warning("Sound not found: " + sound_name)
		return

	var path = sounds[sound_name]
	if not ResourceLoader.exists(path):
		# Sound file doesn't exist yet, skip silently
		return

	var stream = load(path)
	if stream:
		var player = _get_available_sfx_player()
		if player:
			player.stream = stream
			player.volume_db = volume_db
			player.play()


func _get_available_sfx_player() -> AudioStreamPlayer:
	for player in sfx_players:
		if not player.playing:
			return player

	# All players busy, use first one (oldest sound)
	return sfx_players[0]


func play_music(track_name: String, fade_duration: float = 1.0) -> void:
	if not Settings.music_enabled:
		return

	if not music_tracks.has(track_name):
		push_warning("Music track not found: " + track_name)
		return

	var path = music_tracks[track_name]
	if not ResourceLoader.exists(path):
		# Music file doesn't exist yet, skip silently
		return

	var stream = load(path)
	if stream:
		if fade_duration > 0 and music_player.playing:
			# Fade out current, then play new
			var tween = create_tween()
			tween.tween_property(music_player, "volume_db", -80.0, fade_duration)
			tween.tween_callback(_start_music.bind(stream))
		else:
			_start_music(stream)


func _start_music(stream: AudioStream) -> void:
	music_player.stream = stream
	music_player.volume_db = linear_to_db(Settings.music_volume)
	music_player.play()


func stop_music(fade_duration: float = 1.0) -> void:
	if fade_duration > 0 and music_player.playing:
		var tween = create_tween()
		tween.tween_property(music_player, "volume_db", -80.0, fade_duration)
		tween.tween_callback(music_player.stop)
	else:
		music_player.stop()


func set_music_volume(volume: float) -> void:
	if music_player:
		music_player.volume_db = linear_to_db(volume)


func play_button_click() -> void:
	play_sound("button_click")


func play_cannon_place() -> void:
	play_sound("cannon_place")


func play_cannon_sell() -> void:
	play_sound("cannon_sell")


func play_cannon_shoot() -> void:
	play_sound("cannon_shoot", -5.0)  # Slightly quieter


func play_enemy_hit() -> void:
	play_sound("enemy_hit", -3.0)


func play_enemy_death() -> void:
	play_sound("enemy_death")


func play_coin() -> void:
	play_sound("coin", -2.0)


func play_error() -> void:
	play_sound("error")
