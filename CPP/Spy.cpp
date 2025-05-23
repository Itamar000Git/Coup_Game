//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>

#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Spy.hpp"

namespace coup{  

    /**
     * @brief Constructor for the Spy class.
     * @param game The game instance.
     * @param name1 The name of the player.
     */
    Spy::Spy(Game &game1, const std::string &name1)
        : Player(game1, name1) { 
        this->role = "Spy"; 
        playerIndex= game.getNumOfPlayers();
        game.addPlayer(this); 
        Alive = true;
        coinsNum = 0;   
        playerTurn = 0;
        
        isBlocked = false;
        freeMoves=0;
        blockToBribe=false;
        preventToArrest=false;
    }

    int Spy::coins() const{//returns the number of coins the player has
        return coinsNum;
     }
     std::string Spy::getName(){
        return name;
     }
        std::string Spy::getRoll(){
            return role;
        }

    /**
     * @brief The player cant undo a move
     * @param player The player to be undo the last move
     * @throws std::runtime_error this player cant undo a move
     */
    


}