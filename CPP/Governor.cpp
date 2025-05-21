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
//     Governor::Governor(Game &game1,const std::string &name1):Player(),game(game1),name(name1),
//     coinsNum(0), role("Governor"), Alive(true), playerTurn(0) {
//        playerIndex= game.getNumOfPlayers();
//        game.addPlayer(this);

//        //game.getNumOfPlayers()++;
//        // Initialize the player

//    }
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
        // if(game.turn()!=name){
        //     throw std::runtime_error("This is not your turn");
        //     return;
        // }
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
        //lastMove.push_back("undo tax");
        // if(freeMoves>0){
        //     freeMoves--;
        // }
        // else{
        //     game.nextTurn();
        // }

        std::cout <<"undo with: " << name<< " that is "<< role<<std::endl;
    }



    // void Governor::gather(){
    //     if(game.turn()!=name){
    //         throw std::runtime_error("This is not your turn");
    //         return;
    //     }
    //     if(coinsNum>=10){
    //         throw std::runtime_error("You have too many coins you need to coup");
    //         return;
    //     }
    //     if(isBlocked==true){
    //         throw std::runtime_error("You are blocked");
    //         return;
    //     }
    //     if(preventToArrest==true){
    //         setPreventToArrest(false);
    //     }
    //     if(blockToBride==true){
    //         setPreventToBride(false);
    //         game.nextTurn();
    //         freeMoves=0;
    //         lastMove.push_back("gather");
    //         throw std::runtime_error("You are blocked by bride");
    //         return;
    //     }
    //     coinsNum++; //need to add check if there is a block
    //     std::cout <<"gather with: " << name<< " that is "<< role<<std::endl;
    //     std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
    //     if(freeMoves>0){
    //         freeMoves--;
    //     }
    //     else{
    //         game.nextTurn();
    //     }
    //     lastMove.push_back("gather");
    // }

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
    // void Governor::bride(){
    //     if(game.turn()!=name){
    //         throw std::runtime_error("This is not your turn");
    //         return;
    //     }
    //     if(coinsNum>=10){
    //         throw std::runtime_error("You have too many coins you need to coup");
    //         return;
    //     }
    //     if(coinsNum<=3){
    //         throw std::runtime_error("You dont have enough coins");
    //         return;
    //     }
    //     if(preventToArrest==true){
    //         setPreventToArrest(false);
    //     }
    //     if(isBlocked==true){
    //         setIsBlocked(false);
    //     }
    //     if(blockToBride==true){
    //         setPreventToBride(false);
    //         game.nextTurn();
    //         freeMoves=0;
    //         lastMove.push_back("bride");
    //         throw std::runtime_error("You are blocked by bride");
    //         return;
    //     }
    //     coinsNum=coinsNum-4;
    //     freeMoves=1;

    //     std::cout <<"bride with:" << name<< " that is "<< role<<std::endl;
    //     std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
    // }
    // void Governor::arrest( Player &player){
    //     if(game.turn()!=name){
    //         throw std::runtime_error("This is not your turn");
    //         return;
    //     }
    //     if(player.getName()==game.lastArrested()){
    //         throw std::runtime_error("You cant arrest the same player twice");
    //         return;
    //     }
    //     int num=player.getLastCoinNum();
    //     if(num==0){
    //         throw std::runtime_error("You cant arrest a player with 0 coins");
    //         return;
    //     }
    //     if(preventToArrest==true){
    //         setPreventToArrest(false);
    //     }
    //     if(isBlocked==true){
    //         setIsBlocked(false);
    //     }
    //     if(player.getIsAlived()==false){
    //         throw std::runtime_error("You cant arrest a dead player");
    //         return;
    //     }
    //     if(blockToBride==true){
    //         setPreventToBride(false);
    //         game.nextTurn();
    //         freeMoves=0;
    //         lastMove.push_back("arrest");
    //         throw std::runtime_error("You are blocked by bride");
    //         return;
    //     }
    //     if(player.getRoll()=="General"){ //General get his coins back
           
    //         std::cout<<"General get his coins back"<<std::endl;
    //     }
    //     else if(player.getRoll()=="Merchent"){
    //         player.setLastCoinNum(num-2);
    //     }
    //     else{
    //         player.setLastCoinNum(num-1);
    //         coinsNum=coinsNum+1;
    //     }

    //     game.setLastArrest(player.getName());
    //     if(freeMoves>0){
    //         freeMoves--;
    //     }
    //     else{
    //         game.nextTurn();
    //     }
    //     lastMove.push_back("arrest");
    //     std::cout << name<< " that is "<< role<<" arrest : "<< player.getName() <<" that is: "<< player.getRoll()<<std::endl;

    //     std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
    // }


    // void Governor::sanction(Player &player){
    //     if(game.turn()!=name){
    //         throw std::runtime_error("This is not your turn");
    //         return;
    //     }
    //     if(player.getIsAlived()==false){
    //         throw std::runtime_error("You cant arrest a dead player");
    //         return;
    //     }        
    //     if(preventToArrest==true){
    //         setPreventToArrest(false);
    //     }
    //     if(isBlocked==true){
    //         setIsBlocked(false);
    //     }
    //     if(blockToBride==true){
    //         setPreventToBride(false);
    //         freeMoves=0;
    //         game.nextTurn();
    //         lastMove.push_back("arrest");
    //         throw std::runtime_error("You are blocked by bride");
    //         return;
    //     }
    //     int num=player.getLastCoinNum();
    //     int lim=3;
    //     if(player.getRoll()=="judge"){
    //         lim=4;
    //     }
    //     if(player.getRoll()=="Baron"){ //Baron get his coins back
    //         player.setLastCoinNum(player.getLastCoinNum()+1);
    //     }
    //     if(num<lim){
    //         throw std::runtime_error("You dont have enough coins");
    //         return;

    //     }
    //     coinsNum=coinsNum-lim;


    //     if(freeMoves>0){
    //         freeMoves--;
    //     }
    //     else{
    //         game.nextTurn();
    //     }
    //     lastMove.push_back("sanction");

    //     std::cout <<"sanction with:" << name<< " that is "<< role<<std::endl;
    // }
    // void Governor::coup( Player &player){
    //     if(game.turn()!=name){
    //         throw std::runtime_error("This is not your turn");
    //         return;
    //     }
    //     if(coinsNum<7){
    //         throw std::runtime_error("You dont have enough coins");
    //         return;
    //     }
    //     if(preventToArrest==true){
    //         setPreventToArrest(false);
    //     }
    //     if(isBlocked==true){
    //         setIsBlocked(false);
    //     }
    //     if(player.getIsAlived()==false){
    //         throw std::runtime_error("You cant coup a dead player");
    //         return;
    //     }
    //     if(blockToBride==true){
    //         setPreventToBride(false);
    //         game.nextTurn();
    //         freeMoves=0;
    //         lastMove.push_back("coup");
    //         throw std::runtime_error("You are blocked by bride");
    //         return;
    //     }
    //     coinsNum=coinsNum-7;
    //     player.setIsAlived(false);

    //     std::cout <<"coup with:" << name<< " that is "<< role<<std::endl;
    //     std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
    //     std::cout<<"Player: "<< player.getName() << " is dead"<<std::endl;
    //     game.removePlayer(&player);

    //     if(freeMoves>0){
    //         freeMoves--;
    //     }
    //     else{
    //         game.nextTurn();
    //     }
    //     lastMove.push_back("coup");
    // }
}