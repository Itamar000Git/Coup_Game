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
                bool getPreventToArrest() const{
                    return preventToArrest;
                }
                void setPreventToArrest(bool block){
                    preventToArrest = block;
                    if(block == false){
                        game.setLastArrest("");
                    }
                }
                void setPreventToBride(bool block){
                    blockToBride = block;
                }
                void judgPreventBride(Player &player);

                void setIsAlived(bool alive){
                    Alive = alive;
                }
                 bool getIsAlived(){
                    return Alive;
                }
                 ~Judge(){}
        
    };
}


#endif