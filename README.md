# Space Invaders 👾

**Space Invaders** is a high-performance C++ recreation of the classic arcade shooter, built from the ground up using the **Raylib** framework. This project emphasizes proper **OOP** principles, a decoupled state machine architecture, and persistent data storage via SQLite.

<br>

---

## 📑 Table of Contents

| Section | Description |
| :--- | :--- |
| [**🚀 Features**](#-features) | Starfield engine, SQLite, and OOP mechanics |
| [**🏗️ Major Classes**](#️-major-classes) | Core architecture and component breakdown |
| [**📂 Project Structure**](#-project-structure) | Directory map and source code organization |
| [**🛠️ Tech Stack**](#️-tech-stack) | C++, raylib, and SQLiteCpp integration |
| [**🔨 Building and Running**](#-building-and-running) | Compilation and execution guide |
| [**📜 License**](#-license) | MIT License and usage details |

---

## 🚀 Features
- **Dynamic Starfield Engine:** A custom-built background system with procedural, twinkling stars and smooth vertical movement.
- **Persistent Data:** Integration with **SQLite** (via SQLiteCpp) to maintain a local database for player game history and global leaderboards.
- **Advanced OOP Architecture:** Modular design with dedicated classes for entities and a decoupled State Machine for menus and gameplay.
- **Classic Gameplay, Modern Tech:** Original mechanics enhanced with high-fidelity rendering and immersive SFX.

---

## 🏗️ Major Classes

| Class | Location | Responsibility |
| :--- | :--- | :--- |
| **`Game`** | `src/code/4_game/` | The central orchestrator. Manages the main game loop, state transitions, and high-level resource lifecycle. |
| **`State`** | `src/code/3_states/` | Abstract interface for all game screens. Subclasses include `Menu`, `Playing`, `Paused`, `GameOver`, etc. |
| **`Aliens`** | `src/code/2_entities/` | Manages the enemy swarm formation, movement logic, and automatic firing mechanics. |
| **`SpaceShip`** | `src/code/2_entities/` | Handles player input, movement, and laser projectile management. |
| **`MotherShip`** | `src/code/2_entities/` | Periodic bonus enemy that traverses the top of the screen with unique reward logic. |
| **`Laser`** | `src/code/2_entities/` | Generic projectile system shared by both players and enemies for consistent collision detection. |
| **`BackGround`** | `src/code/1_core/` | Procedural starfield generator with independent layer movement and twinkling effects. |
| **`DataBase`** | `src/code/1_core/` | Smart wrapper for SQLite3 providing persistent storage for match history and global stats. |

---

## 📂 Project Structure

```
spaceInvaders/
├── src/                    # Source code
│   ├── code/               # Logic implementation
│   │   ├── 1_core/         # Engine core, background, and database
│   │   ├── 2_entities/     # Ship, Alien, Laser, and MotherShip logic
│   │   ├── 3_states/       # State Machine: Menu, Playing, Settings, etc.
│   │   └── 4_game/         # Orchestration and main loop
│   └── assets/             # Raw graphics, audio, and font files
├── build/                  # Generated build artifacts (ignored by git)
├── LICENSE                 # MIT License
└── README.md               # Project documentation
```

---

## 🛠️ Tech Stack

This project leverages modern C++ and lightweight libraries to ensure high performance and cross-platform compatibility.

| Component | Technology | Role in Project |
| :--- | :--- | :--- |
| **Language** | **C++17** | Core logic and OOP architecture. |
| **Graphics** | [**raylib**](https://www.raylib.com/) | 2D rendering and texture management. |
| **Audio** | **raylib-audio** | Low-latency sound effects. |
| **Database** | [**SQLite3**](https://www.sqlite.org/) | Persistent data storage. |
| **DB Wrapper**| [**SQLiteCpp**](https://github.com/SRombauts/SQLiteCpp) | Safe and idiomatic C++ wrapper for SQL. |
| **Build System**| **CMake** | Dependency management and compilation. |

---

## 🔨 Building and Running

### Prerequisites
- **CMake** (3.11 or higher)
- A **C++17 compatible compiler** (GCC, Clang, or MSVC)

### Build Commands
```bash
# Configure the project
cmake -B build

# Build the project
cmake --build build
```

### Execution
- **Linux/macOS:** `./build/spaceInvaders`
- **Windows:** `./build/Debug/spaceInvaders.exe`

---
## 📜 License

This project is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for the full text. 