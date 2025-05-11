//itamarbabai98@gmail.com

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <set>
#include <memory>
#include "HPP/Player.hpp"
#include "HPP/Governor.hpp"
#include "HPP/Spy.hpp"
#include "HPP/Baron.hpp"
#include "HPP/General.hpp"
#include "HPP/Judge.hpp"
#include "HPP/Merchant.hpp"
#include "HPP/Game.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "HPP/main.hpp"
using namespace std;
using namespace coup;


int main() {
    // sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Valgrind Test");

    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear(sf::Color::Black);
    //     window.display();
    // }

    // return 0;
    Game game{};
    int numPlayers = 0;
    vector<std::string> playerNames;
    mainwin(numPlayers, playerNames);
    
    vector<Player*> players;

    for (int i = 0; i < numPlayers; ++i) {
       // players.push_back(createRandomPlayer(game, playerNames[i]));
    }


    for (const auto &player : players) {
        std::cout << player->getName() << " is a " << player->getRoll() << std::endl;
    }

   
    for (auto player : players) {
        delete player;
    }

    
    cout << "Number of players: " << numPlayers << endl;
    cout << "Players: ";
    for (const auto& player : players) {
        cout << player << " ";
    }
    cout << endl;
   return 0;
}

void mainwin(int& numPlayers, vector<string>& players) {
    sf::RenderWindow mainwindow(sf::VideoMode(800, 600), "Coup");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        mainwindow.close();
        return ; 
    }

    sf::Text title("Coup", font, 60);
    title.setFillColor(sf::Color(50, 50, 50));
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 80);

    sf::RectangleShape button(sf::Vector2f(250, 70));
    button.setFillColor(sf::Color(180, 180, 250));
    button.setPosition(800 / 2 - 125, 300);

    sf::Text buttonText("Start", font, 36);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(800 / 2 - buttonText.getGlobalBounds().width / 2, 310);

    while (mainwindow.isOpen()) {
        sf::Event event;
        while (mainwindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mainwindow.close();

            if (event.type == sf::Event::MouseMoved) {
                if (button.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    button.setFillColor(sf::Color(120, 120, 200));
                else
                    button.setFillColor(sf::Color(180, 180, 250));
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(mainwindow);
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    mainwindow.close();
                    signIn(numPlayers, players); // move to input
                }
            }
        }

        mainwindow.clear(sf::Color(230, 230, 255));  // Pleasant light blue background
        mainwindow.draw(title);
        mainwindow.draw(button);
        mainwindow.draw(buttonText);
        mainwindow.display();
    }
    if(mainwindow.isOpen()){
        mainwindow.close();
    }
    return ;
}


void signIn(int& numPlayers, vector<string>& players) {
    sf::RenderWindow signInWindow(sf::VideoMode(500, 350), "Choose Number of Players");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    std::string inputText;
    sf::Text inputDisplay;
    inputDisplay.setFont(font);
    inputDisplay.setCharacterSize(30);
    inputDisplay.setFillColor(sf::Color::Black);
    inputDisplay.setPosition(250 - 100, 140);

    sf::Text prompt("Enter number of players (2 - 6):", font, 22);
    prompt.setFillColor(sf::Color(50, 50, 50));
    prompt.setPosition(250 - prompt.getGlobalBounds().width / 2, 80);

    sf::Text errorText("", font, 20);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(150, 180);

    sf::RectangleShape inputBox(sf::Vector2f(200, 50));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(150, 130);

    sf::RectangleShape button(sf::Vector2f(100, 50));
    button.setFillColor(sf::Color(180, 180, 250));
    button.setPosition(200, 230);

    sf::Text buttonText("OK", font, 24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(250 - buttonText.getGlobalBounds().width / 2, 240);

    bool validNumberEntered = false;
    int selectedNumber = 0;

    while (signInWindow.isOpen()) {
        sf::Event event;
        while (signInWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                signInWindow.close();

            if (event.type == sf::Event::TextEntered) {
                char c = static_cast<char>(event.text.unicode);
                if (c >= '2' && c <= '6') {
                    inputText = c;
                    selectedNumber = c - '0';
                    validNumberEntered = true;
                    errorText.setString("");
                } else {
                    inputText = "";
                    selectedNumber = 0;
                    validNumberEntered = false;
                    errorText.setString("Please enter a number between 2 and 6.");
                }
                inputDisplay.setString(inputText);
            }

            if (event.type == sf::Event::MouseMoved) {
                if (button.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    button.setFillColor(sf::Color(120, 120, 200));
                else
                    button.setFillColor(sf::Color(180, 180, 250));
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(signInWindow);
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (validNumberEntered) {
                        numPlayers = selectedNumber;
                        signInWindow.close();
                        get_members(numPlayers, players);
                        
                    } else {
                        errorText.setString("Please enter a number between 2 and 6.");
                    }
                }
            }
        }

        signInWindow.clear(sf::Color(245, 245, 255));
        signInWindow.draw(prompt);
        signInWindow.draw(inputBox);
        signInWindow.draw(inputDisplay);
        signInWindow.draw(errorText);
        signInWindow.draw(button);
        signInWindow.draw(buttonText);
        signInWindow.display();
    }
    if(signInWindow.isOpen()){
        signInWindow.close();
    }
    return ;
}


void get_members(int& num, vector<string>& players) {
    sf::RenderWindow window(sf::VideoMode(500, 150 + num * 60), "Player Names");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    std::vector<std::string> names(num, "");
    std::vector<sf::Text> texts(num);
    std::set<std::string> unique;
    std::string current;
    int index = 0;

    for (int i = 0; i < num; ++i) {
        texts[i].setFont(font);
        texts[i].setCharacterSize(20);
        texts[i].setFillColor(sf::Color::Black);
        texts[i].setPosition(50, 50 + i * 40);
    }

    sf::RectangleShape inputBox(sf::Vector2f(350, 30));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);

    sf::RectangleShape button(sf::Vector2f(120, 50));
    button.setFillColor(sf::Color(70, 130, 180));
    button.setPosition(180, 80 + num * 40);

    sf::Text buttonText("Submit", font, 24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(200, 90 + num * 40);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                char c = static_cast<char>(event.text.unicode);
                if (c == '\b') {
                    if (!current.empty()) current.pop_back();
                } else if (std::isalnum(c) || c == ' ') {
                    current += c;
                }
                texts[index].setString(current);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (current.empty() || unique.count(current)) {
                        texts[index].setString("Invalid or Duplicate");
                    } else {
                        names[index] = current;
                        unique.insert(current);
                        current = "";
                        ++index;
                    }
                    if (index == num) {
                        std::cout << "Players:\n";
                        for (auto &n : names)
                            std::cout << n << std::endl;
                        players = names;
                        window.close();
                    }
                }
            }
        }

        window.clear(sf::Color(250, 250, 250));
        for (int i = 0; i < num; ++i) {
            inputBox.setPosition(45, 45 + i * 40);
            window.draw(inputBox);
            window.draw(texts[i]);
        }
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }
    if(window.isOpen()){
        window.close();
    }
    return ;
}

// Player* createRandomPlayer(Game &game, const std::string &name) {
//     GameRolls roll = drawCard(); 
//     switch (roll) {
//         case GameRolls::Baron:
//             return new Baron(game, name);
//         case GameRolls::General:
//             return new General(game, name);
//         case GameRolls::Governor:
//             return new Governor(game, name);
//         case GameRolls::Judge:
//             return new Judge(game, name);
//         case GameRolls::Merchant:
//             return new Merchant(game, name);
//         case GameRolls::Spy:
//             return new Spy(game, name);
//         default:
//             throw std::runtime_error("Unknown roll");
//     }
//  }