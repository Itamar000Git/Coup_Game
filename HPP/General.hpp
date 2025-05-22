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
            

        public:
                General(Game &game, const std::string &name1);
                using Player::operator=; // Bring base class operator= into scope
                General &operator=(const General &other) {
                if (this == &other) {
                    return *this;
                }
                Player::operator=(other); // Call base class assignment operator
                return *this;
                }
                int coins() const;
                std::string getName();
                void undo( Player &player);
                
                void deleteLastMove();
                std::string getRoll();
                void setIsBlocked(bool block){
                    isBlocked = block;
                }
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
                void setPreventToBribe(bool block){
                    blockToBribe = block;
                }
                
                 void setIsAlivedGui(bool alive);
                 bool askToStayAlive();
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
                bool getIsBlocked()const{
                    return isBlocked;
                }

                 ~General(){}
        
    };
}


#endif