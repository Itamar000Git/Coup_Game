#include <iostream>
#include <string>
#include <cstring>

#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Merchant.hpp"

namespace coup{  
//     Merchant::Merchant(Game &game1, const std::string &name1):Player(),name(name1),game(game1),
//     coinsNum(0), role("Merchant"), Alive(true), playerTurn(0) {
//        playerIndex= game.getNumOfPlayers();
//        game.addPlayer(this);
//        //game.getNumOfPlayers()++;
//        // Initialize the player
//    }
    Merchant::Merchant(Game &game1, const std::string &name1)
    : Player(game1, name1) { 
        this->role = "Merchant"; 
        playerIndex= game.getNumOfPlayers();
        game.addPlayer(this); 
        Alive = true;
        coinsNum = 0;   
        playerTurn = 0;
        isBlocked = false;
    }


    int Merchant::coins() const{//returns the number of coins the player has
        return coinsNum;
     }
     std::string Merchant::getName(){
        return name;
     }
    std::string Merchant::getRoll(){
        return role;
     }
    bool Merchant::isAlive(){
        return Alive;
    }
    void Merchant::undo( Player &player){
        std::cout <<"undo with:" << name<< "that is"<< role<<std::endl;
    }
    void Merchant::gather(){
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
        if(blockToBride==true){
            setBlockToBride(false);
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

    void Merchant::tax(){
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
        if(blockToBride==true){
            setBlockToBride(false);
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


    void Merchant::bride(){
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
        if(blockToBride==true){
            setBlockToBride(false);
            game.nextTurn();
            lastMove.push_back("bride");
            throw std::runtime_error("You are blocked by bride");
            return;
        }
        coinsNum=coinsNum-4;
       
        std::cout <<"bride with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
    }
    void Merchant::arrest( Player &player){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(player.getName()==game.lastArrested()){
            throw std::runtime_error("You cant arrest the same player twice");
            return;
        }
        int num=player.getLastCoinNum();
        if(num==0){
            throw std::runtime_error("You cant arrest a player with 0 coins");
            return;
        }
        player.setLastCoinNum(num-1);
        coinsNum=coinsNum+1;
        game.setLastArrest(player.getName());
        game.nextTurn();
        lastMove.push_back("arrest");
        std::cout <<"arrest with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        std::cout<<"Player: "<< player.getName() << " coinsNum is: "<< num-1<<std::endl;
    }
    void Merchant::sanction(){
        std::cout <<"sanction with:" << name<< " that is"<< role<<std::endl;
    }
    void Merchant::coup( Player &player){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(coinsNum<7){
            throw std::runtime_error("You dont have enough coins");
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