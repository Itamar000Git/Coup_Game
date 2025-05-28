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
     * @brief equal operator for the Player class.
     * @param other The player to check equality with.
     * @return A boolean indicating if the players are equal.
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
            virtual std::string getName()=0; //returns the name of the player
            virtual std::string getRoll()=0; //returns the role of the player
            
            virtual void undo(  Player &player)=0; //undo the last move of the player (if its match to rhe role)
            virtual void gather(); // gather 1 coins
            virtual void tax(); // tax 2 coins (if its match to the role)
            virtual void bribe(); // bribe with 3 coins an get 2 turns
            virtual void arrest( Player &player); // steal 1 coins from the player
            virtual void sanction(Player &player); // sanction the player , prevent him to gather ant tax
            virtual void coup( Player &player,bool gui=false); // coup the player, remove him from the game
            virtual void invest(){} // invest 3 coins and get 6 coins (if its match to the role)
             virtual void skipTurn(); // skip the turn of the player (in case of lock)

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
            virtual void starter(){}; //function that dont do anything and override by the merchant

            const std::vector<std::string>& getLastMove() const { //returns the last move of the player
                return lastMove;
            }
            const bool& isBlockToBribe() const{//returns if the player is blocked to bribe
                return blockToBribe;
            }
        
            virtual void setLastMove(std::string move){//set the last move of the player
                lastMove.push_back(move);
            }
            virtual bool canBeArrest(){
                if(coinsNum>=1){
                    return true;
                }
                 
                return false;
            }
           virtual ~Player()
           {
                // Destructor for the Player class
                // Clean up resources if needed
           }

    };

}

#endif 