//itamarbabai98@gmail.com
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "../HPP/Player.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/General.hpp"

namespace coup{  
    
    /**
     * @brief Constructor for the General class.
     * @param game The game instance.
     * @param name1 The name of the player.
     */
   General::General(Game &game, const std::string &name1)
   : Player(game, name1) { 
       this->role = "General"; 
       playerIndex= game.getNumOfPlayers();
       game.addPlayer(this); 
       Alive = true;
       coinsNum = 0;   
       playerTurn = 0;
       isBlocked = false;
       freeMoves=0;
       blockToBribe = false;
       preventToArrest = false;

   }
    int General::coins() const{//returns the number of coins the player has
        return coinsNum;
     }
      std::string General::getName(){
        return name;
     }
    std::string General::getRoll(){
        return role;
    }

    /**
     * @brief Override the undo method for the General class, which allows the General to undo the last coup of a player by paying 5 coins.
     * @param player The player to be undo the last coup action.
     * @throws std::runtime_error if the player is dead (each one), if there is no last move to undo,
     *  if the last move is not coup, if the player has less than 5 coins, if the player is blocked by bribe.
     */
    void General::undo( Player &player){
        if(getIsAlived()==false){ //the player is dead
            throw std::runtime_error("You cant coup a dead player");
            return;
        }
        
        if(player.getIsAlived()==false){ //the other player is dead
            throw std::runtime_error("You cant coup a dead player");
            return;
        }
        if(this==&player){ //the player uncouping himself (implement in a different way)
            throw std::runtime_error("You cant arrest yourself");
        }
        if(player.getLastMove().empty()){ //there is no last move to undo
            throw std::runtime_error("There is no last move to undo");
            return;
        }
        std::string last = player.getLastMove().back();
        if(last!="coup"){ //the last move is not coup
            throw std::runtime_error("Last move is not coup");
            return;
        }
        if(coinsNum<5){ //the player has less than 5 coins
            throw std::runtime_error("You dont have enough coins");
            return;
        }
       
        coinsNum=coinsNum-5; //pay 5 coins to the bank
        game.uncoupLastCoupedPlayer(); //uncoup the last couped player
        player.setLastMove("undo coup");
        std::cout <<"undo coup with: " << name<< " that is "<< role<<std::endl;
        
    }
    
    /**
     * @brief Use this method to set the alive status of the player when using GUI.
     * @param alive The alive status to set.
     */
    void General::setIsAlivedGui(bool alive) {
        if (alive == false && coinsNum >= 5) {
            bool check = askToStayAlive(); // Ask the player if they want to pay 5 coins to stay alive
            if (check == false) {
                Alive = alive;
                return;
            } else {
                coinsNum -= 5;
                std::cout << "General paid 5 coins to stay alive" << std::endl;
                return;
            }
        }
        Alive = alive;
        
    }
    /**
     * @brief Ask the player if they want to pay 5 coins to stay alive using a GUI.
     * @return true if the player wants to stay alive, false otherwise.
     */
    bool General::askToStayAlive() {
        sf::RenderWindow window(sf::VideoMode(400, 200), "Stay Alive?");
        sf::Font font;
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cerr << "Failed to load font\n";
            return false;
        }

        sf::Text questionText("Do you want to pay 5 coins to stay alive?", font, 18); // Create the question text
        questionText.setFillColor(sf::Color::Black);
        questionText.setPosition(20, 50);

        sf::RectangleShape yesButton(sf::Vector2f(100, 50));
        yesButton.setFillColor(sf::Color(100, 200, 100));
        yesButton.setPosition(50, 120);

        sf::Text yesText("YES", font, 20);
        yesText.setFillColor(sf::Color::White);
        yesText.setPosition(75, 130);

        sf::RectangleShape noButton(sf::Vector2f(100, 50));
        noButton.setFillColor(sf::Color(200, 100, 100));
        noButton.setPosition(250, 120);

        sf::Text noText("NO", font, 20);
        noText.setFillColor(sf::Color::White);
        noText.setPosition(275, 130);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return false; 
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (yesButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) { //getting the mouse position on yes button
                        window.close();
                        return true; 
                    }

                    if (noButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) { //getting the mouse position on no button
                        window.close();
                        return false; 
                    }
                }
            }

            window.clear(sf::Color(240, 240, 240));
            window.draw(questionText);
            window.draw(yesButton);
            window.draw(yesText);
            window.draw(noButton);
            window.draw(noText);
            window.display();
        }

        return false; 
    }

}