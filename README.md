//itamarbabai98@gmail.com
# Coup Game - C++

## General Explanation
This project implements the board game "Coup" in C++.  
The project includes player management, turn logic, unique roles and actions, a graphical interface (SFML), and handeling edge-case testing.  
Game logic includes error handling, turn management, imlement the game rules.

---

## Features

### Player Management
- Add and remove players dynamically during the game.
- Automatically skip dead players during next turn.
- Enforce player count limits (2-6 players).
- Prevent duplicate player names.
- Check for a winner and handle game over.

### Roles & Actions
- **Roles**: Governor, Spy, Baron, General, Judge, Merchant.
- **General Actions**: All roles can perform actions like `tax`, `gather`, `sanction`, `arrest`, `coup`.
- **Unique Actions**:
  - **Governor**: Undo tax.
  - **Spy**: Show coins of another player and prevent arrest.
  - **Baron**: Invest coins to double them.
  - **General**: Undo a coup.
  - **Judge**: Undo a bribe.
  - **Merchant**:  Have a bonus with any action.
- **Special States**:
  - **Sanction**: Blocks a player from performing actions.
  - **Arrest**: Removes coins from a player or blocks them.
  - **Coup**: Eliminates a player from the game.
- All actions validate the players state before execution:
  - Checks if it's the player's turn.
  - Ensures the player has enough coins.
  - Verifies the target is alive and valid.
  - Make sure that the player preforming the actions is alive.
  - make sure there ins't any block that can prevent activate that action.
  - Handeling a different roles acting in a differernt way with the same actions.
- Throws clear exceptions for illegal actions, such as acting out of turn or targeting dead players.

### Graphical User Interface (SFML)
- A GUI implementation for specific game interactions:
  - Windows for entering the number of players and their names.
  - Displays error messages for invalid actions.
  - Shows the winner at the end of the game.
  - Enable to choose the player name that is the target of the action.
  - Show player turn name, and last arrested player name.
  - Show if there is any sanction , block to bride or prevent arrest on any player.
- Interactive interface with buttons and input fields.

---

## Compiler and Build Instructions

- **Dependencies**:
#### for downloading the SFML GUI:

  ```bash
  sudo apt install libsfml-dev
  ```
#### For using it you need to make sure you have this libraries:
- #include <SFML/Graphics.hpp>
- #include <SFML/Window.hpp>

- **Compiler**: `g++`

- **Build and Run Example**:
  ```bash
  make Main
  ```
- **Run Tests**:
  ```bash
  make Test
  ```
  - **Clean**:
  ```bash
  make clean
  ```
  - **Run valgrined**:
  ```bash
  make valgrined
  ```

## Project Structure
```bash
Coup_game/
├── CPP/
│   ├── Game.cpp
│   ├── Player.cpp
│   ├── Governor.cpp
│   ├── Spy.cpp
│   ├── Baron.cpp
│   ├── General.cpp
│   ├── Judge.cpp
│   └── Merchant.cpp
├── HPP/
│   ├── Game.hpp
│   ├── Player.hpp
│   ├── Governor.hpp
│   ├── Spy.hpp
│   ├── Baron.hpp
│   ├── General.hpp
│   ├── Judge.hpp
│   ├── main.hpp
│   └── Merchant.hpp
├── OBJ/
├── Demo.cpp
├── test.cpp
├── main.cpp
├── doctest.h
├── README.md
└── makefile
```

### Game Class
- **Purpose**: Manages the overall game state, including the list of players, turn order, and player turn.
- **Main role**:
  - Add and remove players.
  - Manage turn progression, skipping dead players.
  - Check for a winner and handle game over scenarios.
  - Validate actions based on the current game state.
- **Key Methods**:
  - `addPlayer(Player* player)`: Adds a player to the game.
  - `removePlayer(Player* player)`: Removes a player from the game.
  - `turn()`: Returns the name of the player whose turn it is.
  - `nextTurn()`: Advances the turn to the next player.
  - `winner()`: Returns the name of the winner if the game is over.

### Player Class
- **Purpose**: Represents a player in the game, including their role, coins, and state (alive or dead).
- **Main role**:
  - Track the player's coins and state.
  - Proform as a base class that implement the base actions.
  - Perform general actions like `tax`, `gather`, `coup`, `sanction`, `arrest`,`skip`.
  - Validate actions based on the player's state and role.
- **Key Methods**:
  - `tax()`: Collects coins for the player.
  - `gather()`: Gathers coins for the player.
  - `coup(Player* target)`: Eliminates another player.
  - `sanction(Player* target)`: Blocks another player from performing actions.
  - `arrest(Player* target)`: Removes coins from another player or blocks them.
  - `skip()`: Skips the player's turn.

### Governor Class (Inherits from Player)
- **Unique actions**:
  - `undo(Player* target)`: Reverses the last tax action of another player.
  **Override**:
  - `tax()`: Overrides the base tax method to include unique logic for the Governor role.

### Spy Class (Inherits from Player)
- **Unique actions**:
  - `watchNumOfCoins(Player* target)`: Reveals the number of coins another player has.
  - `preventArrest(Player* target)`: Prevents a player from being arrested.

### Baron Class (Inherits from Player)
- **Unique actions**:
  - `invest()`: Doubles the player's coins.
**Override**:
  - `gather()`: Overrides the base gather method to include unique logic for the Baron role.
  - `tax()`: Overrides the base tax method to include unique logic for the Baron role.

### General Class (Inherits from Player)
- **Unique actions**:
  - `undo(Player* target)`: Reverses a coup action performed on another player.
  **Override**:
  - `setIsAlive(bool alive)`: Overrides the base method to include unique logic for the General role.

### Judge Class (Inherits from Player)
- **Unique actions**:
  - `undo(Player* target)`: Reverses a bribe action performed on another player.

### Merchant Class (Inherits from Player)
- **Override**:
  - `starter()`: Overrides the base gather method to include unique logic for the Merchant role.

---

## Tests and Edge Cases

The project includes extensive tests to ensure the game behaves correctly in all scenarios.  
Here is a summary of the tests performed in `test.cpp`:

### Game Initialization
1. Creating a game with fewer than 2 or more than 6 players.
2. Adding a player with a duplicate name.
3. Trying to get the winner before the game is over.
4. Removing a player and checking the turn order.
5. Checking the turn order.

### Player Actions
1. Validating that players can only perform actions on their turn.
2. Trying to perform gather or tax actions after being sanctioned.
3. Trying to preform action that is not coup with more than 10 coins.
4. Ensuring players cannot perform actions when dead.
5. Validating that players cannot perform actions on dead players.

### Role Abilities

### Spy Actions
1. Testing the Spy's ability to watch another player's coins.
2. Ensuring the Spy can prevent another player from being arrested.
3. Validate that the same player cannot be arrested twice in a row.
### Baron Actions
1. Testing the Baron's ability to invest coins without enough coins.
2. Checking if the invest method works correctly.
3. Checking if the tax method works correctly for the Baron.
### Governor Actions
 1. Checking if the tax method works correctly for governor.
 2. Checking if the undo method works correctly for governor.
 3. Checking if the undo method works correctly when there is not enough coins.
 4. Checking if the undo method works correctly when the last move is not tax.
### Merchant Actions
1. Testing the Merchant's ability to gather coins with a bonus.
2. Checking if merchant pay 2 coins after arrest.
### Judge Actions
1. Testing the Judge's ability to undo a bribe.
2. Checking if sanction a judge cost 4 coins.
3. Checking if the bribe method blocked after undo.
### General Actions
1. Testing the General's ability to undo a coup.
2. Checking if the arrest method not effective on general

---

## Example Edge Cases
1. **Soft Locks**:
   - Players unable to perform actions because they are blocked and prevented to arrest and do not have enough coins.
   - Players with no valid actions left can skip their turn.

2. **Multiple Bribes**:
   - Players can Bribe multiple times, but the it's not a profitable action.

3. **Dead Players**:
   - Ensuring dead players cannot perform actions.
   - Skipping dead players in turn order.
   - Preventing actions on dead players.

4. **Turn Order**:
   - Ensuring the game correctly continues with the next alive player.

5. **Invalid Undo Actions**:
   - Ensuring that undo actions are only performed when valid.

6. **General Self-Undo**:
   - Ensuring the General can save themselves from a coup if they have enough coins.

7. **Self-Action**:
   - Ensuring players cannot perform actions on themselves.
  
8. **No Coins**:
   - Players with no coins cannot perform certain actions.

9. **Undo After Coup**:
   - Ensuring that undo actions cannot be performed after a coup.

10. **Multiple Undo Actions**:
    - Ensuring that only the last action can be undone, and that it is valid.