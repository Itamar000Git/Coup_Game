//itamarbabai98@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <string>
#include <vector>
#include "Game.hpp"
namespace coup{  
    class Player {

        protected:
            Game &game;
            std::string name;
            int coinsNum;
            std::string role;
            bool Alive;
            int playerIndex;
            int playerTurn;
            std::vector<std::string> lastMove;
            bool isBlocked;
            bool blockToBride;
    
        public:
            Player(Game &game, const std::string &name)
                : game(game), name(name),blockToBride(0){}

            //Player();
            virtual int coins() const =0;//returns the number of coins the player has
            virtual std::string getName()=0;
            virtual std::string getRoll()=0;
            virtual bool isAlive()=0;
            virtual void undo(  Player &player)=0;
            virtual void gather()=0;
            virtual void tax()=0;
            virtual void bride()=0;
            virtual void arrest( Player &player)=0;
            virtual void sanction()=0;
            virtual void coup( Player &player)=0;
            virtual  void setLastCoinNum(int num)=0;
            virtual int getLastCoinNum()const=0;
            
           // virtual void gotArrested()=0;
            const std::vector<std::string>& getLastMove() const {
                return lastMove;
            }
            const bool& isBlockToBride() const{
                return blockToBride;
            }
            void setBlockToBride(bool block){
                blockToBride = block;
            }
            void setIsAlived(bool alive){
                Alive = alive;
            }
            // void setLastCoinNum(int num){
            //     coinsNum=num;
            // }
            //virtual void deleteLastMove();

            ~Player(){}

    };

}

#endif 