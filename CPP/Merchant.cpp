//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>

#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Merchant.hpp"

namespace coup{  

    /**
     * @brief Constructor for the Merchant class.
     * @param game The game instance.
     * @param name1 The name of the player.
     */
    Merchant::Merchant(Game &game1, const std::string &name1)
    : Player(game1, name1) { 
        this->role = "Merchant"; 
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


    int Merchant::coins() const{//returns the number of coins the player has
        return coinsNum;
     }
     std::string Merchant::getName(){
        return name;
     }
    std::string Merchant::getRoll(){
        return role;
     }

    
   
   

}