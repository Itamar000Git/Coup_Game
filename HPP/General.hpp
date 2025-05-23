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
                General(Game &game, const std::string &name1); // Constructor for the General class
                using Player::operator=; // Bring base class operator= into scope

                General &operator=(const General &other) { // Assignment operator for the General class
                if (this == &other) {
                    return *this;
                }
                Player::operator=(other); // Call base class assignment operator
                return *this;
                }

                int coins() const; //returns the number of coins the player has
                std::string getName(); //returns the name of the player
                void undo( Player &player); // use to undo coup actions
                
                
                std::string getRoll(); //returns the role of the player
                void setIsBlocked(bool block){ //set the player to be blocked or not
                    isBlocked = block;
                }
                void setLastCoinNum(int num){ //set the last number of coins the player had
                    coinsNum=num;
                }
                int getLastCoinNum()const{ //returns the last number of coins the player had
                    return coinsNum;
                }

                bool getPreventToArrest() const{ //returns if the player is prevented to arrest
                    return preventToArrest;
                }
                void setPreventToArrest(bool block){ //set the player to be prevented to arrest
                    preventToArrest = block;
                    if(block == false){
                        game.setLastArrest("");
                    }
                }
                void setPreventToBribe(bool block){ //set the player to be prevented to bribe or not
                    blockToBribe = block;
                }
                
                 void setIsAlivedGui(bool alive); //function that use gui for asking if the player want to stay alive
                 bool askToStayAlive(); //function that ask the player if he want to stay alive from terminal

                /**
                 * * @brief Implement the option of the General to savr himself from death
                 * @param alive The status of the player
                 * @throws std::runtime_error if there is unvalid answer from the player
                 */
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

                 ~General(){
                    // Destructor for the General class
                    // No dynamic memory allocation, so nothing to clean up
                 }
        
    };
}


#endif