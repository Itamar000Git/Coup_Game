//itamarbabai98@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <string>
#include <vector>
#include "Game.hpp"
namespace coup{  

    /**
     * @brief The Player class represents a player in the Coup game.
     * It contains information about the player's name, coins, role, and actions.
     */
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
    /**
     * @brief Constructor for the Player class.
     * @param game The game instance.
     * @param name The name of the player.
     */
    Player(Game &game, const std::string &name)
        : game(game), name(name), coinsNum(0), freeMoves(0), lastcoinsNum(0), 
          role(""), Alive(true), playerIndex(0), playerTurn(0), 
          isBlocked(false), blockToBribe(false), preventToArrest(false) {
            for(int i = 0; i < game.getNumOfPlayers(); ++i) {
                if (game.players()[i] == name) {
                    throw std::runtime_error("Player with this name already exists.");
                }
            }
          }
    
    /**
     * @brief Copy constructor for the Player class.
     * @param other The player to copy from.
     */
    Player(const Player &other)
        : game(other.game), name(other.name), coinsNum(other.coinsNum), 
          freeMoves(other.freeMoves), lastcoinsNum(other.lastcoinsNum), 
          role(other.role), Alive(other.Alive), playerIndex(other.playerIndex), 
          playerTurn(other.playerTurn), lastMove(other.lastMove), 
          isBlocked(other.isBlocked), blockToBribe(other.blockToBribe), 
          preventToArrest(other.preventToArrest) {}
     
    /**
     * @brief Assignment operator for the Player class.
     * @param other The player to assign from.
     * @return A reference to this player.
     */
    virtual bool operator==(Player &player){
        return name==player.name;
    } 
    
    /**
     * @brief Assignment operator for the Player class.
     * @param player The player to assign from.
     * @return A reference to this player.
     */
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

            const std::vector<std::string>& getLastMove() const {
                return lastMove;
            }
            const bool& isBlockToBribe() const{
                return blockToBribe;
            }
            virtual void skipTurn();

            
            virtual void setLastMove(std::string move){
                lastMove.push_back(move);
            }


         

           virtual ~Player(){}

    };

}

#endif 