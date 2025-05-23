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
            

        public:

                Judge(Game &game, const std::string &name1);// Constructor for the Judge class
                using Player::operator=; // Bring base class operator= into scope

                /**
                 * @brief Assignment operator for the Judge class.
                 * @param other The Judge object to assign from.
                 * @return A reference to this Judge object.
                 * 
                 * This operator allows for assignment between Judge objects.
                 * It first checks for self-assignment and then calls the base class assignment operator.
                 */
                Judge &operator=(const Judge &other) {
                if (this == &other) {
                    return *this;
                }
                Player::operator=(other); // Call base class assignment operator
                return *this;
            }
                int coins() const; //returns the number of coins the player has
                std::string getName(); //returns the name of the player
   
                void undo( Player &player); // use to undo bribe actions
                
                
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
                void judgPreventBribe(Player &player);

                void setIsAlived(bool alive){
                    Alive = alive;
                }
                 bool getIsAlived(){
                    return Alive;
                }
                bool getIsBlocked()const{
                    return isBlocked;
                }
                 ~Judge(){}
        
    };
}


#endif