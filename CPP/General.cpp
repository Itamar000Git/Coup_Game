//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/General.hpp"

namespace coup{  
    // General::General(Game &game1, const std::string &name1):Player(),name(name1),game(game1),
    // coinsNum(0), role("General"), Alive(true), playerTurn(0) {
    //    playerIndex= game.getNumOfPlayers();
    //    game.addPlayer(this);
    //    //game.getNumOfPlayers()++;
    //    // Initialize the player

   //}
   General::General(Game &game1, const std::string &name1)
   : Player(game1, name1) { 
       this->role = "General"; 
       playerIndex= game.getNumOfPlayers();
       game.addPlayer(this); 
       Alive = true;
       coinsNum = 0;   
       playerTurn = 0;
       isBlocked = false;

   }



    int General::coins() const{//returns the number of coins the player has
        return coinsNum;
     }
      std::string General::getName(){
        return name;
     }
        std::string General::getRoll(){
            return role;
        }

    void General::undo( Player &player){
        std::cout <<"undo with:" << name<< "that is"<< role<<std::endl;
    }
    void General::gather(){
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
        if(blockToBride==true){
            setPreventToBride(false);
            game.nextTurn();
            lastMove.push_back("gather");
            throw std::runtime_error("You are blocked by bride");
            return;
        }
        coinsNum++; //need to add check if there is a block
        std::cout <<"gather with: " << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        game.nextTurn();
        lastMove.push_back("gather");
        }

    void General::tax(){
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
        if(blockToBride==true){
            setPreventToBride(false);
            game.nextTurn();
            lastMove.push_back("tax");
            throw std::runtime_error("You are blocked by bride");
            return;
        }
        coinsNum+=2; 
        std::cout <<"tax with:" << name<< " that is"<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        game.nextTurn();
        lastMove.push_back("tax");
    }

    void General::bride(){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            return;
        }
        if(coinsNum<=3){
            throw std::runtime_error("You dont have enough coins");
            return;
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(blockToBride==true){
            setPreventToBride(false);
            game.nextTurn();
            lastMove.push_back("bride");
            throw std::runtime_error("You are blocked by bride");
            return;
        }
        coinsNum=coinsNum-4;
       
        std::cout <<"bride with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
    }
    void General::arrest( Player &player){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(player.getName()==game.lastArrested()){
            throw std::runtime_error("You cant arrest the same player twice");
            return;
        }
        if(preventToArrest==true){
            throw std::runtime_error("You are blocked");
            return;
        }
        if(player.getIsAlived()==false){
            throw std::runtime_error("You cant arrest a dead player");
            return;
        }
        int num=player.getLastCoinNum();
        if(num==0){
            throw std::runtime_error("You cant arrest a player with 0 coins");
            return;
        }
        if(blockToBride==true){
            setPreventToBride(false);
            game.nextTurn();
            lastMove.push_back("arrest");
            throw std::runtime_error("You are blocked by bride");
            return;
        }

        if(player.getRoll()=="General"){ //General get his coins back
           
            coinsNum=coinsNum+1;
        }
        else if(player.getRoll()=="Merchent"){
            player.setLastCoinNum(num-2);
        }
        else{
            player.setLastCoinNum(num-1);
            coinsNum=coinsNum+1;
        }
        
        game.setLastArrest(player.getName());
        game.nextTurn();
        lastMove.push_back("arrest");
        std::cout << name<< " that is "<< role<<" arrest : "<< player.getName() <<" that is: "<< player.getRoll()<<std::endl;

        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
    }
    void General::sanction(){
        std::cout <<"sanction with:" << name<< " that is"<< role<<std::endl;
    }
    void General::coup( Player &player){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(coinsNum<7){
            throw std::runtime_error("You dont have enough coins");
            return;
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(player.getIsAlived()==false){
            throw std::runtime_error("You cant coup a dead player");
            return;
        }
        if(blockToBride==true){
            setPreventToBride(false);
            game.nextTurn();
            lastMove.push_back("arrest");
            throw std::runtime_error("You are blocked by bride");
            return;
        }
        coinsNum=coinsNum-7;
        player.setIsAlived(false);

        std::cout <<"coup with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        std::cout<<"Player: "<< player.getName() << " is dead"<<std::endl;
        game.removePlayer(&player);
        game.nextTurn();
        lastMove.push_back("coup");
    }
}