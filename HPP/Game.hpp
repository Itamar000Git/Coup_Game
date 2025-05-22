//itamarbabai98@gmail.com

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>

//#include "Player.hpp"
namespace coup
{  
    class Player;//Early declaration for using the players vector
    class Game{
        private:

            std::vector<Player*> board;

            int playerTurn;
            int numOfPlayers;
            int gameInit;
            
            std::string lastArrest;
            std::vector<Player*> coupedPlayers;
            //string currentTurn;
    
        public:
            Game();
            void addPlayer(Player* player);
            int& getNumOfPlayers();
            std::string turn();
            std::vector<std::string> players();
            //std::vector<Player*>& getCoupedPlayers();
            void setCoupedPlayers(Player* player){
                coupedPlayers.push_back(player);
            }
            void uncoupLastCoupedPlayer();
            std::string winner();
            void removePlayer(Player* player);
            void nextTurn();
            std::string lastArrested();
            void setLastArrest(std::string name){
                lastArrest=name;
            }
            
            friend std::ostream& operator<<(std::ostream& os, const Game& game);

            
        

            ~Game(){}
    };
}
#endif