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
            int lastcoinsNum; // The last number of coins the player had, in use for undo tax on baron
        public:
            Baron(Game &game, const std::string &name1); // Constructor for the Baron class
            Baron(const Baron &other): Player(other) {
                this->lastcoinsNum = other.lastcoinsNum; // Copy the last coins number
            }
            
            /**
             * @brief Assignment operator for the Baron class.
             * @param other The Baron object to assign from.
             * @return A reference to this Baron object.
             * 
             * This operator allows for assignment between Baron objects.
             * It first checks for self-assignment and then calls the base class assignment operator.
             */
            
            using Player::operator=; // Bring base class operator= into scope
            Baron &operator=(const Baron &other) {
                if (this == &other) {
                    return *this;
                }
                Player::operator=(other); // Call base class assignment operator
                return *this;
            }

                int coins() const;
                std::string getName();
            
               
                /**
                 * @brief The player cant undo a move
                 * @param player The player to be undo the last move
                 * @throws std::runtime_error this player cant undo a move
                 */
                void undo( Player &player){throw std::runtime_error("You cant undo a anything");}
                void gather();
                void tax();
                
                void invest();
                
                
                int getLastCoinNum()const{ //returns the last number of coins the player had
                    return lastcoinsNum;
                }
                void setPreventToArrest(bool block){ //set the player to be prevented to arrest
                    preventToArrest = block;
                    if(block == false){
                        game.setLastArrest("");
                    }
                }

                bool getPreventToArrest()const{ //returns if the player is prevented to arrest
                    return preventToArrest;
                }
                
                std::string getRoll();
                void setLastCoinNum(int num){//set the last number of coins the player had
                    coinsNum=num;
                }
                void setPreventToBribe(bool block){ //set the player to be prevented to bribe or not
                    blockToBribe = block;
                }
                void setIsAlived(bool alive){ //set the player to be alive or not
                    Alive = alive;
                }
                 bool getIsAlived(){ //get the player is alive status
                    return Alive;
                }
                void setIsBlocked(bool block){ //set the player to be blocked or not
                    isBlocked = block;
                }
                bool getIsBlocked()const{ //get the player is blocked status
                    return isBlocked;
                }
   
                 ~Baron(){
                    // Destructor for the Baron class
                    // No dynamic memory allocation, so nothing to clean up

                 }
        
    };
}


#endif