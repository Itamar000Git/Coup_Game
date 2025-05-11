//itamarbabai98@gmail.com

#ifndef SPY_HPP
#define SPY_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"

namespace coup{  
    class Spy:public Player{
        private:
            // Game &game;
            // std::string name;
            // int coinsNum;
            // std::string role;
            // bool Alive;
            // int playerIndex;
            // int playerTurn;
            // std::vector<std::string> lastMove;

        public:
                Spy(Game &game, const std::string &name1);
                int coins() const;
                std::string getName();
              
                void undo( Player &player);
                //void gather();
                void tax();
                void bride();
                void arrest( Player &player);
                void sanction(Player &player);
                void coup( Player &player);
                void deleteLastMove();
                std::string getRoll();
                int watchNumOfCoins(Player &player) const{
                   return player.coins();
                }
                void setLastCoinNum(int num){
                    coinsNum=num;
                }
                int getLastCoinNum()const{
                    return coinsNum;
                }
                bool getPreventToArrest() const{
                    return preventToArrest;
                }
                void setPreventToArrest(bool block){
                    preventToArrest = block;
                    if(block == false){
                        game.setLastArrest("");
                    }
                }
                void prventArrest(Player &player){
                    player.setPreventToArrest(true);
               }
                void setPreventToBride(bool block){
                    blockToBride = block;
                }
                void setIsAlived(bool alive){
                    Alive = alive;
                }
                 bool getIsAlived(){
                    return Alive;
                }
                 ~Spy(){}
        
    };
}


#endif