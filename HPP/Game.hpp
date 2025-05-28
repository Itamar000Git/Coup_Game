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
        
            Game();
            void addPlayer(Player* player);
            int& getNumOfPlayers();
            std::string turn();
            std::vector<std::string> players();
            std::vector<Player*> playersVector()  { // return the players vector
                return board;
            }


            /**
             * * @brief Add a player to the coupedPlayers vector
             * @param player The player to be added
             */
            void setCoupedPlayers(Player* player){
                coupedPlayers.push_back(player);
            }
            void uncoupLastCoupedPlayer(); 
            std::string winner(); // get the winner of the game
            void removePlayer(Player* player); // remove the player from the game
            void nextTurn(); // move to the next player
            std::string lastArrested(); // get the last arrested player

            /**
             * @brief Set the last arrested player
             * @param name The name of the last arrested player
             */
            void setLastArrest(std::string name){
                lastArrest=name;
            }
            

            friend std::ostream& operator<<(std::ostream& os, const Game& game); //override the << operator to print the game state

            
        

            ~Game(){}
    };
}
#endif