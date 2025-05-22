//itamarbabai98@gmail.com

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>

namespace coup
{  
    class Player;//Early declaration for using the players vector

    /**
     * @brief The Game class represents the game of Coup.
     * It manages the players, their turns, and the game state.
     */
    class Game{
        private:

            std::vector<Player*> board;

            int playerTurn;
            int numOfPlayers;
            int gameInit;
            
            std::string lastArrest;
            std::vector<Player*> coupedPlayers;
    
        public:
        //
            Game();
            void addPlayer(Player* player);
            int& getNumOfPlayers();
            std::string turn();
            std::vector<std::string> players();

            /**
             * * @brief Add a player to the coupedPlayers vector
             * @param player The player to be added
             */
            void setCoupedPlayers(Player* player){
                coupedPlayers.push_back(player);
            }
            void uncoupLastCoupedPlayer();
            std::string winner();
            void removePlayer(Player* player);
            void nextTurn();
            std::string lastArrested();

            /**
             * @brief Set the last arrested player
             * @param name The name of the last arrested player
             */
            void setLastArrest(std::string name){
                lastArrest=name;
            }
            

            friend std::ostream& operator<<(std::ostream& os, const Game& game);

            
        

            ~Game(){}
    };
}
#endif