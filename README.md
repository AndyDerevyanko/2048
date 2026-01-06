<h1 align="center">🟨 2048: Console Edition — A Clean C++ Implementation 🎯</h1>

<p align="center">
    A compact version of 2048 written in C++: originally created to solve a problem on DMOJ titled “2048”, this program supports two different modes—one where you can play the game normally, and another that determines the highest achievable tile across all possible permutations of moves from a given board state.
  <br>
  <a href="https://github.com/AndyDerevyanko/2048/issues">Report Bug / Request Feature</a>
</p>


## 📚 Table of Contents

- [What is 2048?](#what-is-2048)
- [Controls](#controls)
- [Working Demo](#working-demo)
- [Features](#features)
- [Implementation](#implementation)
- [UML Diagrams](#uml-diagrams)
- [Future Improvements (Maybe)](#future-improvements-maybe)

<a id="what-is-2048"></a>
## ❓ What is 2048?

<img src="https://raw.githubusercontent.com/AndyDerevyanko/2048/main/images/2048_logo.png" width="200" align="left">

2048 is a simple numeric sliding-puzzle game. Slide tiles (W/A/S/D) to combine equal numbers into their sum, creating larger and larger powers of two. The goal: build big tiles (2048, 4096, whatever you want) before the board fills and no moves remain.
<br><br><br><br><br><br><br>

<a id="controls"></a>
## 🌟 Controls

**W** - Slide up <br>
**A** - Slide left <br>
**S** - Slide down <br>
**D** - Slide right <br>
**!** - Quit program <br>
**i** - Toggle input mode between *one-by-one* and *series* <br>

<a id="working-demo"></a>
## 🎮 Working Demo

Try out a working demo [here](https://onlinegdb.com/UQdStOBwL).

<p align="left" style="">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/2048/main/images/demo.png" alt="demo" width="300">
</p>

<a id="features"></a>
## 🧩 Features

- Fully working 2048 implementaiton in console with additional input capabilities and a problem-solver (DMOJ 2048 problem)
- Custom-board input to run from any 4x4 state: INCLUDING NON-2 power numbers (ex. you can enter 5 or 7 or 291 for fun)
- Built-in brute-force checker and solver to estimate best reachable max tile
- Compact self-contained OOP design
- Usage of throw/except (stylistic choice)
- Clear console visualization with simple ASCII board printing
- No external dependencies

<a id="implementation"></a>
## 👨‍💻 Implementation

This program uses OOP. As such, it contains a variety of different objects. The board class manages a 4×4 grid and provides all core 2048 mechanics including shifting, combining, move simulation, and random tile spawning, along with utilities for testing and analyzing boards. The test namespace handles input, display, gameplay loops, and includes a brute-force solver that estimates the highest reachable tile. Users can play interactively, feed scripted move sequences, or run preset boards through the solver for analysis. Everything is implemented with simple ASCII console output. 

The board class contains many components, they are summarized below:
- "board" class: This represents the central data structure of the game, containing the int entry `[4][4]` grid and the bool shouldPickRand toggle. It includes basic logic helpers like isempty, issame, combine, and shiftcell
- "shift" and "move" methods: These represent the core mechanical logic; shift(direction) compacts tiles along an axis, while up(), down(), left(), and right() execute a full sequence of shifting, combining equal adjacent tiles, and shifting again
- "movetest" class/logic: This serves as the validation layer, using movetest() and movetestdir(direction) to simulate moves and determine if the board state would change, which is essential for detecting game-over states or move validity
- "utility" helpers: A collection of specific functional tools including zerochecker(), findmax(), and various move-copy routines required for the solver to manipulate temporary board states
- "spawn and I/O" methods: These handle grid population; pickrandcell() manages the random spawning of 2s or 4s (with a 10% chance for a 4), while readtoboard() allows the system to parse specific board states from whitespace-separated numeric input
- "test" namespace: This represents the interface and loop management, containing takeinputonebyone() and takeinputseries() for input handling, and playgame() for the main interactive execution loop
- "solver" and "checker" routines: These represent the analysis tools; checker() uses a brute-force approach to simulate move permutations to find the highest reachable tile, while problemsolve() automates the analysis of five preset board configurations

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/2048/main/images/2048_board.png" alt="2048 board" width="450">
</p>

<a id="uml-diagrams"></a>
## 👨‍👩‍👧‍👦 UML Diagrams
UML Diagrams for each object are available below:


### Board UML Diagram ###
<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/2048/main/images/board_uml.png" alt="board uml" width="600">
</p>

### Testing Namespace UML Diagram ###
<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/2048/main/images/test_uml.png" alt="namespace test uml" width="600">
</p>

<a id="future-improvements-maybe"></a>
## 🔮 Future Improvements (Maybe)
- Adding score tracking and a best-score save/load (simple file write)
- Implementing an undo stack (store last N boards) so player can experiment without losing progress
- Making RNG seed configurable so results are perfectly reproducible (srand(seed)).


