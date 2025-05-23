//itamarbabai98@gmail.com

#ifndef SPY_HPP
#define SPY_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"

namespace coup{  
    class Spy:public Player{
        private:
            

        public:
                Spy(Game &game, const std::string &name1);// Constructor for the Spy class
                using Player::operator=; // Bring base class operator= into scope

                /**
                 * @brief Assignment operator for the Spy class.
                 * @param other The Spy object to assign from.
                 * @return A reference to this Spy object.
                 * 
                 * This operator allows for assignment between Spy objects.
                 * It first checks for self-assignment and then calls the base class assignment operator.
                 */
                Spy &operator=(const Spy &other) {
                if (this == &other) {
                    return *this;
                }
                Player::operator=(other); // Call base class assignment operator
                return *this;
            }
                int coins() const;//returns the number of coins the player has
                std::string getName();//returns the name of the player
              
                void undo( Player &player){
                    throw std::runtime_error("You cant undo a anything");
                }

                
               
               
                std::string getRoll(); //returns the role of the player
                void setIsBlocked(bool block){
                    isBlocked = block;
                }

                /**
                 * @brief The player can see the coins of another player
                 * @param player The player to be seen
                 * @throws std::runtime_error if the player is dead
                 * @return The number of coins the player has
                 */
                int watchNumOfCoins(Player &player) const{
                    if(Alive == false){
                        throw std::runtime_error("You cant action as a dead player");
                    }
                    if(player.getIsAlived() == false){
                        throw std::runtime_error("You cant see a dead player coins");
                    }
                    
                   return player.coins();
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

                /**
                 * @brief The player can prevent another player to arrest him
                 * @param player The player to be prevented
                 * @throws std::runtime_error if the player is dead
                 */
                void prventArrest(Player &player){
                    if(Alive == false){
                        throw std::runtime_error("You cant action as a dead player");
                    }
                    if(player.getIsAlived() == false){
                        throw std::runtime_error("You cant see a dead player coins");
                    }
                    player.setPreventToArrest(true);
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
                 ~Spy(){}
        
    };
}


#endif