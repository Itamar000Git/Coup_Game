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
            // Game &game;
            // std::string name;
            // int coinsNum;
            // std::string role;
            // bool Alive;
            // int playerIndex;
            // int playerTurn;
            // std::vector<std::string> lastMove;

        public:
                Spy(Game &game, const std::string &name1);
                using Player::operator=; // Bring base class operator= into scope
                Spy &operator=(const Spy &other) {
                if (this == &other) {
                    return *this;
                }
                Player::operator=(other); // Call base class assignment operator
                return *this;
            }
                int coins() const;
                std::string getName();
              
                void undo( Player &player);
                int getCoins(Player &player) const{
                    if(player.getIsAlived() == false){
                        throw std::runtime_error("You cant see a dead player coins");
                    }
                    return player.coins();
                }
                //void gather();
               // void tax();
                //void bride();
               // void arrest( Player &player);
                //void sanction(Player &player);
                //void coup( Player &player);
                void deleteLastMove();
                std::string getRoll();
                void setIsBlocked(bool block){
                    isBlocked = block;
                }
                int watchNumOfCoins(Player &player) const{
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
                void prventArrest(Player &player){
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