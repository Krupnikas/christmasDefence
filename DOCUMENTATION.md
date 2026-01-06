# Christmas Defence - Codebase Documentation

## Overview

**Christmas Defence** is a Tower Defence game built with C++ and Qt5 framework. The game was developed as a theme-independent Tower Defence engine that can be reskinned by changing texture folders. The current theme is Christmas/New Year.

The game features:
- Grid-based gameplay on N x M cell fields
- Multiple cannon types with upgrade paths
- Wave-based enemy spawning system
- Resource management (cash/HP)
- OpenGL-accelerated rendering via QGraphicsView

## Project Structure

```
christmasDefence/
├── main.cpp              # Application entry point
├── mainview.cpp/h        # Main application widget and event handling
├── Scene.cpp/h           # Graphics scene management (coordinate transforms)
├── Resource.cpp/h        # Resource loading (textures, sounds, paths)
├── Helper.cpp/h          # Utility functions (math, pathfinding, metrics)
├── Window.cpp/h          # Abstract window interface
├── Sound.cpp/h           # Sound management
├── Bullet/               # Bullet implementations
│   ├── IBullet.cpp/h     # Abstract bullet base class
│   ├── BurnBullet.cpp/h  # Fire damage bullet
│   ├── FastBullet.cpp/h  # High-speed bullet
│   ├── MonsterBullet.cpp/h # Heavy damage bullet
│   └── SlowBullet.cpp/h  # Slowing effect bullet
├── Cannon/               # Cannon (tower) implementations
│   ├── ICannon.cpp/h     # Abstract cannon base class
│   ├── BurnCannon.cpp/h  # Fire cannon (area damage)
│   ├── FastCannon.cpp/h  # Rapid-fire cannon
│   ├── MonsterCannon.cpp/h # Heavy damage cannon
│   ├── SlowCannon.cpp/h  # Slowing cannon
│   └── CannonRadius.cpp/h # Visual cannon range indicator
├── Effect/               # Visual effects
│   ├── CEffect.cpp/h     # Base effect class
│   └── CEnemyEffect.cpp/h # Enemy-specific effects
├── Enemy/                # Enemy implementations
│   ├── IEnemy.cpp/h      # Abstract enemy base class
│   ├── FastEnemy.cpp/h   # Fast-moving enemy
│   ├── Movements.cpp/h   # Pathfinding and movement logic
│   ├── CHpBackground.cpp/h # HP bar background
│   └── CHpCurrent.cpp/h  # HP bar current value
├── Game/                 # Core game logic
│   ├── Game.cpp/h        # Main game controller
│   ├── Wave.cpp/h        # Wave data structure
│   ├── WaveManager.cpp/h # Wave spawning logic
│   ├── UserManager.cpp/h # Player resources (cash, HP)
│   └── FieldItem.cpp/h   # Field cell items
├── InfoBlock/            # UI panels
│   ├── IInfoBlock.cpp/h  # Abstract info block base
│   ├── CannonSelection.cpp/h # Cannon purchase menu
│   ├── CannonUpgrade.cpp/h   # Cannon upgrade menu
│   ├── ControlButtons.cpp/h  # Game control buttons
│   ├── ImageAndNumber.cpp/h  # Icon + number display
│   ├── PauseWindow.cpp/h     # Pause menu
│   ├── UserInfo.cpp/h        # Cash/HP display
│   └── WaveInfoBlock.cpp/h   # Wave progress display
├── Menu/                 # Menu screens
│   ├── GameMenu.cpp/h    # Main menu
│   └── LevelMenu.cpp/h   # Level selection menu
├── Metrics/              # Game constants and configuration
│   ├── Metrics.h         # Core metrics (screen size, cell counts)
│   ├── MetricsDef.h      # Metrics definitions
│   ├── BulletMetrics.h   # Bullet-specific metrics
│   ├── CannonMetrics.h   # Cannon-specific metrics
│   ├── EnemyMetrics.h    # Enemy-specific metrics
│   └── ZOrderMetrics.h   # Z-order layering constants
└── SceneObject/          # Renderable objects
    ├── SceneObject.cpp/h # Base scene object class
    ├── Button.cpp/h      # Clickable button
    ├── ButtonDepr.cpp/h  # Deprecated button (legacy)
    ├── GameBackground.cpp/h # In-game background
    └── SceneBackground.cpp/h # Menu background
```

## Architecture

### Core Classes

#### MainView (mainview.h)
The main application widget that:
- Creates and manages the Qt application
- Holds references to the game, menus, scene, and resources
- Handles all mouse events and routes them appropriately
- Manages game state transitions (menu -> game -> pause)

#### CGame (Game/Game.h)
The central game controller that:
- Manages all game objects (cannons, enemies, bullets)
- Runs position and draw timers (separate update loops)
- Handles pathfinding via distance grid
- Processes cell selection and cannon placement
- Reads level configuration files

Key data structures:
```cpp
std::list<std::shared_ptr<IBullet>> bullets;
std::list<std::shared_ptr<IEnemy>> enemies;
std::vector<std::vector<std::shared_ptr<ICannon>>> cannons;  // Grid of cannons
std::vector<std::vector<int>> distances;  // Pathfinding distance grid
```

#### CScene (Scene.h)
Manages the QGraphicsScene and provides:
- Coordinate transformation (local <-> global)
- Adding/removing graphics items
- FPS/TPS display
- Aspect ratio handling (16:9 letterboxing)

Local coordinate system: 1600x900 pixels
Actual rendering scales to window size.

### Object Hierarchy

```
CSceneObject (base for all visible objects)
├── ICannon (abstract cannon)
│   ├── CFastCannon
│   ├── CMonsterCannon
│   ├── CSlowCannon
│   └── CBurnCannon
├── IEnemy (abstract enemy)
│   └── CFastEnemy
├── IBullet (abstract bullet)
│   ├── CFastBullet
│   ├── CMonsterBullet
│   ├── CSlowBullet
│   └── CBurnBullet
└── IInfoBlock (UI panels)
    ├── CCannonSelection
    ├── CCannonUpgrade
    ├── CUserInfo
    └── CWaveInfoBlock

IWindow (abstract window)
├── CGame
├── CGameMenu
└── CLevelMenu
```

### Game Loop

The game uses two separate timers:
1. **Position Timer** (game logic at `PositionTimerInterval` ms)
   - Wave management
   - Bullet movement and collision detection
   - Enemy movement and death checks
   - Cannon rotation and targeting
   - TPS calculation

2. **Draw Timer** (rendering at `DrawTimerInterval` ms)
   - Updates all sprite positions
   - FPS calculation

### Pathfinding

Enemies navigate using a distance grid computed via BFS from end cells. The `helper::updateDistances()` function recalculates paths when cannons are placed/removed. Enemies always move toward lower distance values.

### Level File Format

Level files (e.g., `1.txt`) contain:
```
<CellNumY>           # Grid height
<edge> <pos>         # Start cell configuration
<edge> <pos>         # End cell configuration
<field_items>        # (Currently unused)
<num_waves>          # Number of waves
<wave_data>...       # For each wave: timeBeforeStart, enemyInterval, totalEnemies, type, texture, power
<cash> <hp>          # Starting resources
```

## Branches

### master (main development branch)
Contains the stable, working version of the game with:
- All core game mechanics
- 4 cannon types (Fast, Monster, Slow, Burn)
- Wave-based enemy spawning
- OpenGL rendering optimization

Recent commits:
- `04fd4e4` - Rollback to classical enemies
- `cc2d5c6` - memese
- `dec50aa` - update game settings
- `b5a4dce` - vector to list (changed containers for better iteration)
- `c6d7c2b` - no trace

### animation (experimental sprite work)
Adds a new Sprite class for animation support:
- **New files**: `SceneObject/Sprite.cpp`, `SceneObject/Sprite.h`
- Creates `CSprite` class extending `QGraphicsItem`
- Currently minimal implementation (constructor only)

Single commit:
- `1f0fb42` - Work with sprite class

### perfomance (typo: "performance" - threading optimization)
Adds multi-threaded calculation for better performance:
- **New files**: `Game/CalculationThread.cpp`, `Game/CalculationThread.h`
- Moves game logic calculations to separate thread
- Adds mutex protection for bullets (`bulletsMutex`)
- Changes bullet/enemy containers to allow indexed access

Key changes:
- `CCalculationThread` class extends `QThread`
- Separates calculation from rendering
- Tracks TPS in calculation thread

Commits:
- `581a83a` - merging
- `f92bf00` - another performance(
- `dc8c78c` - perfomance
- `fe1e3e7` - merge
- `d9843c5` - qthread

## Key Metrics and Constants

From `Metrics/Metrics.h`:
```cpp
LocalWidth = 1600      // Virtual screen width
LocalHeight = 900      // Virtual screen height
LevelNum = 20          // Maximum levels
GameMenuButtonNum = 4  // Menu button count
SoundLevel = 0.1       // Default sound volume
```

Cannon types: 4 (Fast, Monster, Slow, Burn)
Each cannon has 3 upgrade levels (Small, Medium, Big)

## Dependencies

- **Qt 5.x** - Core framework
  - QtCore, QtGui, QtWidgets
  - QtMultimedia (sound/music)
  - QtOpenGL (accelerated rendering)
- **OpenGL** - Hardware-accelerated graphics

## Building

The project uses Qt's qmake build system:
```bash
qmake christmasDefence.pro
make
```

Cross-platform support for:
- Desktop (Windows, macOS, Linux)
- Mobile (Android, iOS) - via Qt

## Original Design Goals (from README)

The game was designed as a "theme-independent Tower Defence skeleton" that can be reskinned by changing texture folders. Key principles:
1. High abstraction level - game works with any correct parameter/texture changes
2. Grid-based gameplay on N x M cells
3. Three object types: cannons (K types), enemies (L types), bullets (K types)
4. Enemies move from start edge to end edge, avoiding cannons
5. Cannons fire periodically, creating bullet objects
6. Resource system for building cannons
7. Wave-based enemy progression

## Code Style Notes

- Uses `std::shared_ptr` extensively for memory management
- Qt signals/slots for event handling
- Namespace `m::` for metrics constants
- Namespace `helper::` for utility functions
- Namespace `mov::` for movement/pathfinding
- Hungarian-ish naming: `C` prefix for classes (CGame, CScene, etc.)
- Protected members with trailing underscore in private methods
