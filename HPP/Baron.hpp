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
                bool isAlive();
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
                
                std::string getRoll();
                void setLastCoinNum(int num){
                    lastcoinsNum=num;
                }
   
                 ~Baron(){


                 }
        
    };
}


#endif