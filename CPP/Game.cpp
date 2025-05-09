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

    Game::Game() : playerTurn(0), numOfPlayers(0),gameInit(0) {
        board.reserve(6); // Reserve space for up to 6 players
        // Initialize the game
    }


    void Game::addPlayer(Player* player){ // need to exception that init=0
        board.push_back(player);
        numOfPlayers++;
    }
    int& Game::getNumOfPlayers(){
        return numOfPlayers;  
    }

    std::string Game::turn(){ //need to add exception 2-6 players
        if(gameInit==0){
            gameInit=1;
        }
        return board[playerTurn]->getName();
    }
    

    std::vector<std::string> Game::players(){
        std::vector<std::string> curPlayers;
        for(int i=0; i<board.size(); i++){
            if(board[i]->getIsAlived() == true){
                curPlayers.push_back(board[i]->getName());
            }
        }
        return curPlayers;
    }


    void Game::removePlayer(Player* player){ //when player removed is stull on the voard just not alive
        for(int i=0; i< board.size(); i++){
            if(player->getName()==board[i]->getName()){
                //board.erase(board.begin()+i);
                numOfPlayers--;
                if(numOfPlayers==1){
                    winner();
                }
                return;
            }
        }
        throw std::runtime_error("Player not found in the game.");

    }


    void Game::nextTurn(){
        if (numOfPlayers <= 1) { 
           return; // No need to proceed if there's only one player left
        }
        do {
            playerTurn = (playerTurn + 1) % board.size();
        } while (!board[playerTurn]->getIsAlived());
      // playerTurn= (playerTurn+1)%numOfPlayers;
    }
    std::string Game::lastArrested(){
        return lastArrest;
    }

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

 


    std::string Game::winner(){
        int count=0;
        int index=-1;
        for(int i=0;i<board.size();i++){
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


}