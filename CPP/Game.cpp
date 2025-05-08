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
            if(board[i]->isAlive() == true){
                curPlayers.push_back(board[i]->getName());
            }
        }
        return curPlayers;
    }


    void Game::removePlayer(Player* player){ //when player removed is stull on the voard just not alive
        for(int i=0; i< numOfPlayers; i++){
            if(player->getName()==board[i]->getName()){
                //board.erase(board.begin()+i);
                numOfPlayers--;
                return;
            }
        }
        throw std::runtime_error("Player not found in the game.");

    }


    void Game::nextTurn(){
        if (players().size() <= 1) { 
            throw std::runtime_error("Cannot proceed to the next turn: only one player remains.");
        }
        do {
            playerTurn = (playerTurn + 1) % board.size();
        } while (!board[playerTurn]->isAlive());
      // playerTurn= (playerTurn+1)%numOfPlayers;
    }


    std::string Game::winner(){
        int count=0;
        int index=-1;
        for(int i=0;i<numOfPlayers;i++){
            if(board[i]->isAlive()==true){
                index=i;
                count++;
            }
        }
        if(count==1){
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