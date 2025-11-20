# Terminal Tetris
Tetris written entirly in C for the terminal.

---

## Requirements:
- The user must be using a UNIX-based machine.
- Terminal Tetris will not work on Windows.
- NVIDIA GeForce RTX 5090  
  *JK JK 😂*
---

## How to play:
Clone the repository  
Compile with: gcc *.c -o game -pthread or gcc -DEASY_MODE *.c -o game -pthread for easy mode.  
Then run the program!

---

## Controles:
- a: move piece left.
- d: move piece right.
- s: lower piece to bottom of the board.
- q: rotate piece left.
- e: rotate piece right.
- esc: quit

---

## Score:
- 1 Row: 100 points
- 2 Rows: 250 points
- 3 Rows: 500 points
- Tetris: 1000 points

---

## Levels:
- 0-999 points: Fall rate of one block per second.
- 1000-2499: Fall rate of one block per 0.8 seconds.
- 2500-5999: Fall rate of one block per 0.6 seconds.
- 6000-9999: Fall rate of one block per 0.4 seconds.
- 10000-19999: Fall rate of one block per 0.2 seconds.
- 20000 and beyond: Fall rate of one block per 0.1 second (good luck).

## Don't like the scoring or the gravity?
Go ahead and change the source code!
The gravity tick rates are found at the top of game.c.
The level cut offs are found at the bottem of game.c in the update_fall_tick_rate function.
