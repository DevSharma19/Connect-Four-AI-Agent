# Connect 4 Minimax AI

An experimental C++ implementation of **minimax-based AI agents** for the game *Connect 4*, exploring optimization techniques such as **bitboards**, **alpha-beta pruning**, and **transposition tables**.

---

## 🧠 Overview
This project investigates how different enhancements to the **minimax algorithm** affect performance in a zero-sum game environment.  
The goal is to evaluate the extent to which **bitboard representations**, **alpha-beta pruning**, and **transposition tables** can improve both **speed** and **accuracy** of a Connect 4 AI agent.

Originally developed in **2023** by **Dev Sharma**.

---

## 🎯 Research Context
> The minimax algorithm is a decision-making system used in zero-sum games — situations where one player’s gain is the other’s loss.  
> It systematically searches through possible moves to find the optimal outcome, but becomes computationally expensive in large search spaces.  
> This project experimentally measures improvements in the holistic performance of minimax through optimization techniques in the context of *Connect 4*.

---

## ⚙️ Implementation
The project implements multiple agent variants:
- `AgentHuman` — human player interface.
- `AgentMinimaxAB` — minimax with alpha-beta pruning.
- `AgentMinimaxTT` — minimax with transposition tables.
- `AgentMinimaxBase` — baseline (unoptimized) minimax.

Supporting components:
- `BoardState` — represents the Connect 4 board and rules.
- `resources/` — contains input assets or lookup data.
- `CMakeLists.txt` — build configuration file.

---

## 🏗️ Project Structure
```
Connect4-Minimax/
├── AgentHuman.cpp / .h
├── AgentMinimaxAB.cpp / .h
├── AgentMinimaxTT.cpp / .h
├── AgentMinimaxBase.cpp / .h
├── BoardState.cpp / .h
├── main.cpp
├── resources/
├── CMakeLists.txt
└── .gitignore
```


---

## 🚀 Building and Running

### Prerequisites
- C++17 or later  
- CMake (v3.15+)  
- Any compatible compiler (e.g., g++, clang++, MSVC)

### Build
```bash
mkdir build && cd build
cmake ..
make
```

### Run
```
./connect4_minimax
```

---

## 📊 Evaluation and Testing

Each agent variant can be benchmarked against others to measure:
- Computation time per move
- Depth of search achieved
- Memory usage
- Game win rates

---

## 🧩 Future Work

- Implement parallelized minimax for deeper search.
- Add neural evaluation heuristics.
- Visualize search tree exploration metrics.

---

## 👤 Author

Dev Sharma
Originally developed in 2023.
Published to GitHub in 2025 for archival and educational purposes.

---

## 📜 License

This project is released under the MIT License.
