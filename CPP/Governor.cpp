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

    void Governor::undo( Player &player){
        
        if(player.getIsAlived()==false){
            throw std::runtime_error("You cant undo a dead player");
            return;
        }
        if(player.getLastMove().empty()){
            throw std::runtime_error("There is no last move to undo");
            return;
        }
        std::string last = player.getLastMove().back();
        if(last!="tax"){
            throw std::runtime_error("Judge can only undo bribe");
            return;
        }
        if(player.getRoll()=="Baron"){ // undo tax for baron is different

            Baron &baron = static_cast<Baron&>(player);
            int num = baron.getLastCoinNum(); 
            if(num<2){
                throw std::runtime_error("Player dont have enough coins");
                return;
            }
            std::cout<<"num is: "<<num<<std::endl;
            baron.setLastCoinNum(num);
            std::cout<<"baron coins: "<<baron.coins()<<std::endl;
        }
        else{
            if(player.coins()<2){
                throw std::runtime_error("Player dont have enough coins");
                return;
            }

            player.setLastCoinNum(player.coins()-2); //undo tax -2 coins
        }
       

        std::cout <<"undo with: " << name<< " that is "<< role<<std::endl;
    }

    /**
     * The governor can tax 3 coins from the bank
     */
    void Governor::tax(){

        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            return;
        }
        if(isBlocked==true){
            throw std::runtime_error("You are blocked");
            return;
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }

        if(blockToBribe==true){
            setPreventToBribe(false);
            game.nextTurn();
            freeMoves=0;
            lastMove.push_back("tax");
            throw std::runtime_error("You are blocked by bribe");
            return;
        }
        coinsNum+=3; 
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