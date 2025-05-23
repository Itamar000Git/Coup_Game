//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>

#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Judge.hpp"

namespace coup{  
    /**
     * @brief Constructor for the Judge class.
     * @param game The game instance.
     * @param name1 The name of the player.
     */
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

    /**
     * @brief The player can undo the last move of another player if its a bribe, once the bribe player start the 
     * actions that he bribe, the judg can't undo it.
     * @param player The player to be undo the last move
     * @throws std::runtime_error if the player is dead (each one), if there is no last move to undo,
     *  if the last move is not bribe.
     */
    void Judge::undo( Player &player){ //if the last move is bribe we can undo it and set the block to bribe
        if(getIsAlived()==false){ //the player is dead
            throw std::runtime_error("You cant undo a dead player");
            return;
        }
        if(player.getIsAlived()==false){//the other player is dead
            throw std::runtime_error("You cant undo a dead player");
            return;
        }
        if(this==&player){ //the player undo himself
            throw std::runtime_error("You cant arrest yourself");
        }
        if(player.getLastMove().empty()){//there is no last move to undo
            throw std::runtime_error("There is no last move to undo");
            return;
        }
        std::string last = player.getLastMove().back();
        std::cout<<"last move is: "<<last<<std::endl;
        if(last!="bribe"){ //the last move is not bribe
            throw std::runtime_error("Judge can only undo bribe");
            return;
        }
        player.setPreventToBribe(true); //set the player as blocked to bribe
        
        player.setLastMove("undo bribe");
        std::cout <<"undo with:" << name<< "that is"<< role<<std::endl;
    }
    
    
    /**
     * @brief The player can set the block to bribe to true, so the player can't bribe.
     * @param num The player to be blocked
     */
    void Judge::judgPreventBribe(Player &player){
        player.setPreventToBribe(true);
    }

}