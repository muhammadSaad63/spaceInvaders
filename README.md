# Space Invaders 👾

**Space Invaders** is a high-performance C++ recreation of the classic arcade shooter, built from the ground up using the **Raylib** framework, this project emphasizes proper **OOP** principles and robust state management.

<br> 

---


## 📑 Table of Contents

| Section | Description |
| :--- | :--- |
| [**🚀 Features**](#-features) | Overview of Starfield engine, SQLite, and OOP mechanics |
| [**📂 Project Structure**](#-project-structure) | Directory map and source code organization |
| [**🛠️ Tech Stack**](#️-tech-stack) | Deep dive into C++, raylib, and SQLiteCpp integration |
| [**📜 License**](#-license) | MIT License and open-source usage details |

<br><br>    

---

## 🚀 Features
- **Dynamic Starfield Engine:** A custom-built background system with procedural, twinkling stars and smooth vertical movement.
- **Persistent Data:** Integration with **SQLite** (via SQLiteCpp) to maintain a local database for player game history and global leaderboards.
- **Advanced OOP Architecture:** Modular design with dedicated classes for entities (SpaceShip, Aliens, Lasers) and a decoupled State Machine for menus and gameplay.
- **Classic Gameplay, Modern Tech:** Original mechanics enhanced with high-fidelity rendering and immersive SFX.

---

## 📂 Project Structure

```
spaceInvaders/
├── src/                    # Source code
│   ├── core/               # Engine core, background, and database wrappers
│   ├── entities/           # Ship, Alien, Laser, and MotherShip logic
│   ├── states/             # Game states: Menu, Playing, Settings, History
│   └── main.cpp            # Application entry point
├── assets/                 # Graphics, Audio, and .db files
├── LICENSE                 # MIT License
└── README.md               # Project documentation
```

---

## 🛠️ Tech Stack

This project leverages modern C++ and lightweight libraries to ensure high performance and cross-platform compatibility.

| Component | Technology | Role in Project |
| :--- | :--- | :--- |
| **Language** | **C++17** | Core logic, OOP architecture, and memory management. |
| **Graphics** | [**raylib**](https://www.raylib.com/) | 2D rendering, textures, and the procedural starfield. |
| **Audio** | **raylib-audio** | Low-latency sound effects and background music. |
| **Database** | [**SQLite3**](https://www.sqlite.org/) | Persistent storage for high scores and player history. |
| **DB Wrapper**| [**SQLiteCpp**](https://github.com/SRombauts/SQLiteCpp) | Smart C++ wrapper for safe and easy SQL queries. |
| **Build System**| **CMake** | Managing dependencies and cross-platform compilation. |

---

## 📜 License

This project is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for the full text. 

> "Space Invaders: A tribute to the golden age of arcades, rebuilt with the precision of modern C++."