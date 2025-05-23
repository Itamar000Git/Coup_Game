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

            Governor(Game &game, const std::string &name1); // Constructor for the Governor class
            using Player::operator=; // Bring base class operator= into scope

            /**
             * @brief Assignment operator for the Governor class.
             * @param other The Governor object to assign from.
             * @return A reference to this Governor object.
             */
            Governor &operator=(const Governor &other) {
                if (this == &other) {
                    return *this;
                }
                Player::operator=(other); // Call base class assignment operator
                return *this;
            }
                int coins() const; //returns the number of coins the player has
                std::string getName(); //returns the name of the player

                void undo( Player &player); // use to undo tax actions
                
                void tax(); // override tax function
                
                std::string getRoll(); //returns the role of the player
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