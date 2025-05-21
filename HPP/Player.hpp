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
    int freeMoves;
    int lastcoinsNum;
    std::string role;
    bool Alive;
    int playerIndex;
    int playerTurn; // not used
    std::vector<std::string> lastMove;
    bool isBlocked;
    bool blockToBribe;
    bool preventToArrest;

public:
    Player(Game &game, const std::string &name)
        : game(game), name(name), coinsNum(0), freeMoves(0), lastcoinsNum(0), 
          role(""), Alive(true), playerIndex(0), playerTurn(0), 
          isBlocked(false), blockToBribe(false), preventToArrest(false) {}

    Player(const Player &other)
        : game(other.game), name(other.name), coinsNum(other.coinsNum), 
          freeMoves(other.freeMoves), lastcoinsNum(other.lastcoinsNum), 
          role(other.role), Alive(other.Alive), playerIndex(other.playerIndex), 
          playerTurn(other.playerTurn), lastMove(other.lastMove), 
          isBlocked(other.isBlocked), blockToBribe(other.blockToBribe), 
          preventToArrest(other.preventToArrest) {}
        // protected:
        //     Game &game;
        //     std::string name;
        //     int coinsNum;
        //     int freeMoves;
        //     int lastcoinsNum;
        //     std::string role;
        //     bool Alive;
        //     int playerIndex;
        //     int playerTurn; //not used
        //     std::vector<std::string> lastMove;
        //     bool isBlocked;
        //     bool blockToBride;
        //     bool preventToArrest;
            
    
        // public:
        //     Player(Game &game, const std::string &name)
        //         : game(game), name(name),blockToBride(false),preventToArrest(false),freeMoves(0){}

        //     Player(const Player &other)
        //         : game(other.game), name(other.name), coinsNum(other.coinsNum), 
        //           role(other.role), Alive(other.Alive), playerIndex(other.playerIndex), 
        //           playerTurn(other.playerTurn), lastMove(other.lastMove), 
        //           isBlocked(other.isBlocked), blockToBride(other.blockToBride), 
        //           preventToArrest(other.preventToArrest), freeMoves(other.freeMoves),lastcoinsNum(other.lastcoinsNum) {}
                  
            //Player();
            virtual bool operator==(Player &player){
                return name==player.name;
            } 
            
            virtual Player& operator=(const Player &player){
                if(this==&player){
                    return *this;
                }
                name=player.name;
                coinsNum=player.coinsNum;
                role=player.role;
                Alive=player.Alive;
                playerIndex=player.playerIndex;
                playerTurn=player.playerTurn;
                lastMove=player.lastMove;
                isBlocked=player.isBlocked;
                blockToBribe=player.blockToBribe;
                preventToArrest=player.preventToArrest;
                freeMoves=player.freeMoves;
                lastcoinsNum=player.lastcoinsNum;
                return *this;
            }
  
           
            virtual int coins() const =0;//returns the number of coins the player has
            virtual std::string getName()=0;
            virtual std::string getRoll()=0;
            //virtual bool isAlive()=0;
            virtual void undo(  Player &player)=0;
            virtual void gather();
            virtual void tax();
            virtual void bribe();
            virtual void arrest( Player &player);
            virtual void sanction(Player &player);
            virtual void coup( Player &player,bool gui=false);
            virtual void invest(){}
            virtual void setIsBlocked(bool block)=0;
            virtual bool getIsBlocked()const=0;
            virtual  void setLastCoinNum(int num)=0;
            virtual int getLastCoinNum()const=0;
            virtual bool getPreventToArrest()const=0;
            virtual void setPreventToArrest(bool block)=0;
            virtual void setPreventToBribe(bool block)=0;
            //void skipTurn();
            // virtual int getTaxNum()const{
            //     return 2;
            // }
            virtual void setIsAlived(bool alive){
                Alive = alive;
            }
            virtual void setIsAlivedGui(bool alive){
                Alive = alive;
            }
            virtual bool askToStayAlive(){
                return false;
            }
            virtual bool getIsAlived()=0;
            virtual void starter(){};

           // virtual void gotArrested()=0;
            const std::vector<std::string>& getLastMove() const {
                return lastMove;
            }
            const bool& isBlockToBribe() const{
                return blockToBribe;
            }
            virtual void skipTurn();

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

           virtual ~Player(){}

    };

}

#endif 