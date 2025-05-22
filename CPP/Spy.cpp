//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>

#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Spy.hpp"

namespace coup{  

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

    void Spy::undo( Player &player){
        std::cout <<"undo with:" << name<< " that is"<< role<<std::endl;
    }


}