//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>

#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Judge.hpp"

namespace coup{  

    Judge::Judge(Game &game1, const std::string &name1): Player(game1, name1) { 
        this->role = "Judge"; 
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

    int Judge::coins() const{//returns the number of coins the player has
        return coinsNum;
     }
     std::string Judge::getName(){
        return name;
     }
        std::string Judge::getRoll(){
            return role;
        }

    void Judge::undo( Player &player){ //if the last move is bribe we can undo it and set the block to bribe
        if(player.getIsAlived()==false){
            throw std::runtime_error("You cant undo a dead player");
            return;
        }
        if(player.getLastMove().empty()){
            throw std::runtime_error("There is no last move to undo");
            return;
        }
        std::string last = player.getLastMove().back();
        std::cout<<"last move is: "<<last<<std::endl;
        if(last!="bribe"){
            throw std::runtime_error("Judge can only undo bribe");
            return;
        }
        player.setPreventToBribe(true);
        
        player.setLastMove("undo bribe");
        std::cout <<"undo with:" << name<< "that is"<< role<<std::endl;
    }
    
    

    void Judge::judgPreventBribe(Player &player){
        player.setPreventToBribe(true);
    }

}