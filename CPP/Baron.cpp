//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>

#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Baron.hpp"

namespace coup{

    /**
     * @brief Constructor for the Baron class.
     * @param game1 The game instance.
     * @param name1 The name of the player.
     */
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

     std::string Baron::getName(){
        return name;
     }
    std::string Baron::getRoll(){
        return role;
     }



    /**
     * @brief Override the gather method because the Baron still getting pay when sanctioned.
     * @throws std::runtime_error if it's not the player's turn , if the player has too many coins, if the player is blocked by bribe and after bride.
    */
    void Baron::gather(){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
        }
        if(isBlocked==true){
            
            setIsBlocked(false);
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
        coinsNum++; 
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
    /**
     * @brief Override the tax method because the Baron still getting pay when sanctioned.
     * @throws std::runtime_error if it's not the player's turn , if the player has too many coins, if the player is blocked by bribe and after bride.
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
            setIsBlocked(false);
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

    /**
     * @brief Spatially for the Baron, the invest method is used to get 6 coins by paying 3 coins.
     * @throws std::runtime_error if it's not the player's turn , if the player has too many coins,
     *  if the player is blocked by bribe and after bride ,if the player has less than 3 coins.
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