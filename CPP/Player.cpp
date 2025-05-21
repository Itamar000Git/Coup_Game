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

    //player& Player::operator=(const Player &player){

/**
 * 
 */
    void Player::gather(){
    
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
        }
        if(isBlocked==true){
            throw std::runtime_error("You are blocked");
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }

        
        if(blockToBribe==true){
            setPreventToBribe(false);
            freeMoves=0;
            game.nextTurn();            
            lastMove.push_back("gather");
            throw std::runtime_error("You are blocked by bribe");
        }
        starter();
        //lastcoinsNum=coinsNum;
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

      void Player::tax(){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
        }
        if(isBlocked==true){
            throw std::runtime_error("You are blocked");
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
        }
        starter();

        coinsNum+=2; 
        std::cout <<"tax with:" << name<< " that is"<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }  
        lastMove.push_back("tax");
     }

    void Player::bribe(){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            
        }
        if(coinsNum<=3){
            throw std::runtime_error("You dont have enough coins");
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(isBlocked==true){
            setIsBlocked(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            freeMoves=0;

            game.nextTurn();
            
            lastMove.push_back("bribe");
            throw std::runtime_error("You are blocked by bribe");
        }
        starter();
        coinsNum=coinsNum-4;
        freeMoves=1;
        lastMove.push_back("bribe");

        std::cout <<"bride with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
    }
  

        void Player::arrest( Player &player){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            
        }
        if(preventToArrest==true){
            throw std::runtime_error("You are blocked");
        }
        if(player.getName()==game.lastArrested()){
            throw std::runtime_error("You cant arrest the same player twice");
        }
        if(player.getIsAlived()==false){
            throw std::runtime_error("You cant arrest a dead player");
        }
        int num=player.coins();
        if(num==0){
            throw std::runtime_error("You cant arrest a player with 0 coins");
        }
        if(isBlocked==true){
            setIsBlocked(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            freeMoves=0;
            game.nextTurn();
            lastMove.push_back("arrest");
            throw std::runtime_error("You are blocked by bribe");
        }
        starter();
        if(player.getRoll()=="General"){ //General get his coins back
           
            std::cout<<"General get his coins back"<<std::endl;
        }
        else if(player.getRoll()=="Merchant"){
            if(num==1){
                throw std::runtime_error("You dont have enough coins to arrest Merchent ");
            }
            player.setLastCoinNum(num-2);
        }
        else{
            player.setLastCoinNum(num-1);
            coinsNum=coinsNum+1;
        }
        starter();
        game.setLastArrest(player.getName());
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
        lastMove.push_back("arrest");
        std::cout << name<< " that is "<< role<<" arrest : "<< player.getName() <<" that is: "<< player.getRoll()<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
      
        
    }


        void Player::sanction( Player &player){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            
        }
        if(player.getIsAlived()==false){
            throw std::runtime_error("You cant sanction a dead player");
        }        
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(isBlocked==true){
            setIsBlocked(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            freeMoves=0;
            game.nextTurn();
            lastMove.push_back("arrest");
            throw std::runtime_error("You are blocked by bribe");
        }
        int num=player.coins();
        int lim=3;
        if(player.getRoll()=="Judge"){
            lim=4;
        }
        if(num<lim){
            throw std::runtime_error("You dont have enough coins");

        }
        // if(player.getRoll()=="Baron"){ 
        //     player.setLastCoinNum(player.coins()+1);
        // }
        coinsNum=coinsNum-lim;
        player.setIsBlocked(true);

        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
        lastMove.push_back("sanction");

        std::cout <<"sanction with:" << name<< " that is "<< role<<std::endl;
    }
   
    void Player::coup( Player &player,bool gui){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(coinsNum<7){
            throw std::runtime_error("You dont have enough coins");
            return;
        }
        if(player.getIsAlived()==false){
            throw std::runtime_error("You cant coup a dead player");
            return;
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(isBlocked==true){
            setIsBlocked(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            game.nextTurn();
            freeMoves=0;
            lastMove.push_back("coup");
            throw std::runtime_error("You are blocked by bribe");
            return;
        }
        starter();
        coinsNum=coinsNum-7;
        if(gui==true){
             player.setIsAlivedGui(false);
        }
        else{
            player.setIsAlived(false);

        }
        
        std::cout <<"coup with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        std::cout<<"Player: "<< player.getName() << " is dead"<<std::endl;
        game.removePlayer(&player);
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
        lastMove.push_back("coup");
    }


    void Player::skipTurn(){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(isBlocked==true){
            setIsBlocked(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            freeMoves=0;
            game.nextTurn();
            lastMove.push_back("arrest");
            throw std::runtime_error("You are blocked by bribe");
        }
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
        lastMove.push_back("skip");
        std::cout <<"skip with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;

    }
}