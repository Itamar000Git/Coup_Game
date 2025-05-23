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
- **Special States**:
  - **Sanction**: Blocks a player from performing actions.
  - **Arrest**: Removes coins from a player or blocks them.
  - **Coup**: Eliminates a player from the game.
- All actions validate legality:
  - Checks if it's the player's turn.
  - Ensures the player has enough coins.
  - Verifies the target is alive and valid.
  - Make sure that the player preforming the actions is alive.
  - make sure there ins't any block that can prevent activate that action.
  - handeling differnt roles acting in a differernt way with the same actions.
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


### Edge Case Testing
- Comprehensive unit tests using `doctest` for all edge cases.
- Handles invalid actions and states with clear error messages (`std::runtime_error`) and a clear text after.

### Multi-Player Support
- Supports 2 to 6 players.
- Enforces unique player names and all game rules for any player count.


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
│   └── Merchant.hpp
├── OBJ/
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
<!-- 
## Tests and Edge Cases

The project includes extensive tests to ensure the game behaves correctly in all scenarios.  
Here is a summary of the tests performed in `test.cpp`:

### Game Initialization
1. Creating a game with fewer than 2 or more than 6 players.
2. Adding a player with a duplicate name.
3. Removing players and checking turn order.

### Turn and Action Logic
1. Ensuring only the correct player can act.
2. Skipping dead players in turn order.
3. Preventing actions out of turn or on dead players.

### Role Abilities
1. Testing each unique action for every role:
   - Governor: Undo tax, sanction.
   - Spy: Watch coins, prevent arrest.
   - Baron: Invest, bribe.
   - General: Undo coup.
   - Judge: Undo bribe.
   - Merchant: Gather with bonus.
2. Validating that sanctions and arrests block actions as intended.
3. Ensuring undo actions work only when allowed.

### Special States
1. Handling of sanction, arrest, and coup.
2. Preventing illegal state transitions (e.g., sanctioning an already sanctioned player).

### Game End and Winner Detection
1. Correctly identifying the winner.
2. Preventing winner queries before the game is over.

### Memory and Resource Management
1. Tests can be run under valgrind to ensure no memory leaks.

---

## Example Edge Cases
1. **Invalid Actions**:
   - Acting out of turn.
   - Targeting dead players.
   - Performing actions without enough coins.
2. **Undo Logic**:
   - Undoing actions when not allowed (e.g., undoing a non-tax action).
3. **Special States**:
   - Sanctioning a player already sanctioned.
   - Arresting a dead player.
4. **Game End**:
   - Attempting to act after the game is over.
5. **Turn Progression**:
   - Skipping dead players and ensuring the c -->