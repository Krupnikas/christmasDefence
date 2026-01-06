extends Node2D
## Main game scene controller

signal cell_selected(cell: Vector2i)
signal cell_deselected

# Grid
var grid_cells: Dictionary = {}  # Vector2i -> CellData
var placed_cannons: Dictionary = {}  # Vector2i -> CannonBase

# Pathfinding
var pathfinder: AStarGrid2D
var spawn_points: Array[Vector2] = []
var exit_points: Array[Vector2] = []

# Wave management
var wave_data: Array = []
var current_wave_enemies: Array = []
var spawn_timer: float = 0.0
var spawn_interval: float = 1.0
var enemies_to_spawn: int = 0
var current_enemy_type: int = 0

# Selection
var selected_cell: Vector2i = Vector2i(-1, -1)
var hover_cell: Vector2i = Vector2i(-1, -1)

# UI references
@onready var grid_container: Node2D = $Grid
@onready var cannons_container: Node2D = $Cannons
@onready var enemies_container: Node2D = $Enemies
@onready var bullets_container: Node2D = $Bullets
@onready var hud: Control = $CanvasLayer/HUD
@onready var camera: Camera2D = $Camera2D

# Preloaded scenes
var cannon_scenes: Dictionary = {}
var enemy_scenes: Dictionary = {}


func _ready() -> void:
	GameManager.game_scene = self
	_setup_grid()
	_setup_pathfinding()
	_load_cannon_scenes()
	_load_enemy_scenes()
	_generate_wave_data()

	# Connect signals
	GameManager.game_over.connect(_on_game_over)

	# Start first wave after delay
	await get_tree().create_timer(2.0).timeout
	_start_next_wave()


func _process(delta: float) -> void:
	if GameManager.current_state != GameManager.GameState.PLAYING:
		return

	_handle_input()
	_process_wave_spawning(delta)


func _handle_input() -> void:
	# Get mouse position in world coordinates
	var mouse_pos = get_global_mouse_position()
	var cell = world_to_grid(mouse_pos)

	# Update hover
	if cell != hover_cell:
		hover_cell = cell
		_update_hover_visual()

	# Left click - select cell
	if Input.is_action_just_pressed("click"):
		_on_cell_clicked(cell)

	# Right click - sell cannon
	if Input.is_action_just_pressed("right_click"):
		_on_cell_right_clicked(cell)

	# Camera controls
	if Settings.enable_camera_controls:
		_handle_camera_input()


func _handle_camera_input() -> void:
	if Input.is_action_just_pressed("zoom_in"):
		camera.zoom = (camera.zoom * 1.1).clamp(
			Vector2(Settings.camera_zoom_min, Settings.camera_zoom_min),
			Vector2(Settings.camera_zoom_max, Settings.camera_zoom_max)
		)

	if Input.is_action_just_pressed("zoom_out"):
		camera.zoom = (camera.zoom / 1.1).clamp(
			Vector2(Settings.camera_zoom_min, Settings.camera_zoom_min),
			Vector2(Settings.camera_zoom_max, Settings.camera_zoom_max)
		)


func _setup_grid() -> void:
	var cell_size = GameManager.cell_size

	for x in range(GameManager.grid_width):
		for y in range(GameManager.grid_height):
			var cell_pos = Vector2i(x, y)
			var world_pos = grid_to_world(cell_pos)

			# Create cell visual
			var cell_visual = ColorRect.new()
			cell_visual.size = Vector2(cell_size - 2, cell_size - 2)
			cell_visual.position = world_pos + Vector2(1, 1)
			cell_visual.color = Color(0.1, 0.1, 0.1, 0.5)
			grid_container.add_child(cell_visual)

			grid_cells[cell_pos] = {
				"visual": cell_visual,
				"walkable": true,
				"cannon": null
			}

	# Set spawn and exit points
	spawn_points = [grid_to_world(Vector2i(0, GameManager.grid_height / 2)) + Vector2(GameManager.cell_size / 2, GameManager.cell_size / 2)]
	exit_points = [grid_to_world(Vector2i(GameManager.grid_width - 1, GameManager.grid_height / 2)) + Vector2(GameManager.cell_size / 2, GameManager.cell_size / 2)]


func _setup_pathfinding() -> void:
	pathfinder = AStarGrid2D.new()
	pathfinder.region = Rect2i(0, 0, GameManager.grid_width, GameManager.grid_height)
	pathfinder.cell_size = Vector2(GameManager.cell_size, GameManager.cell_size)
	pathfinder.diagonal_mode = AStarGrid2D.DIAGONAL_MODE_NEVER
	pathfinder.update()


func _load_cannon_scenes() -> void:
	var cannon_types = ["gun", "sniper", "rapid", "fire", "ice", "acid", "laser", "tesla", "miner"]
	for type in cannon_types:
		var path = "res://scenes/cannons/%s_cannon.tscn" % type
		if ResourceLoader.exists(path):
			cannon_scenes[type] = load(path)


func _load_enemy_scenes() -> void:
	var enemy_types = ["regular", "fast", "tank", "flying", "dodger", "resistant"]
	for type in enemy_types:
		var path = "res://scenes/enemies/%s_enemy.tscn" % type
		if ResourceLoader.exists(path):
			enemy_scenes[type] = load(path)


func _generate_wave_data() -> void:
	# Generate waves based on level
	var level = GameManager.current_level
	var num_waves = GameManager.total_waves

	for i in range(num_waves):
		var wave = {
			"enemy_count": 5 + i * 2 + level,
			"enemy_types": _get_wave_enemy_types(i, level),
			"spawn_interval": max(0.5, 2.0 - i * 0.1),
			"hp_multiplier": 1.0 + i * 0.15 + (level - 1) * 0.1
		}
		wave_data.append(wave)


func _get_wave_enemy_types(wave_index: int, level: int) -> Array:
	var types = ["regular"]

	if wave_index >= 2 or level >= 3:
		types.append("fast")
	if wave_index >= 4 or level >= 5:
		types.append("tank")
	if wave_index >= 6 or level >= 7:
		types.append("flying")
	if wave_index >= 8 or level >= 9:
		types.append("dodger")
	if wave_index >= 10 or level >= 11:
		types.append("resistant")

	return types


func _start_next_wave() -> void:
	if GameManager.current_wave >= GameManager.total_waves:
		return

	GameManager.start_wave()

	var wave = wave_data[GameManager.current_wave - 1]
	enemies_to_spawn = wave.enemy_count
	spawn_interval = wave.spawn_interval
	current_wave_enemies = wave.enemy_types

	GameManager.enemies_remaining = enemies_to_spawn


func _process_wave_spawning(delta: float) -> void:
	if enemies_to_spawn <= 0:
		return

	spawn_timer += delta

	if spawn_timer >= spawn_interval:
		spawn_timer = 0.0
		_spawn_enemy()
		enemies_to_spawn -= 1


func _spawn_enemy() -> void:
	if current_wave_enemies.is_empty():
		return

	var enemy_type = current_wave_enemies[randi() % current_wave_enemies.size()]
	var enemy: EnemyBase

	# Create enemy based on type
	if enemy_scenes.has(enemy_type):
		enemy = enemy_scenes[enemy_type].instantiate()
	else:
		# Fallback to creating script-based enemy
		enemy = _create_enemy_by_type(enemy_type)

	if not enemy:
		return

	# Apply wave HP multiplier
	var wave = wave_data[GameManager.current_wave - 1]
	enemy.max_hp *= wave.hp_multiplier
	enemy.current_hp = enemy.max_hp

	# Set spawn position
	var spawn_pos = spawn_points[randi() % spawn_points.size()]
	enemy.global_position = spawn_pos

	# Calculate path
	var path = _calculate_enemy_path(enemy)
	enemy.set_path(path)

	enemies_container.add_child(enemy)

	# Connect signals
	enemy.died.connect(_on_enemy_died)
	enemy.reached_exit.connect(_on_enemy_reached_exit)


func _create_enemy_by_type(type: String) -> EnemyBase:
	match type:
		"regular":
			return RegularEnemy.new()
		"fast":
			return FastEnemy.new()
		"tank":
			return TankEnemy.new()
		"flying":
			return FlyingEnemy.new()
		"dodger":
			return DodgerEnemy.new()
		"resistant":
			return ResistantEnemy.new()
		_:
			return RegularEnemy.new()


func _calculate_enemy_path(enemy: EnemyBase) -> Array[Vector2]:
	var start_cell = world_to_grid(enemy.global_position)
	var end_cell = world_to_grid(exit_points[0])

	if enemy.is_flying:
		# Flying enemies go directly to exit
		return [exit_points[0]]

	if not Settings.enable_pathfinding:
		# Simple direct path
		var path: Array[Vector2] = []
		for x in range(start_cell.x, end_cell.x + 1):
			path.append(grid_to_world(Vector2i(x, start_cell.y)) + Vector2(GameManager.cell_size / 2, GameManager.cell_size / 2))
		return path

	# A* pathfinding
	var astar_path = pathfinder.get_point_path(start_cell, end_cell)
	var world_path: Array[Vector2] = []

	for point in astar_path:
		world_path.append(point + Vector2(GameManager.cell_size / 2, GameManager.cell_size / 2))

	return world_path


func _on_cell_clicked(cell: Vector2i) -> void:
	if not is_valid_cell(cell):
		_deselect_cell()
		return

	if placed_cannons.has(cell):
		# Show upgrade/sell menu
		selected_cell = cell
		cell_selected.emit(cell)
		if hud.has_method("show_cannon_info"):
			hud.show_cannon_info(placed_cannons[cell])
	else:
		# Show cannon selection menu
		selected_cell = cell
		cell_selected.emit(cell)
		if hud.has_method("show_cannon_selection"):
			hud.show_cannon_selection(cell)


func _on_cell_right_clicked(cell: Vector2i) -> void:
	if placed_cannons.has(cell):
		sell_cannon(cell)


func _deselect_cell() -> void:
	selected_cell = Vector2i(-1, -1)
	cell_deselected.emit()
	if hud.has_method("hide_panels"):
		hud.hide_panels()


func _update_hover_visual() -> void:
	# Update cell highlighting
	for cell_pos in grid_cells:
		var cell_data = grid_cells[cell_pos]
		if cell_pos == hover_cell and is_valid_cell(cell_pos):
			cell_data.visual.color = Color(0.3, 0.3, 0.3, 0.7)
		else:
			cell_data.visual.color = Color(0.1, 0.1, 0.1, 0.5)


func place_cannon(cell: Vector2i, cannon_type: GameManager.CannonType) -> bool:
	if not is_valid_cell(cell):
		return false

	if placed_cannons.has(cell):
		return false

	var cost = GameManager.CANNON_COSTS[cannon_type]
	if not GameManager.can_afford(cost):
		AudioManager.play_error()
		return false

	# Check if placement would block path
	if Settings.enable_pathfinding and not _validate_placement(cell):
		AudioManager.play_error()
		# Show feedback
		return false

	# Create cannon
	var cannon = _create_cannon(cannon_type)
	if not cannon:
		return false

	# Spend cash
	GameManager.spend_cash(cost)

	# Place cannon
	cannon.global_position = grid_to_world(cell) + Vector2(GameManager.cell_size / 2, GameManager.cell_size / 2)
	cannons_container.add_child(cannon)
	cannon.add_to_group("cannons")

	placed_cannons[cell] = cannon
	grid_cells[cell].cannon = cannon
	grid_cells[cell].walkable = false

	# Update pathfinding
	pathfinder.set_point_solid(cell, true)

	AudioManager.play_cannon_place()
	GameManager.cannon_placed.emit(cannon)

	_deselect_cell()
	return true


func _create_cannon(cannon_type: GameManager.CannonType) -> CannonBase:
	var type_name = GameManager.CannonType.keys()[cannon_type].to_lower()

	if cannon_scenes.has(type_name):
		return cannon_scenes[type_name].instantiate()

	# Fallback to script-based creation
	match cannon_type:
		GameManager.CannonType.GUN:
			return GunCannon.new()
		GameManager.CannonType.SNIPER:
			return SniperCannon.new()
		GameManager.CannonType.RAPID:
			return RapidCannon.new()
		GameManager.CannonType.FIRE:
			return FireCannon.new()
		GameManager.CannonType.ICE:
			return IceCannon.new()
		GameManager.CannonType.ACID:
			return AcidCannon.new()
		GameManager.CannonType.LASER:
			return LaserCannon.new()
		GameManager.CannonType.TESLA:
			return TeslaCannon.new()
		GameManager.CannonType.MINER:
			return MinerCannon.new()
		_:
			return GunCannon.new()


func _validate_placement(cell: Vector2i) -> bool:
	# Temporarily mark cell as solid
	pathfinder.set_point_solid(cell, true)

	# Check if path exists from spawn to exit
	var start_cell = world_to_grid(spawn_points[0])
	var end_cell = world_to_grid(exit_points[0])
	var path = pathfinder.get_point_path(start_cell, end_cell)

	# Restore cell
	pathfinder.set_point_solid(cell, false)

	return path.size() > 0


func sell_cannon(cell: Vector2i) -> void:
	if not placed_cannons.has(cell):
		return

	var cannon = placed_cannons[cell]
	cannon.sell()

	placed_cannons.erase(cell)
	grid_cells[cell].cannon = null
	grid_cells[cell].walkable = true

	# Update pathfinding
	pathfinder.set_point_solid(cell, false)

	_deselect_cell()


func upgrade_cannon(cell: Vector2i) -> bool:
	if not placed_cannons.has(cell):
		return false

	var cannon = placed_cannons[cell]
	return cannon.upgrade()


# Utility functions
func grid_to_world(cell: Vector2i) -> Vector2:
	return Vector2(cell.x * GameManager.cell_size, cell.y * GameManager.cell_size)


func world_to_grid(pos: Vector2) -> Vector2i:
	return Vector2i(int(pos.x / GameManager.cell_size), int(pos.y / GameManager.cell_size))


func is_valid_cell(cell: Vector2i) -> bool:
	return cell.x >= 0 and cell.x < GameManager.grid_width and cell.y >= 0 and cell.y < GameManager.grid_height


# Signal handlers
func _on_enemy_died(_bounty: int) -> void:
	# Check for wave completion
	if enemies_to_spawn <= 0 and get_tree().get_nodes_in_group("enemies").size() <= 1:
		await get_tree().create_timer(1.0).timeout
		if GameManager.current_wave < GameManager.total_waves:
			_start_next_wave()


func _on_enemy_reached_exit() -> void:
	pass


func _on_game_over(won: bool) -> void:
	# Show game over UI
	if hud.has_method("show_game_over"):
		hud.show_game_over(won)
