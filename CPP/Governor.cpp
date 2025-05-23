//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>

#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Governor.hpp"
#include "../HPP/Baron.hpp"

namespace coup{  
    /**
     * @brief Constructor for the Governor class.
     * @param game1 The game instance.
     * @param name1 The name of the player.
     */
   Governor::Governor(Game &game1, const std::string &name1)
   : Player(game1, name1) { 
       this->role = "Governor"; 
       playerIndex= game.getNumOfPlayers();
       game.addPlayer(this); 
       Alive = true;
       coinsNum = 0;   
       playerTurn = 0;
       isBlocked = false;
       blockToBribe = false;
       preventToArrest = false;
       freeMoves=0;
   }


    int Governor::coins() const{//returns the number of coins the player has
        return coinsNum;
     }
     std::string Governor::getName(){
        return name;
     }
    std::string Governor::getRoll(){
        return role;
     }

    /**
     * @brief Undo the last move of the player if it was tax.
     * @param player The player whose last move is to be undo.
     * @throws std::runtime_error if the player is dead (both) or there is no last move to undo,
     * if the last move is not tax, if the player has less than 2 coins.
     */
    void Governor::undo( Player &player){
        if(getIsAlived()==false){ //the player is dead
            throw std::runtime_error("You cant coup a dead player");
            return;
        }
        if(player.getIsAlived()==false){ //the other player is dead
            throw std::runtime_error("You cant undo a dead player");
            return;
        }
        if(this==&player){ //the player undo himself
            throw std::runtime_error("You cant arrest yourself");
        }
        if(player.getLastMove().empty()){ //there is no last move to undo
            throw std::runtime_error("There is no last move to undo");
            return;
        }
        std::string last = player.getLastMove().back();
        if(last!="tax"){ //the last move is not tax
            throw std::runtime_error("Governor can only undo tax");
            return;
        }
        if(player.getRoll()=="Baron"){ // undo tax for baron is different
            int num = player.getLastCoinNum(); //get the last coins number
            
            std::cout<<"num is: "<<num<<std::endl;
            player.setLastCoinNum(num); //set the last coins number to the baron
            std::cout<<"baron coins: "<<player.coins()<<std::endl;
        }
        else{
            if(player.coins()<2){
                throw std::runtime_error("Player dont have enough coins");
                return;
            }

            player.setLastCoinNum(player.coins()-2); //undo tax -2 coins

        }
       
        player.setLastMove("undo tax");
        std::cout <<"undo with: " << name<< " that is "<< role<<std::endl;
    }

    /**
     * @brief Override the Tax method add 3 coins to the player if he is governor.
     * @throws std::runtime_error if its not the player's turn, if the player has too many coins,
     * if the player is blocked by bribe or if the player is blocked.
     */
    void Governor::tax(){

        if(game.turn()!=name){ //this is not the player's turn
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(coinsNum>=10){ //the player has more than 10 coins
            throw std::runtime_error("You have too many coins you need to coup");
            return;
        }
        if(isBlocked==true){ //the player is blocked
            throw std::runtime_error("You are blocked");
            return;
        }
        if(preventToArrest==true){ //if the player is blocked by arrest we remove the block
            setPreventToArrest(false);
        }

        if(blockToBribe==true){ //if the player is blocked by bribe we remove the block and set the free moves to 0 and move to the next player
            setPreventToBribe(false);
            game.nextTurn();
            freeMoves=0;
            lastMove.push_back("tax");
            throw std::runtime_error("You are blocked by bribe");
            return;
        }
        coinsNum+=3; //tax 3 coins from the bank with governor
        std::cout <<"tax with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
        lastMove.push_back("tax");
    }
  
}