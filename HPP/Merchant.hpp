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
            

        public:
                Merchant(Game &game, const std::string &name1);// Constructor for the Merchant class
                using Player::operator=; // Bring base class operator= into scope

                /**
                 * @brief Assignment operator for the Merchant class.
                 * @param other The Merchant object to assign from.
                 * @return A reference to this Merchant object.
                 * 
                 * This operator allows for assignment between Merchant objects.
                 * It first checks for self-assignment and then calls the base class assignment operator.
                 */
                Merchant &operator=(const Merchant &other) {
                if (this == &other) {
                    return *this;
                }
                Player::operator=(other); // Call base class assignment operator
                return *this;
            }         
                int coins() const;//returns the number of coins the player has
                std::string getName();//returns the name of the player

                /**
                 * @brief The player cant undo a move
                 * @param player The player to be undo the last move
                 * @throws std::runtime_error this player cant undo a move
                 */
                void undo( Player &player){
                     throw std::runtime_error("You cant undo a anything");
                }
                
                
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
                void starter(){
                    if(coinsNum>=3){
                        coinsNum++;
                    }
                }
                bool getIsBlocked()const{
                    return isBlocked;
                }
                 ~Merchant(){}
        
    };
}


#endif