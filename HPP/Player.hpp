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
            bool preventToArrest;
    
        public:
            Player(Game &game, const std::string &name)
                : game(game), name(name),blockToBride(false),preventToArrest(false){}

            Player(const Player &other)
                : game(other.game), name(other.name), coinsNum(other.coinsNum), 
                  role(other.role), Alive(other.Alive), playerIndex(other.playerIndex), 
                  playerTurn(other.playerTurn), lastMove(other.lastMove), 
                  isBlocked(other.isBlocked), blockToBride(other.blockToBride), 
                  preventToArrest(other.preventToArrest) {}
                  
            //Player();
            virtual bool operator==(Player &player){
                return name==player.name;
            } 
            virtual int coins() const =0;//returns the number of coins the player has
            virtual std::string getName()=0;
            virtual std::string getRoll()=0;
            //virtual bool isAlive()=0;
            virtual void undo(  Player &player)=0;
            virtual void gather()=0;
            virtual void tax()=0;
            virtual void bride()=0;
            virtual void arrest( Player &player)=0;
            virtual void sanction()=0;
            virtual void coup( Player &player)=0;
            virtual  void setLastCoinNum(int num)=0;
            virtual int getLastCoinNum()const=0;
            virtual bool getPreventToArrest()const=0;
            virtual void setPreventToArrest(bool block)=0;
            virtual void setPreventToBride(bool block)=0;
            virtual void setIsAlived(bool alive)=0;
            virtual bool getIsAlived()=0;

           // virtual void gotArrested()=0;
            const std::vector<std::string>& getLastMove() const {
                return lastMove;
            }
            const bool& isBlockToBride() const{
                return blockToBride;
            }
            // void setBlockToBride(bool block){
            //     blockToBride = block;
            // }
            // void setIsAlived(bool alive){
            //     Alive = alive;
            // }
            // void setLastCoinNum(int num){
            //     coinsNum=num;
            // }
            //virtual void deleteLastMove();

            ~Player(){}

    };

}

#endif 