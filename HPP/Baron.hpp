//itamarbabai98@gmail.com

#ifndef BARON_HPP
#define BARON_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"

namespace coup{  
    class Baron: public Player{
        private:
            int lastcoinsNum;
            // Game &game;
            // std::string name;
            // int coinsNum;
            // std::string role;
            // bool Alive;
            // int playerIndex;
            // int playerTurn;
            // std::vector<std::string> lastMove;

        public:
            Baron(Game &game, const std::string &name1);
            
                int coins() const;
                std::string getName();
                //bool isAlive();
                void undo( Player &player);
                void gather();
                void tax();
                void bride();
                void arrest( Player &player);
                void sanction();
                void coup( Player &player);
                void invest();
                void deleteLastMove();
                int getLastCoinNum()const{
                    return lastcoinsNum;
                }
                void setPreventToArrest(bool block){
                    preventToArrest = block;
                    if(block == false){
                        game.setLastArrest("");
                    }
                }

                bool getPreventToArrest()const{
                    return preventToArrest;
                }
                
                std::string getRoll();
                void setLastCoinNum(int num){
                    lastcoinsNum=num;
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
   
                 ~Baron(){


                 }
        
    };
}


#endif