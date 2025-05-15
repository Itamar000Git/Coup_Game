//itamarbabai98@gmail.com

#ifndef MERCHENT_HPP
#define MERCHENT_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"

namespace coup{  
    class Merchant:public Player{
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
                Merchant(Game &game, const std::string &name1);
                using Player::operator=; // Bring base class operator= into scope
                Merchant &operator=(const Merchant &other) {
                if (this == &other) {
                    return *this;
                }
                Player::operator=(other); // Call base class assignment operator
                return *this;
            }         
                int coins() const;
                std::string getName();
                void undo( Player &player);
                //void gather();
                //void tax();
                //void bride();
                //void arrest( Player &player);
                //void sanction(Player &player);
                //void coup( Player &player);
                void deleteLastMove();
                std::string getRoll();
                void setIsBlocked(bool block){
                    isBlocked = block;
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
                void setPreventToBride(bool block){
                    blockToBride = block;
                }
                void setIsAlived(bool alive){
                    Alive = alive;
                }
                 bool getIsAlived(){
                    return Alive;
                }
                void starter(){
                    if(coinsNum>=3){
                        coinsNum++;
                    }
                }
                 ~Merchant(){}
        
    };
}


#endif