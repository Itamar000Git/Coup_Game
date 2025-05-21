//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>

#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Baron.hpp"

namespace coup{

    Baron::Baron(Game &game1, const std::string &name1)
        : Player(game1, name1) { 
        this->role = "Baron"; 
        playerIndex= game.getNumOfPlayers();
        game.addPlayer(this); 
        coinsNum = 0;
        lastcoinsNum=0;   
        playerTurn = 0;
        freeMoves=0;
        Alive = true;
        blockToBribe = false;
        preventToArrest = false;
        isBlocked = false;

    }


    int Baron::coins() const{//returns the number of coins the player has
        return coinsNum;
     }
    //  int Baron::getLastCoinNum()const{
    //     return lastcoinsNum;
    //  }

     std::string Baron::getName(){
        return name;
     }
    std::string Baron::getRoll(){
        return role;
     }

    void Baron::undo( Player &player){
        std::cout <<"undo with:" << name<< " that is "<< role<<std::endl;
    }

    /**
    * if there is sanction the baron get only 1 coin
    */
    // void Baron::gather(){ 
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
    //         freeMoves=0;
    //         game.nextTurn();
            
    //         lastMove.push_back("gather");
    //         throw std::runtime_error("You are blocked by bride");
    //         return;
    //     }
    //     lastcoinsNum=coinsNum;
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
    * if there is sanction the baron get only 1 coin
    */
    void Baron::tax(){
        int num =2;
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            return;
        }
        if(isBlocked==true){
            num=1;
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            freeMoves=0;
            game.nextTurn();
            
            lastMove.push_back("tax");
            throw std::runtime_error("You are blocked by bribe");
            return;
        }
        lastcoinsNum=coinsNum;
        coinsNum=coinsNum+num;
        std::cout <<"tax with: " << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
        lastMove.push_back("tax");
    }
    // void Baron::bride(){
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
    //         freeMoves=0;
    //         game.nextTurn();
    //         lastMove.push_back("bride");
    //         throw std::runtime_error("You are blocked by bride");
    //         return;
    //     }
    //     coinsNum=coinsNum-4;
    //     freeMoves=1;
       
    //     std::cout <<"bride with:" << name<< " that is "<< role<<std::endl;
    //     std::cout<<"Num of coins is: "<<coinsNum<<std::endl;

    // }
    // void Baron::arrest( Player &player){
    //     if(game.turn()!=name){
    //         throw std::runtime_error("This is not your turn");
    //         return;
    //     }
    //     if(preventToArrest==true){
    //         throw std::runtime_error("You are blocked");
    //         return;
    //     }
    //     if(player.getName()==game.lastArrested()){
    //         throw std::runtime_error("You cant arrest the same player twice");
    //         return;
    //     }
    //     if(player.getIsAlived()==false){
    //         throw std::runtime_error("You cant arrest a dead player");
    //         return;
    //     }
    //     int num=player.getLastCoinNum();
    //     if(num==0){
    //         throw std::runtime_error("You cant arrest a player with 0 coins");
    //         return;
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
    //     starter();
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
    // void Baron::sanction( Player &player){
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
    //     if(player.getRoll()=="Judge"){
    //         lim=4;
    //     }
    //     if(num<lim){
    //         throw std::runtime_error("You dont have enough coins");
    //         return;

    //     }
    //     if(player.getRoll()=="Baron"){ //Baron get his coins back
    //         player.setLastCoinNum(player.getLastCoinNum()+1);
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
    // void Baron::coup( Player &player){
    //     if(game.turn()!=name){
    //         throw std::runtime_error("This is not your turn");
    //         return;
    //     }
    //     if(coinsNum<7){
    //         throw std::runtime_error("You dont have enough coins");
    //         return;
    //     }
    //     if(player.getIsAlived()==false){
    //         throw std::runtime_error("You cant coup a dead player");
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
    /**
    * The baron can invest 3 coins and get 6 coins
    */
    void Baron::invest(){ 
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            return;
        }
        if(coinsNum<3){
            throw std::runtime_error("You dont have enough coins");
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
        coinsNum=coinsNum+3; // coinsNum-3+6
        std::cout <<"invest with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
        lastMove.push_back("invest");
    }

 


}