//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>

#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Merchant.hpp"

namespace coup{  

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

    void Merchant::undo( Player &player){
        std::cout <<"undo with:" << name<< "that is"<< role<<std::endl;
    }
   

}