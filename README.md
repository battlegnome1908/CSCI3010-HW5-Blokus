# Blokus Remastered — C++ Qt Desktop Game

**Blokus Remastered** is a full-featured digital version of the classic board game *Blokus*, implemented in modern C++ with the Qt framework. This project recreates core gameplay mechanics while introducing new interactive abilities, a responsive GUI, and multiplayer support — showcasing skills in object-oriented design, Qt event handling, and game logic systems.

---

## 🚀 Features

- 🎮 **Multiplayer Turn-Based Play**  
  Supports 2–4 players with alternating turns and color-coded boards.

- 🧩 **Drag-and-Drop Piece Placement**  
  Real-time previews, snappable placement, and visual feedback.

- 🔁 **Piece Rotation**  
  Rotate pieces using the `R` key or mouse wheel.

- 🧠 **Rule Enforcement**  
  Includes Blokus-specific rules such as corner-only connections and edge avoidance.

- 🎨 **Custom UI Design**  
  Built with Qt Designer and QGraphicsScenes for polished interactions.

- 🧱 **Modular Architecture**  
  Separation of logic and UI across `Shape`, `Board`, `Player`, and `Game` classes.

- 🧪 **Extensible Ability System** *(in progress)*  
  System planned for introducing special powers like:
  - **Bomb**: Clear a 3x3 area.
  - **Mirror**: Copy a shape.
  - **Wildcard**: Build your own 3x3 shape.

---

## 🛠️ Tech Stack

- **Language**: C++17  
- **Framework**: Qt 6  
- **UI**: Qt Designer, QGraphicsView  
- **Architecture**: OOP, event-driven design  
- **Version Control**: Git

---

## 📁 Project Structure

| File | Description |
|------|-------------|
| `main.cpp` | Application entry point |
| `PlotWindow` | GUI window, board and tray rendering |
| `Shape`, `ShapeItem`, `ShapeFactory` | Data and rendering for player pieces |
| `Board` | Manages tile grid and placement validation |
| `Player` | Tracks pieces placed and remaining |
| `Game` | Turn management and player rotation |

---

## 🧪 Playtesting & Design

User-tested through both physical prototypes and in-app gameplay:

- **Abilities** were prototyped with cards, dice, and mock-up shapes.
- Feedback from users led to improvements in clarity, pacing, and feature prioritization.
- Lessons learned:
  - Remove manual math from gameplay.
  - Speed matters; make placement intuitive and quick.
  - Abilities should have clear trade-offs and costs.

---

## 🧭 Roadmap

- [ ] Finalize and test ability system
- [ ] Add player scoring and game-end logic
- [ ] Dynamically scale board to player count
- [ ] Build leaderboard and stat tracking
- [ ] Complete the full 21-piece set with randomized piece distribution

---

## 📸 Screenshots

<img width="567" height="456" alt="image" src="https://github.com/user-attachments/assets/a1209135-bbf8-41d2-9117-a247807f4e9e" />
<img width="1288" height="758" alt="image" src="https://github.com/user-attachments/assets/a6aa3429-960c-46a7-ac7d-0dae2a5a73d8" />


---

## 🙋‍♂️ About the Developer

Hi, I'm a computer science major and Army veteran at CU Boulder. This project was built for **CSCI 3010: Intensive Programming Workshop** as a creative twist on a classic strategy game. I’m especially passionate about clean architecture, gameplay systems, and polished user experience.

If you’re a potential employer or collaborator interested in Qt development, C++, or systems-level design — I’d love to connect.

---

## 📄 License

This project is open-source and free to use for educational purposes. If you'd like to build on it or adapt it, please reach out or fork the repository.

