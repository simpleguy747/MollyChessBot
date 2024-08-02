# MollyChessBot

## UCI-Compatible Chess Engine

A C implementation of a UCI-compatible chess engine, featuring:

### Position Representation

* 6 + 2 bitboards for efficient piece placement and movement tracking
* Single array of size 64 for representing the chess board

### Search Techniques

* Negamax algorithm with alpha-beta pruning for optimized search

### Move Ordering

* MVV-LVA (Most Valuable Victim - Least Valuable Attacker) ordering for efficient move exploration

### Credits

Special thanks to the Engine Programming community on Discord for their support and guidance in developing this chess engine.

### Features

* UCI-compatible interface for integration with popular chess GUIs
* Efficient position representation using bitboards
* Optimized search using Negamax with alpha-beta pruning
* Improved move ordering using MVV-LVA

### Getting Started

To build and run the engine, follow these steps:

1. Clone the repository: `git clone https://github.com/simpleguy747/MollyChessBot.git`
2. Build the engine: `gcc -o mollychessbot mollychessbot.c`
3. Run the engine: `./mollychessbot`

### License

This project is licensed under the MIT License. See LICENSE.txt for details.

### Contributing

Contributions are welcome! If you'd like to contribute to the MollyChessBot project, please fork the repository and submit a pull request.
