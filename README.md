Tic-Tac-Toe NxM Game
This is a simple implementation of the classic Tic-Tac-Toe game using the GTK+ library in C. Unlike the traditional 3x3 grid, this version allows for a customizable grid size, making it an NxM grid where players aim to align N symbols in a row to win.

Features
NxM Grid: Play on a grid of custom size.
Turn-based Play: Players take turns to place their symbols (X or O) on the grid.
Win Detection: The game detects when a player aligns N symbols in a row horizontally, vertically, or diagonally to declare a winner.
Reset and Restart: You can reset the game or restart with a different grid size.
Requirements
GTK+ 3: Ensure you have GTK+ 3 installed on your system to compile and run this application.
Usage
Compilation: Use a C compiler to build the application. For example:

css
Copy code
gcc -o tictactoe tictactoe.c `pkg-config --cflags --libs gtk+-3.0`
Execution: Run the compiled executable:

bash
Copy code
./tictactoe
Gameplay: Follow on-screen instructions to set the grid size and play the game.

Controls
Mouse Click: Click on the grid cells to place your symbol.
Structure
tictactoe.c: Contains the main C code for the Tic-Tac-Toe game.
README.md: This file, providing information and instructions for the application.
Contributing
Feel free to contribute to this project by forking it, making improvements, and creating a pull request.

License
This project is licensed under the MIT License - see the LICENSE file for details.
