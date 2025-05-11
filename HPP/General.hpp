//itamarbabai98@gmail.com
#ifndef GENERAL_HPP
#define GENERAL_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Player.hpp"
#include "Game.hpp"

namespace coup{  
    class General:public Player{
        private:
            // Game &game;
            // std::string name;
            // int coinsNum;
            // std::string role;
            // bool Alive;
            // int playerIndex;
            // int playerTurn;
            // std::vector<std::string> lastMove;

        public:
                General(Game &game, const std::string &name1);
                int coins() const;
                std::string getName();
                void undo( Player &player);
                //void gather();
                void tax();
                void bride();
                void arrest( Player &player);
                void sanction(Player &player);
                void coup( Player &player);
                void deleteLastMove();
                std::string getRoll();
                void setLastCoinNum(int num){
                    coinsNum=num;
                }
                int getLastCoinNum()const{
                    return coinsNum;
                }

                bool getPreventToArrest() const{
                    return preventToArrest;
                }
                void setPreventToArrest(bool block){
                    preventToArrest = block;
                    if(block == false){
                        game.setLastArrest("");
                    }
                }
                void setPreventToBride(bool block){
                    blockToBride = block;
                }

                void setIsAlived(bool alive){
                    if(alive==false && coinsNum>=5){
                        std::cout<<"General Do you want to pay 5 coins to stay alive? y-Yes n-No"<<std::endl;
                        std::string answer;
                        std::cin>>answer;
                        if(answer=="n"){
                            Alive = alive;
                            return;
                        }
                        if(answer!="y"){
                            std::cout<<"Invalid answer"<<std::endl;
                            return;
                        }
                        coinsNum=coinsNum-5;
                        std::cout<<"General pay 5 coins to stay alive"<<std::endl;
                        return;
                    }
                    Alive = alive;
                }
                 bool getIsAlived(){
                    return Alive;
                }
                

                 ~General(){}
        
    };
}


#endif