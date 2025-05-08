//itamarbabai98@gmail.com

#ifndef JUDGE_HPP
#define JUDGE_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"

namespace coup{  
    class Judge:public Player{
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
                Judge(Game &game, const std::string &name1);
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
                void deleteLastMove();
                std::string getRoll();
                void setLastCoinNum(int num){
                    coinsNum=num;
                }
                int getLastCoinNum()const{
                    return coinsNum;
                }
                 ~Judge(){}
        
    };
}


#endif