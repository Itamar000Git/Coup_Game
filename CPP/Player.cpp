//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <vector>
#include "../HPP/Game.hpp"
#include "../HPP/Player.hpp"
#include <cstring>

namespace coup
{  

    // void Player::deleteLastMove(){
    //     if (lastMove.empty()) {
    //         throw std::runtime_error("No moves to delete.");
    //     }
    //     std::string last= lastMove.back();
    //     lastMove.pop_back();
    //     if(last=="gather"){
    //         coinsNum--;
    //     }
  
    // }
    //  Player::Player() {

    //  }


    // std::string Player::getName(){
    //     //return name;
    // }
    // bool Player::isAlive(){
     
    // }

    // int Player::coins() const{//returns the number of coins the player has
      
    // }

    // void Player::undo(const Player &player){}//need to implement in the inharitance

  
    void Player::gather(){
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
        starter();
        if(blockToBride==true){
            setPreventToBride(false);
            freeMoves=0;
            game.nextTurn();
            
            lastMove.push_back("gather");
            throw std::runtime_error("You are blocked by bride");
            return;
        }
        lastcoinsNum=coinsNum;
        coinsNum++; //need to add check if there is a block
        std::cout <<"gather with: " << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
    
        lastMove.push_back("gather");
    }
    // void Player::tax(){}

    // void Player::bride(){}
    // void Player::arrest(){};
    // void Player::sanction(){}
    // void Player::coup(){}



}