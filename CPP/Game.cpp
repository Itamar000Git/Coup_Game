//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "../HPP/Game.hpp"
#include "../HPP/Player.hpp"
#include <cstring>

namespace coup
{  
    /**
     * @brief The Game class represents the game of Coup.
     * It manages the players, their actions, and the game state.
     */
    Game::Game() : playerTurn(0), numOfPlayers(0),gameInit(0) {
        board.reserve(6); // Reserve space for up to 6 players
        // Initialize the game
    }

    /**
     * @brief Add a player to the game.
     * @param player The player to be added.
     * @throw std::runtime_error if the maximum number of players is reached.
     */
    void Game::addPlayer(Player* player){ // need to exception that init=0
        if(numOfPlayers >= 6) {
            throw std::runtime_error("Maximum number of players reached.");
        }
        board.push_back(player);
        numOfPlayers++;
        gameInit++;
    }

    /**
     * @brief Get the number of players in the game.
     * @return The number of players in reference (actualy it's also set).
     */
    int& Game::getNumOfPlayers(){
        return numOfPlayers;  
    }

    /**
     * @brief Get the name of the player that is currently taking their turn.
     * @return The name of the current player.
     * @throw std::runtime_error if the game has less than 2 players or more than 6 players.
     */
    std::string Game::turn(){ //need to add exception 2-6 players
        if(gameInit < 2 || gameInit > 6) {
            throw std::runtime_error("Game must have between 2 and 6 players.");
        }
       
        return board[playerTurn]->getName();
    }
    
    /**
     * @brief Get the names of all players currently in the game.
     * @return A vector of player names.
    */
    std::vector<std::string> Game::players(){
        std::vector<std::string> curPlayers;
        for(size_t i=0; i<board.size(); i++){
            if(board[i]->getIsAlived() == true){
                curPlayers.push_back(board[i]->getName());
            }
        }
        return curPlayers;
    }

    /**
     * @brief Removing a player frop game by adding him to the couped vector and decreasing the num of players by one.
     */
    void Game::removePlayer(Player* player){ 
        for(size_t i=0; i< board.size(); i++){
            if(player->getName()==board[i]->getName()){
                setCoupedPlayers(player);
                numOfPlayers--;
                if(numOfPlayers==1){
                    winner();
                }
                return;
            }
        }
        throw std::runtime_error("Player not found in the game.");

    }

    /**
     * @brief Move to the next player's turn.
     * If the current player is dead, skip to the next alive player.
     */
    void Game::nextTurn(){
        if (numOfPlayers <= 1) { 
           return; // No need to proceed if there's only one player left
        }
        do {
            playerTurn = (playerTurn + 1) % board.size();
        } while (!board[playerTurn]->getIsAlived());
    }

    /**
     * @brief Get the name of the last arrested player.
     * @return The name of the last arrested player.
     */
    std::string Game::lastArrested(){
        return lastArrest;
    }

    /**
     * @brief Overload the << operator to print the game status.
     * @param os The output stream.
     * @param game The game object.
     * @return The output stream.
     */
    std::ostream& operator<<(std::ostream& os, const Game& game){
        os << "Game status: " << std::endl;
        for (size_t i = 0; i < game.board.size(); i++) {
            os << game.board[i]->getName() << " is " 
               << (game.board[i]->getIsAlived() ? "alive" : "dead") 
               << " with " << game.board[i]->coins() << " coins"
               << " playing as: "<< game.board[i]->getRoll() << std::endl;
        }
        os << "Next turn: " << game.board[game.playerTurn]->getName() << std::endl;
        os << "Last arrested: " << game.lastArrest << std::endl;
        return os;
    }

 

    /**
     * @brief Get the winner of the game.
     * @return The name of the winning player.
     * @throw std::runtime_error if the game is not over yet or if there is a problem getting the winner.
     */
    std::string Game::winner(){
        int count=0;
        int index=-1;
        for(size_t i=0;i<board.size();i++){
            if(board[i]->getIsAlived()==true){
                index=i;
                count++;
            }
        }
        if(count==1){
            std::cout << "The winner is: " << board[index]->getName() <<"!"<< std::endl;
            return board[index]->getName();
        }
        else if (count>1){
            throw std::runtime_error("The game is not over yet.");     
           }
        else{
            throw std::runtime_error("There is problem getting winner");     
        }

    }
    /**
     * @brief pop the last player from the couped vector and set him to alive.
     */
    void Game::uncoupLastCoupedPlayer(){
        if(coupedPlayers.size() > 0){
            coupedPlayers.back()->setIsAlived(true);
            coupedPlayers.pop_back();
            numOfPlayers++;
        }
    }

}