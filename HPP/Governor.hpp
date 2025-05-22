//itamarbabai98@gmail.com

#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"

namespace coup{  
    class Governor:public Player{
        private:
            

        public:
            Governor(Game &game, const std::string &name1);
            using Player::operator=; // Bring base class operator= into scope
            Governor &operator=(const Governor &other) {
                if (this == &other) {
                    return *this;
                }
                Player::operator=(other); // Call base class assignment operator
                return *this;
            }
                int coins() const;
                std::string getName();

                void undo( Player &player);
                
                void tax();
                
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
                void setPreventToBribe(bool block){
                    blockToBribe = block;
                }
                void setIsAlived(bool alive){
                    Alive = alive;
                }
                 bool getIsAlived(){
                    return Alive;
                }
                bool getIsBlocked()const{
                    return isBlocked;
                }
                 ~Governor(){}

        
    };
}


#endif