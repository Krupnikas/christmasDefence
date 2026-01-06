# Tower Defence: Game Design Document

**Version:** 2.0
**Based on:** Christmas Defence Engine
**Status:** Design Complete

---

## Table of Contents

1. [Executive Summary](#1-executive-summary)
2. [Core Vision](#2-core-vision)
3. [Technical Foundation](#3-technical-foundation)
4. [Visual Design](#4-visual-design)
5. [Game Architecture](#5-game-architecture)
6. [Cannon System](#6-cannon-system)
7. [Enemy System](#7-enemy-system)
8. [Combat & Status Effects](#8-combat--status-effects)
9. [Economy System](#9-economy-system)
10. [Level System](#10-level-system)
11. [Pathfinding System](#11-pathfinding-system)
12. [UI/UX Design](#12-uiux-design)
13. [Camera System](#13-camera-system)
14. [Feature Flags & Settings](#14-feature-flags--settings)
15. [Balance Targets](#15-balance-targets)
16. [Implementation Mapping](#16-implementation-mapping)

---

## 1. Executive Summary

A minimalist, strategy-focused tower defense game built on the Christmas Defence Qt5/C++ engine. The game emphasizes difficult but fair economics where challenge comes from resource management rather than reflexes.

### Key Features
- 9 unique cannon types with distinct mechanics
- 6 enemy types with varied behaviors and resistances
- Strategic economy requiring optimal resource management
- A* pathfinding with dynamic obstacle avoidance
- Progressive 15-level campaign with star ratings
- Feature flag system for experimental mechanics

---

## 2. Core Vision

### Design Philosophy
> "Barely possible to progress, but achievable with optimal strategy"

The player should always feel 10-20% short of "comfortable" resources. Every decision matters:
- Cannon placement is permanent investment
- Selling is strategic, not error correction (70% refund)
- No single "best" cannon - all are situationally useful
- Combined effects (slow + damage) are rewarded

### Target Experience
| Level Range | Difficulty | Expected Behavior |
|-------------|------------|-------------------|
| 1-5 | Learning | Forgiving, teaches mechanics |
| 6-10 | Strategic | Requires planning, some retries |
| 11-15 | Expert | Demands optimal play, multiple attempts |

---

## 3. Technical Foundation

### Engine Base
Built on the Christmas Defence Qt5/C++ engine with:

| Component | Technology |
|-----------|------------|
| Framework | Qt 5.x (QtCore, QtGui, QtWidgets) |
| Rendering | OpenGL via QGraphicsView |
| Audio | QtMultimedia |
| Coordinate System | Virtual 1600x900, scales to window |
| Platforms | Desktop (Win/Mac/Linux), Mobile (Android/iOS) |

### Core Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                        MainView                              │
│  (Application widget, event routing, state management)       │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  ┌──────────┐    ┌──────────┐    ┌──────────┐               │
│  │ CGameMenu│    │CLevelMenu│    │  CGame   │               │
│  │  (Main)  │───>│ (Select) │───>│ (Play)   │               │
│  └──────────┘    └──────────┘    └──────────┘               │
│                                        │                     │
│                           ┌────────────┼────────────┐        │
│                           ▼            ▼            ▼        │
│                     ┌─────────┐  ┌─────────┐  ┌─────────┐   │
│                     │ Cannons │  │ Enemies │  │ Bullets │   │
│                     │  Grid   │  │  List   │  │  List   │   │
│                     └─────────┘  └─────────┘  └─────────┘   │
│                                                              │
├─────────────────────────────────────────────────────────────┤
│                         CScene                               │
│  (QGraphicsScene wrapper, coordinate transforms, rendering)  │
└─────────────────────────────────────────────────────────────┘
```

### Game Loop (Dual Timer System)

```
┌─────────────────────────────────────────┐
│           Position Timer                 │
│     (Logic @ PositionTimerInterval)      │
├─────────────────────────────────────────┤
│ • Wave spawning                         │
│ • Enemy movement & pathfinding          │
│ • Cannon targeting & rotation           │
│ • Bullet movement & collision           │
│ • Status effect processing              │
│ • Economy updates (Miner income)        │
│ • HP checks (enemies & cannons)         │
│ • TPS calculation                       │
└─────────────────────────────────────────┘

┌─────────────────────────────────────────┐
│            Draw Timer                    │
│     (Render @ DrawTimerInterval)         │
├─────────────────────────────────────────┤
│ • Sprite position updates               │
│ • Status effect visuals                 │
│ • HP bar rendering                      │
│ • UI updates                            │
│ • FPS calculation                       │
└─────────────────────────────────────────┘
```

---

## 4. Visual Design

### Theme: OLED Minimalist

| Element | Specification |
|---------|---------------|
| Background | Pure black (#000000) - OLED friendly |
| Grid Lines | Subtle dark gray (#1a1a1a) |
| UI Elements | Clean, flat design with color accents |
| Typography | Sans-serif, high contrast |

### Color Palette

| Usage | Color | Hex |
|-------|-------|-----|
| Background | Black | #000000 |
| Grid | Dark Gray | #1a1a1a |
| Fire Effect | Orange/Red | #ff6600 / #ff0000 |
| Ice Effect | Cyan/Blue | #00ffff / #0066ff |
| Acid Effect | Green | #00ff00 |
| Laser Effect | Purple | #ff00ff |
| Tesla Effect | Yellow/White | #ffff00 / #ffffff |
| Health Bar | Green→Yellow→Red | Gradient |
| Currency | Gold | #ffd700 |

### Status Effect Visuals

| Effect | Visual Indicator |
|--------|------------------|
| Burning | Orange pulsing aura, ember particles |
| Frozen/Slowed | Blue frost aura, ice crystal particles |
| Acid | Green bubbling effect, drip particles |
| Electrified | Yellow arc sparks between targets |

### Feedback Text

| Event | Display |
|-------|---------|
| Fire + Ice Cancel | "THAW!" or "DOUSED!" |
| Dodge | "DODGE!" |
| Critical Hit | "CRITICAL!" |
| Path Blocked | "BLOCKED!" |
| Insufficient Funds | "NOT ENOUGH!" |

---

## 5. Game Architecture

### Class Hierarchy

```
CSceneObject (base renderable)
│
├── ICannon (abstract cannon) ────────────────────────┐
│   ├── CGunCannon      (balanced starter)            │
│   ├── CSniperCannon   (long range, crits)           │
│   ├── CRapidCannon    (fast fire, low damage)       │
│   ├── CFireCannon     (burn DoT)         [existing] │
│   ├── CIceCannon      (slow effect)      [existing] │
│   ├── CAcidCannon     (splash damage)               │
│   ├── CLaserCannon    (pierce enemies)              │
│   ├── CTeslaCannon    (chain lightning)             │
│   └── CMinerCannon    (coin generation)             │
│
├── IEnemy (abstract enemy) ──────────────────────────┐
│   ├── CRegularEnemy   (standard)                    │
│   ├── CFastEnemy      (high speed)       [existing] │
│   ├── CTankEnemy      (high HP, resists)            │
│   ├── CFlyingEnemy    (ignores obstacles)           │
│   ├── CDodgerEnemy    (40% dodge)                   │
│   └── CResistantEnemy (status immune)               │
│
├── IBullet (abstract projectile) ────────────────────┐
│   ├── CGunBullet                                    │
│   ├── CSniperBullet                                 │
│   ├── CRapidBullet                                  │
│   ├── CFireBullet              [existing]           │
│   ├── CIceBullet               [existing]           │
│   ├── CAcidBullet                                   │
│   ├── CLaserBeam     (instant, no projectile)       │
│   └── CTeslaArc      (chain, no projectile)         │
│
└── IInfoBlock (UI panels) ───────────────────────────┐
    ├── CCannonSelection   [existing]                 │
    ├── CCannonUpgrade     [existing]                 │
    ├── CUserInfo          [existing]                 │
    ├── CWaveInfoBlock     [existing]                 │
    └── CStarRating        [new]                      │
```

### Manager Classes

| Manager | Responsibility |
|---------|----------------|
| CWaveManager | Wave spawning, progression, bonuses |
| CUserManager | Cash, HP, score tracking |
| CPathfindingManager | A* pathfinding, path validation |
| CStatusEffectManager | DoT processing, effect stacking |
| CSaveManager | Progress persistence, star ratings |
| CSettingsManager | Feature flags, game settings |

---

## 6. Cannon System

### Cannon Types (9 Total)

| # | Type | Unlock | Cost | Mechanic | Status |
|---|------|--------|------|----------|--------|
| 1 | **Gun** | Level 1 | 50 | Balanced damage, medium range | Implement |
| 2 | **Sniper** | Level 2 | 100 | Long range, 20% critical (2x damage) | Implement |
| 3 | **Rapid** | Level 3 | 75 | 3x fire rate, 0.4x damage | Implement |
| 4 | **Fire** | Level 4 | 80 | Burn DoT (3s, 5 DPS) | Exists (BurnCannon) |
| 5 | **Ice** | Level 5 | 80 | 50% slow (3s) | Exists (SlowCannon) |
| 6 | **Acid** | Level 6 | 120 | Splash (50% damage, 1 cell radius) | Implement |
| 7 | **Laser** | Level 8 | 150 | Pierce through all enemies in line | Implement |
| 8 | **Tesla** | Level 10 | 200 | Chain to 3 enemies (50% decay) | Implement |
| 9 | **Miner** | Level 7 | 150 | 2.5 coins/sec, no attack | Implement |

### Cannon Properties

```cpp
struct CannonStats {
    int cost;           // Purchase price
    int hp;             // Cannon health (destroyed when 0)
    float range;        // Attack radius in cells
    float fireRate;     // Shots per second
    int damage;         // Base damage per hit
    float critChance;   // Critical hit probability (0-1)
    float critMulti;    // Critical damage multiplier
    ESizeType size;     // Small, Medium, Big (upgrade level)
};
```

### Cannon HP System

- All cannons have HP (varies by type)
- Enemies attack cannons when in range
- Destroyed cannons are removed (no refund)
- Visual: HP bar below cannon sprite

| Cannon | Base HP | Upgraded HP |
|--------|---------|-------------|
| Gun | 100 | 150 / 200 |
| Sniper | 60 | 90 / 120 |
| Rapid | 80 | 120 / 160 |
| Fire | 80 | 120 / 160 |
| Ice | 80 | 120 / 160 |
| Acid | 100 | 150 / 200 |
| Laser | 70 | 105 / 140 |
| Tesla | 90 | 135 / 180 |
| Miner | 150 | 225 / 300 |

### Upgrade System

Each cannon has 3 tiers (existing `ESizeType`):
- **Small** (Base): Initial purchase
- **Medium** (+50% stats): Upgrade cost = 75% of base
- **Big** (+100% stats): Upgrade cost = 100% of base

### Sell Mechanic
- **Trigger**: Right-click on cannon
- **Refund**: 70% of total invested (base + upgrades)
- **Confirmation**: Optional (feature flag)

---

## 7. Enemy System

### Enemy Types (6 Total)

| # | Type | HP | Speed | Special | Status |
|---|------|----|----- -|---------|--------|
| 1 | **Regular** | 100 | 1.0x | None | Implement |
| 2 | **Fast** | 50 | 2.0x | Low HP | Exists |
| 3 | **Tank** | 300 | 0.5x | 50% physical resist | Implement |
| 4 | **Flying** | 80 | 1.2x | Ignores ground obstacles | Implement |
| 5 | **Dodger** | 70 | 1.3x | 40% dodge chance | Implement |
| 6 | **Resistant** | 120 | 0.9x | Immune to status effects | Implement |

### Enemy Properties

```cpp
struct EnemyStats {
    int hpMax;              // Maximum health
    float speed;            // Movement multiplier
    float physicalResist;   // Damage reduction (0-1)
    float dodgeChance;      // Chance to avoid hit (0-1)
    bool statusImmune;      // Ignores burn/slow/etc
    bool flying;            // Ignores pathfinding obstacles
    int attackDamage;       // Damage to cannons
    float attackRange;      // Range to attack cannons
    float attackSpeed;      // Attacks per second
    int bounty;             // Coins on kill
};
```

### Enemy Attack System

- Enemies attack cannons when within `attackRange`
- Attack while moving (no stopping)
- Prioritize nearest cannon in range
- Attack animation: Quick melee swipe

| Enemy Type | Attack Damage | Attack Range | Attack Speed |
|------------|---------------|--------------|--------------|
| Regular | 10 | 0.5 cells | 1.0/sec |
| Fast | 5 | 0.3 cells | 2.0/sec |
| Tank | 20 | 0.8 cells | 0.5/sec |
| Flying | 8 | 0.5 cells | 1.0/sec |
| Dodger | 8 | 0.4 cells | 1.5/sec |
| Resistant | 15 | 0.6 cells | 0.8/sec |

### Movement System

Existing `mov::Movements` class handles:
- Grid-to-local coordinate conversion
- Smooth movement between cells
- Queue-based direction changes
- Edge detection for spawn/exit

**Enhancement needed:**
- A* pathfinding integration
- Flying enemy wave pattern
- Dynamic path recalculation

---

## 8. Combat & Status Effects

### Damage Types

| Type | Description | Resisted By |
|------|-------------|-------------|
| Physical | Gun, Sniper, Rapid, Acid | Tank, Flying (50%) |
| Fire | Burn cannon DoT | Resistant (immune) |
| Ice | Slow effect (no damage) | Resistant (immune) |
| Energy | Laser, Tesla | None |

### Status Effects

| Effect | Source | Duration | Behavior |
|--------|--------|----------|----------|
| **Burning** | Fire Cannon | 3 sec | 5 DPS, orange aura |
| **Slowed** | Ice Cannon | 3 sec | 50% speed reduction, blue aura |
| **Acid** | Acid Cannon | Instant | Splash on impact |

### Effect Interactions

```
Fire + Ice = CANCEL
├── If burning enemy is hit by ice → "DOUSED!" (both removed)
└── If slowed enemy is hit by fire → "THAW!" (both removed)

Effects do NOT stack from same source
Effects DO stack from different sources (up to 2x slow from 2 ice cannons)
```

### Damage Calculation

```cpp
float CalculateDamage(Cannon* cannon, Enemy* enemy) {
    float baseDamage = cannon->damage;

    // Critical hit
    if (Random() < cannon->critChance) {
        baseDamage *= cannon->critMultiplier;
        ShowFeedback("CRITICAL!");
    }

    // Dodge check
    if (Random() < enemy->dodgeChance) {
        ShowFeedback("DODGE!");
        return 0;
    }

    // Resistance
    if (cannon->damageType == Physical) {
        baseDamage *= (1.0 - enemy->physicalResist);
    }

    return baseDamage;
}
```

---

## 9. Economy System

### Core Principle
> Player should always be 10-20% short of "comfortable"

### Income Sources

| Source | Amount | Timing |
|--------|--------|--------|
| Enemy Kill | 5-20 coins (by type) | On death |
| Wave Completion | 30% of next wave cost | End of wave |
| Miner Cannon | 2.5 coins/sec | Continuous |
| Interest (optional) | 5% of banked | Per wave |

### Kill Bounties

| Enemy | Bounty |
|-------|--------|
| Regular | 10 |
| Fast | 5 |
| Tank | 20 |
| Flying | 12 |
| Dodger | 8 |
| Resistant | 15 |

### Miner Cannon Economics

```
Cost: 150 coins
Income: 2.5 coins/sec
Payback Period: 60 seconds

Break-even analysis:
- Level avg duration: 180 sec
- Net profit if placed early: (180 - 60) * 2.5 = 300 coins
- But: No combat value, vulnerable to attacks
- Strategy: Place behind front lines, protect with HP
```

### Sell System

```cpp
int CalculateSellValue(Cannon* cannon) {
    int totalInvested = cannon->baseCost;
    for (Upgrade& u : cannon->upgrades) {
        totalInvested += u.cost;
    }
    return totalInvested * 0.70;  // 70% refund
}
```

### Starting Resources by Level

| Level Range | Starting Cash | Starting HP |
|-------------|---------------|-------------|
| 1-5 | 200-300 | 20 |
| 6-10 | 250-400 | 15 |
| 11-15 | 300-500 | 10 |

---

## 10. Level System

### Level Grid

```
┌─────┬─────┬─────┬─────┬─────┐
│  1  │  2  │  3  │  4  │  5  │  Row 1: Tutorial
├─────┼─────┼─────┼─────┼─────┤
│  6  │  7  │  8  │  9  │ 10  │  Row 2: Intermediate
├─────┼─────┼─────┼─────┼─────┤
│ 11  │ 12  │ 13  │ 14  │ 15  │  Row 3: Expert
└─────┴─────┴─────┴─────┴─────┘
```

### Progression System

- Complete Level N to unlock Level N+1
- Each level has 1-3 star rating based on score
- Stars unlock cosmetic rewards (optional)

### Star Rating Thresholds

```cpp
int CalculateStars(int score, int levelId) {
    LevelData& level = levels[levelId];
    if (score >= level.threeStarScore) return 3;
    if (score >= level.twoStarScore) return 2;
    if (score >= level.oneStarScore) return 1;
    return 0;  // Failed
}
```

### Level File Format (Extended)

```
# Level file format v2
<grid_width> <grid_height>     # Variable dimensions (8x5 to 14x7)
<start_edge> <start_pos>       # Spawn location
<end_edge> <end_pos>           # Exit location
<field_items>                  # Obstacles, decorations
<num_waves>
<wave_data>...                 # Per wave: delay, interval, count, type, texture, power
<starting_cash> <starting_hp>
<one_star_score> <two_star_score> <three_star_score>
<unlocked_cannons>             # Bit flags for available cannon types
```

### Sample Level Configurations

| Level | Grid | Waves | Cash | HP | Cannons Available |
|-------|------|-------|------|-----|-------------------|
| 1 | 8x5 | 3 | 200 | 20 | Gun |
| 5 | 10x6 | 8 | 250 | 20 | Gun, Sniper, Rapid, Fire, Ice |
| 10 | 12x7 | 15 | 350 | 15 | All except Tesla |
| 15 | 14x7 | 25 | 500 | 10 | All |

---

## 11. Pathfinding System

### Algorithm: A* Pathfinding

Replaces existing BFS distance grid with A* for:
- Dynamic obstacle avoidance
- Efficient path recalculation
- Path validation before cannon placement

### Implementation

```cpp
class CPathfindingManager {
public:
    // Find path from start to end avoiding cannons
    std::vector<QPoint> FindPath(QPoint start, QPoint end);

    // Check if placing cannon would block all paths
    bool ValidatePlacement(QPoint cell);

    // Recalculate paths for all enemies
    void InvalidatePaths();

private:
    struct Node {
        QPoint pos;
        float gCost;  // Cost from start
        float hCost;  // Heuristic to end
        float fCost() { return gCost + hCost; }
        Node* parent;
    };

    float Heuristic(QPoint a, QPoint b);  // Manhattan distance
    std::vector<QPoint> GetNeighbors(QPoint pos);
    bool IsWalkable(QPoint pos);
};
```

### Path Validation

```cpp
bool CGame::CanPlaceCannon(QPoint cell) {
    // Temporarily mark cell as blocked
    cannons[cell.x()][cell.y()] = TEMP_BLOCK;

    // Check if any start->end path exists
    bool pathExists = false;
    for (QPoint start : m::startCells) {
        for (QPoint end : m::endCells) {
            if (pathfinder.FindPath(start, end).size() > 0) {
                pathExists = true;
                break;
            }
        }
    }

    // Remove temporary block
    cannons[cell.x()][cell.y()] = nullptr;

    if (!pathExists) {
        ShowFeedback("BLOCKED!");
    }

    return pathExists;
}
```

### Flying Enemy Movement

Flying enemies ignore ground obstacles:

```cpp
bool IsWalkable(QPoint pos, Enemy* enemy) {
    if (enemy->flying) {
        return IsInBounds(pos);  // Only check boundaries
    }
    return IsInBounds(pos) && !HasCannon(pos);
}
```

Flying movement pattern: Subtle wave motion
```cpp
QPointF GetFlyingOffset(float time) {
    float amplitude = 0.1f * CellSize;
    float frequency = 2.0f;
    return QPointF(0, sin(time * frequency) * amplitude);
}
```

---

## 12. UI/UX Design

### Main Menu (CGameMenu)

```
┌────────────────────────────────────────┐
│                                        │
│           TOWER DEFENCE                │
│                                        │
│         ┌──────────────┐               │
│         │   CAMPAIGN   │               │
│         └──────────────┘               │
│         ┌──────────────┐               │
│         │  QUICK PLAY  │               │
│         └──────────────┘               │
│         ┌──────────────┐               │
│         │   SETTINGS   │               │
│         └──────────────┘               │
│         ┌──────────────┐               │
│         │     EXIT     │               │
│         └──────────────┘               │
│                                        │
└────────────────────────────────────────┘
```

### Level Selection (CLevelMenu)

```
┌────────────────────────────────────────┐
│  ← BACK          SELECT LEVEL          │
├────────────────────────────────────────┤
│                                        │
│   ┌───┐  ┌───┐  ┌───┐  ┌───┐  ┌───┐   │
│   │ 1 │  │ 2 │  │ 3 │  │ 4 │  │ 5 │   │
│   │★★★│  │★★☆│  │★☆☆│  │   │  │ 🔒│   │
│   └───┘  └───┘  └───┘  └───┘  └───┘   │
│                                        │
│   ┌───┐  ┌───┐  ┌───┐  ┌───┐  ┌───┐   │
│   │ 6 │  │ 7 │  │ 8 │  │ 9 │  │10 │   │
│   │ 🔒│  │ 🔒│  │ 🔒│  │ 🔒│  │ 🔒│   │
│   └───┘  └───┘  └───┘  └───┘  └───┘   │
│                                        │
│   ┌───┐  ┌───┐  ┌───┐  ┌───┐  ┌───┐   │
│   │11 │  │12 │  │13 │  │14 │  │15 │   │
│   │ 🔒│  │ 🔒│  │ 🔒│  │ 🔒│  │ 🔒│   │
│   └───┘  └───┘  └───┘  └───┘  └───┘   │
│                                        │
└────────────────────────────────────────┘
```

### In-Game HUD

```
┌────────────────────────────────────────────────────────────┐
│ 💰 350    ❤️ 15    📊 Wave 3/10    ⭐⭐☆         [⚙️] [⏸️] │
├────────────────────────────────────────────────────────────┤
│                                                            │
│   Game Field (variable grid)                               │
│                                                            │
│   [Enemies spawn from edges, pathfind to exit]             │
│                                                            │
│   [Cannons placed on grid cells]                           │
│                                                            │
├────────────────────────────────────────────────────────────┤
│ CANNONS:  [Gun] [Sniper] [Rapid] [Fire] [Ice] ...         │
│           $50    $100     $75    $80    $80               │
└────────────────────────────────────────────────────────────┘
```

### Cannon Selection Panel (CCannonSelection)

Appears when clicking empty cell:
```
┌─────────────────────────────────┐
│     Available Cannons           │
├─────────────────────────────────┤
│  [🔫]  [🎯]  [⚡]  [🔥]  [❄️]   │
│   50   100    75    80    80    │
├─────────────────────────────────┤
│  [💀]  [📡]  [⚡]  [⛏️]         │
│  120   150   200   150          │
├─────────────────────────────────┤
│           [Cancel]              │
└─────────────────────────────────┘
```

### Cannon Upgrade Panel (CCannonUpgrade)

Appears when clicking existing cannon:
```
┌─────────────────────────────────┐
│      Gun Cannon (Lv.1)          │
├─────────────────────────────────┤
│  HP: ████████░░ 80/100          │
│  Range: 3.0 cells               │
│  Damage: 15                     │
│  Fire Rate: 1.0/sec             │
├─────────────────────────────────┤
│  [Upgrade $38]  [Sell $35]      │
└─────────────────────────────────┘
```

---

## 13. Camera System

### Feature Flag Controlled
`ENABLE_CAMERA_CONTROLS: bool`

### Controls

| Input | Action |
|-------|--------|
| Mouse Wheel | Zoom in/out (0.5x - 2.0x) |
| Middle Mouse Drag | Pan view |
| Double-click | Reset to default view |

### Implementation

```cpp
class CCameraController {
public:
    void SetZoom(float zoom);      // Clamp 0.5 - 2.0
    void Pan(QPointF delta);       // Offset view
    void Reset();                  // Default position

    QTransform GetTransform();     // For QGraphicsView

private:
    float zoom = 1.0f;
    QPointF offset = {0, 0};

    const float MIN_ZOOM = 0.5f;
    const float MAX_ZOOM = 2.0f;
};
```

### Usage
- Useful for larger grid levels (12x7+)
- Zoom out for strategic overview
- Zoom in to see details/effects
- Disabled by default for simplicity

---

## 14. Feature Flags & Settings

### Settings Autoload

```cpp
// Stored in settings.cfg or QSettings
struct GameSettings {
    // Gameplay Features
    bool ENABLE_CAMERA_CONTROLS = false;
    bool ENABLE_PATHFINDING = true;
    bool ENABLE_CANNON_HP = true;
    bool ENABLE_ENEMY_ATTACKS = true;
    bool ENABLE_MINER_CANNON = true;
    bool ENABLE_SELL_CONFIRMATION = false;

    // Debug Options
    bool DEBUG_SHOW_PATHS = false;
    bool DEBUG_SHOW_RANGES = false;
    bool DEBUG_INFINITE_MONEY = false;
    bool DEBUG_INVINCIBLE_CANNONS = false;
    bool DEBUG_SHOW_FPS = true;

    // Audio
    float MUSIC_VOLUME = 0.5f;
    float SFX_VOLUME = 0.7f;

    // Graphics
    bool ENABLE_PARTICLES = true;
    bool ENABLE_SCREEN_SHAKE = true;
};
```

### Runtime Toggle

Debug flags can be toggled via:
- Settings menu (production flags)
- Console commands (debug flags)
- Keyboard shortcuts (development)

---

## 15. Balance Targets

### DPS Reference Table

| Cannon | Base DPS | Upgraded DPS | Notes |
|--------|----------|--------------|-------|
| Gun | 15 | 30 | Baseline |
| Sniper | 25 | 50 | +20% crit |
| Rapid | 18 | 36 | Consistent |
| Fire | 20 | 40 | +5 DoT DPS |
| Ice | 0 | 0 | Utility only |
| Acid | 12 | 24 | +50% splash |
| Laser | 30 | 60 | Pierce value |
| Tesla | 20 | 40 | Chain value |
| Miner | 0 | 0 | 2.5 coins/sec |

### Wave Scaling

```
Wave N expected enemy HP: Base * (1 + 0.15 * N)
Wave N enemy count: Base + (N * 2)
Wave N reward: Sum(Bounties) + Bonus
```

### Economy Simulation

```
Level 5 Example (10 waves):
- Starting cash: 250
- Total enemy bounties: ~800
- Wave bonuses: ~300
- Miner income (if placed wave 2): ~350
- Total income potential: ~1700

Required spending for survival: ~1500
Margin for error: ~13%  ← Target range
```

### Difficulty Validation Checklist

- [ ] Level completable with optimal play
- [ ] No single cannon dominates
- [ ] Economy forces meaningful choices
- [ ] Status combos rewarded
- [ ] Final waves require full map usage

---

## 16. Implementation Mapping

### Existing Code to Reuse

| Existing Class | New Usage |
|----------------|-----------|
| `CFastCannon` | Base for `CRapidCannon` |
| `CBurnCannon` | Rename to `CFireCannon` |
| `CSlowCannon` | Rename to `CIceCannon` |
| `CMonsterCannon` | Base for `CTankCannon` (heavy) |
| `CFastEnemy` | Reuse directly |
| `IEnemy::move()` | Integrate A* pathfinding |
| `CWaveManager` | Add star scoring |
| `CUserManager` | Add Miner income tracking |
| `CScene` | Add camera transform |

### New Classes Required

| Class | Priority | Description |
|-------|----------|-------------|
| `CPathfindingManager` | High | A* implementation |
| `CStatusEffectManager` | High | DoT and slow processing |
| `CGunCannon` | High | Base cannon type |
| `CSniperCannon` | Medium | Long range + crit |
| `CAcidCannon` | Medium | Splash damage |
| `CLaserCannon` | Medium | Pierce mechanic |
| `CTeslaCannon` | Medium | Chain mechanic |
| `CMinerCannon` | High | Economy generator |
| `CTankEnemy` | Medium | High HP enemy |
| `CFlyingEnemy` | Medium | Ignore obstacles |
| `CDodgerEnemy` | Low | Dodge mechanic |
| `CResistantEnemy` | Low | Status immunity |
| `CSaveManager` | High | Progress persistence |
| `CStarRating` | Medium | UI component |
| `CCameraController` | Low | Zoom/pan |

### Migration Path

1. **Phase 1: Core Mechanics**
   - Rename existing cannons (Burn→Fire, Slow→Ice)
   - Add Gun cannon as new base type
   - Implement cannon HP system
   - Add enemy attacks on cannons
   - Add Miner cannon

2. **Phase 2: Pathfinding**
   - Implement A* pathfinding manager
   - Integrate with enemy movement
   - Add path validation for placement
   - Implement flying enemy bypass

3. **Phase 3: Content**
   - Add remaining cannon types
   - Add remaining enemy types
   - Implement status effect interactions
   - Create 15 levels with progression

4. **Phase 4: Polish**
   - Add star rating system
   - Implement save/load
   - Add camera controls
   - Visual polish and effects

---

## Appendix A: Quick Reference

### Keyboard Shortcuts (Development)

| Key | Action |
|-----|--------|
| F1 | Toggle debug paths |
| F2 | Toggle debug ranges |
| F3 | Toggle infinite money |
| F4 | Toggle invincible cannons |
| ESC | Pause / Menu |
| Space | Fast forward (2x speed) |

### File Locations

| Resource | Path |
|----------|------|
| Levels | `res/<theme>/levels/*.txt` |
| Textures | `res/<theme>/*.png` |
| Sounds | `res/<theme>/sounds/*.mp3` |
| Save Data | `~/.towerdefence/save.dat` |
| Settings | `~/.towerdefence/settings.cfg` |

---

*Document generated for Tower Defence project based on Christmas Defence engine.*
