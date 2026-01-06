# Tower Defence - Godot Version

A minimalist, strategy-focused tower defense game built with Godot 4.2+.

## Features

- **9 Cannon Types**: Gun, Sniper, Rapid, Fire, Ice, Acid, Laser, Tesla, Miner
- **6 Enemy Types**: Regular, Fast, Tank, Flying, Dodger, Resistant
- **Strategic Economy**: Tight resource management where every decision matters
- **A* Pathfinding**: Enemies navigate around placed cannons
- **15 Levels**: Progressive campaign with star ratings
- **OLED-Friendly**: Pure black background design

## Play Online

The game is automatically deployed to GitHub Pages when changes are pushed to the main branch.

**Play at**: `https://[username].github.io/christmasDefence/`

## Local Development

### Requirements

- Godot 4.2+ (with .NET support optional)
- Git LFS (for large assets)

### Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/[username]/christmasDefence.git
   cd christmasDefence/godot_version
   ```

2. Open in Godot:
   ```bash
   godot project.godot
   ```

3. Press F5 to run

### Export

The project includes export presets for:
- **Web** (HTML5) - Primary target for GitHub Pages
- **Linux** (x86_64)
- **Windows** (x86_64)

## Project Structure

```
godot_version/
├── project.godot           # Project configuration
├── export_presets.cfg      # Export settings
├── scenes/
│   ├── ui/                 # Menu scenes
│   │   ├── main_menu.tscn
│   │   ├── level_select.tscn
│   │   └── hud.tscn
│   ├── game/
│   │   └── game.tscn       # Main game scene
│   ├── cannons/            # Cannon scenes
│   ├── enemies/            # Enemy scenes
│   └── bullets/            # Bullet scenes
├── scripts/
│   ├── autoload/           # Singleton managers
│   │   ├── game_manager.gd
│   │   ├── settings.gd
│   │   ├── save_manager.gd
│   │   └── audio_manager.gd
│   ├── cannons/            # Cannon scripts
│   ├── enemies/            # Enemy scripts
│   ├── bullets/            # Bullet scripts
│   ├── game/               # Core game logic
│   └── ui/                 # UI scripts
├── assets/
│   ├── sprites/            # Textures and sprites
│   ├── sounds/             # Audio files
│   ├── fonts/              # Custom fonts
│   └── themes/             # UI themes
└── levels/                 # Level data files
```

## Controls

| Input | Action |
|-------|--------|
| Left Click | Select cell / Place cannon |
| Right Click | Sell cannon |
| Mouse Wheel | Zoom in/out (if enabled) |
| ESC | Pause game |
| Space | Toggle speed (1x/2x) |

## Cannon Types

| Type | Cost | Description |
|------|------|-------------|
| Gun | $50 | Balanced starter |
| Sniper | $100 | Long range, critical hits |
| Rapid | $75 | Fast fire, low damage |
| Fire | $80 | Burn damage over time |
| Ice | $80 | Slows enemies |
| Acid | $120 | Splash damage |
| Laser | $150 | Pierce through enemies |
| Tesla | $200 | Chain lightning |
| Miner | $150 | Generates coins (2.5/sec) |

## Enemy Types

| Type | HP | Speed | Special |
|------|------|-------|---------|
| Regular | 100 | Normal | None |
| Fast | 50 | 2x | Low HP |
| Tank | 300 | 0.5x | 50% physical resist |
| Flying | 80 | 1.2x | Ignores obstacles |
| Dodger | 70 | 1.3x | 40% dodge |
| Resistant | 120 | 0.9x | Status immune |

## Configuration

Feature flags can be toggled in Settings:
- `enable_camera_controls` - Zoom/pan
- `enable_pathfinding` - A* pathfinding
- `enable_cannon_hp` - Cannons can be destroyed
- `enable_enemy_attacks` - Enemies attack cannons
- `enable_miner_cannon` - Enable Miner type

## Deployment

The game automatically deploys to GitHub Pages via GitHub Actions when:
- Changes are pushed to `master` or `main` branch
- Files in `godot_version/` are modified

Manual deployment can be triggered from the Actions tab.

## License

MIT License - See LICENSE file for details.
