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
#include <ctime>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "HPP/main.hpp"
using namespace std;
using namespace coup;


int main() {

    Game game_2{};
    int numPlayers = 0;
    vector<std::string> playerNames;
    mainwin(numPlayers, playerNames);
    
    vector<Player*> players(numPlayers);
    for (int i = 0; i < numPlayers; ++i) {
        players[i] = nullptr;
    }
    for (int i = 0; i < numPlayers; ++i) {
        players[i]=drawCard(playerNames[i], game_2);
    }

    //boardwin(players, numPlayers, game_2);
     displayCoupBoard(players);
    for (int i = 0; i < numPlayers; ++i) {
        std::cout << players[i]->getName() << " is a " << players[i]->getRoll() << std::endl;
    }

   
    for (auto player : players) {
        delete player;
    }

    

   return 0;
}

Player* drawCard(std::string name, Game &game) {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned int>(time(0))); // Initialize random seed
        initialized = true;
    }
    int randomNum = rand() % 6; // Random number between 0 and 5
    switch (randomNum) {
        case 0: return new Baron(game, name);
        case 1: return new General(game, name);
        case 2: return new Governor(game, name);
        case 3: return new Judge(game, name);
        case 4: return new Merchant(game, name);
        case 5: return new Spy(game, name);
    }
   
    //return Player; // Default case, should not happen
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



void signIn(int& numPlayers, std::vector<std::string>& players) {
    sf::RenderWindow window(sf::VideoMode(500, 350), "Choose Number of Players");

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    std::string inputText;
    sf::Text inputDisplay("", font, 36);
    inputDisplay.setFillColor(sf::Color::Black);
    inputDisplay.setPosition(250 - 10, 130);

    sf::Text prompt("Enter number of players (2 - 6):", font, 22);
    prompt.setFillColor(sf::Color(50, 50, 50));
    prompt.setPosition(250 - prompt.getGlobalBounds().width / 2, 70);

    sf::Text errorText("", font, 20);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(125, 180);

    sf::RectangleShape inputBox(sf::Vector2f(100, 50));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(200, 120);

    sf::RectangleShape button(sf::Vector2f(100, 50));
    button.setFillColor(sf::Color(180, 180, 250));
    button.setPosition(200, 230);

    sf::Text buttonText("OK", font, 24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(250 - buttonText.getGlobalBounds().width / 2, 240);

    bool validInput = false;
    int selectedNumber = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::TextEntered) {
                char c = static_cast<char>(event.text.unicode);
                if (c == '\b') {
                    inputText.clear();
                    inputDisplay.setString("");
                } else if (std::isdigit(c)) {
                    if (c >= '2' && c <= '6') {
                        inputText = c;
                        selectedNumber = c - '0';
                        validInput = true;
                        errorText.setString("");
                        inputDisplay.setString(inputText);
                    } else {
                        inputText = "";
                        inputDisplay.setString("");
                        errorText.setString("Only numbers between 2 and 6 are allowed.");
                        validInput = false;
                    }
                }
            }

  
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (validInput) {
                    numPlayers = selectedNumber;
                    window.close();
                    get_members(numPlayers, players);
                } else {
                    errorText.setString("Please enter a valid number (2-6).");
                }
            }


            if (event.type == sf::Event::MouseMoved) {
                if (button.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    button.setFillColor(sf::Color(120, 120, 200));
                else
                    button.setFillColor(sf::Color(180, 180, 250));
            }


            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (validInput) {
                        numPlayers = selectedNumber;
                        window.close();
                        get_members(numPlayers, players);
                    } else {
                        errorText.setString("Please enter a valid number (2-6).");
                    }
                }
            }
        }

        window.clear(sf::Color(245, 245, 255));
        window.draw(prompt);
        window.draw(inputBox);
        window.draw(inputDisplay);
        window.draw(errorText);
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }
}

void get_members(int& num, std::vector<std::string>& players) {
    sf::RenderWindow window(sf::VideoMode(500, 250), "Enter Player Names");

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    std::vector<std::string> names;
    std::set<std::string> unique;

    int index = 0;
    std::string current;
    sf::Text promptText("", font, 22);
    promptText.setFillColor(sf::Color::Black);
    promptText.setPosition(50, 40);

    sf::Text inputText("", font, 22);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(50, 80);

    sf::RectangleShape inputBox(sf::Vector2f(400, 35));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(45, 75);

    sf::RectangleShape button(sf::Vector2f(120, 40));
    button.setFillColor(sf::Color(70, 130, 180));
    button.setPosition(180, 130);

    sf::Text buttonText("Submit", font, 22);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(200, 137);

    sf::Clock errorClock;
    std::string errorMsg = "";
    sf::Text errorText("", font, 18);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(50, 180);

    while (window.isOpen()) {
        promptText.setString("Enter name for player " + std::to_string(index + 1) + " of " + std::to_string(num));

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                char c = static_cast<char>(event.text.unicode);
                if (c == '\b' && !current.empty()) {
                    current.pop_back();
                } else if ((std::isalnum(c) || c == ' ') && current.size() < 20) {
                    current += c;
                }
                inputText.setString(current);
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                event.type = sf::Event::MouseButtonPressed; // Simulate button press
                event.mouseButton.button = sf::Mouse::Left;
                event.mouseButton.x = button.getPosition().x + 10;
                event.mouseButton.y = button.getPosition().y + 10;
                sf::Event::MouseButtonEvent mouseEvent = event.mouseButton;
                sf::Mouse::setPosition(sf::Vector2i(mouseEvent.x, mouseEvent.y), window);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (current.empty()) {
                        errorMsg = "Name cannot be empty.";
                        errorClock.restart();
                    } else if (unique.count(current)) {
                        errorMsg = "Name already used.";
                        errorClock.restart();
                    } else {
                        names.push_back(current);
                        unique.insert(current);
                        current.clear();
                        inputText.setString("");
                        index++;
                        if (index == num) {
                            players = names;
                            window.close();
                        }
                    }
                }
            }
        }

        // Clear error message after 2 seconds
        if (errorClock.getElapsedTime().asSeconds() > 2)
            errorMsg = "";

        errorText.setString(errorMsg);

        window.clear(sf::Color(250, 250, 250));
        window.draw(promptText);
        window.draw(inputBox);
        window.draw(inputText);
        window.draw(button);
        window.draw(buttonText);
        window.draw(errorText);
        window.display();
    }
}


void displayCoupBoard(const vector<Player*>& players) {
    sf::RenderWindow window(sf::VideoMode(1200, 160 + players.size() * 80), "Coup Board");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    sf::Text title("Coup Board", font, 30);
    title.setFillColor(sf::Color::Black);
    title.setPosition(500 - title.getGlobalBounds().width / 2, 20);

    std::vector<sf::Text> playerTexts(players.size());
    std::vector<sf::RectangleShape> gatherButtons(players.size());
    std::vector<sf::RectangleShape> taxButtons(players.size());
    std::vector<sf::RectangleShape> bribeButtons(players.size());
    std::vector<sf::RectangleShape> arrestButtons(players.size());
    std::vector<sf::RectangleShape> sanctionButtons(players.size());
    std::vector<sf::RectangleShape> coupButtons(players.size());
    std::vector<sf::Text> gatherTexts(players.size());
    std::vector<sf::Text> taxTexts(players.size());
    std::vector<sf::Text> bribeTexts(players.size());
    std::vector<sf::Text> arrestTexts(players.size());
    std::vector<sf::Text> sanctionTexts(players.size());
    std::vector<sf::Text> coupTexts(players.size());
    std::vector<sf::RectangleShape> investButtons(players.size());
    std::vector<sf::Text> investTexts(players.size());


    for (size_t i = 0; i < players.size(); ++i) {
        // Player info
        std::string playerInfo = players[i]->getName() + " - " + players[i]->getRoll();
        playerTexts[i].setFont(font);
        playerTexts[i].setCharacterSize(20);
        playerTexts[i].setFillColor(sf::Color::Black);
        playerTexts[i].setString(playerInfo);
        playerTexts[i].setPosition(50, 80 + i * 80);

        // Gather button
        gatherButtons[i].setSize(sf::Vector2f(100, 40));
        gatherButtons[i].setFillColor(sf::Color(180, 180, 250));
        gatherButtons[i].setPosition(300, 80 + i * 80);

        gatherTexts[i].setFont(font);
        gatherTexts[i].setCharacterSize(18);
        gatherTexts[i].setFillColor(sf::Color::White);
        gatherTexts[i].setString("Gather");
        gatherTexts[i].setPosition(300 + 25, 80 + i * 80 + 5);

        // Tax button
        taxButtons[i].setSize(sf::Vector2f(100, 40));
        taxButtons[i].setFillColor(sf::Color(180, 250, 180));
        taxButtons[i].setPosition(420, 80 + i * 80);

        taxTexts[i].setFont(font);
        taxTexts[i].setCharacterSize(18);
        taxTexts[i].setFillColor(sf::Color::White);
        taxTexts[i].setString("Tax");
        taxTexts[i].setPosition(420 + 35, 80 + i * 80 + 5);

        // Bribe button
        bribeButtons[i].setSize(sf::Vector2f(100, 40));
        bribeButtons[i].setFillColor(sf::Color(250, 180, 180));
        bribeButtons[i].setPosition(540, 80 + i * 80);

        bribeTexts[i].setFont(font);
        bribeTexts[i].setCharacterSize(18);
        bribeTexts[i].setFillColor(sf::Color::White);
        bribeTexts[i].setString("Bribe");
        bribeTexts[i].setPosition(540 + 25, 80 + i * 80 + 5);

        // Arrest button
        arrestButtons[i].setSize(sf::Vector2f(100, 40));
        arrestButtons[i].setFillColor(sf::Color(200, 200, 200));
        arrestButtons[i].setPosition(660, 80 + i * 80);

        arrestTexts[i].setFont(font);
        arrestTexts[i].setCharacterSize(18);
        arrestTexts[i].setFillColor(sf::Color::White);
        arrestTexts[i].setString("Arrest");
        arrestTexts[i].setPosition(660 + 25, 80 + i * 80 + 5);

        // Sanction button
        sanctionButtons[i].setSize(sf::Vector2f(100, 40));
        sanctionButtons[i].setFillColor(sf::Color(200, 150, 250));
        sanctionButtons[i].setPosition(780, 80 + i * 80);

        sanctionTexts[i].setFont(font);
        sanctionTexts[i].setCharacterSize(18);
        sanctionTexts[i].setFillColor(sf::Color::White);
        sanctionTexts[i].setString("Sanction");
        sanctionTexts[i].setPosition(780 + 10, 80 + i * 80 + 5);

        // Coup button
        coupButtons[i].setSize(sf::Vector2f(100, 40));
        coupButtons[i].setFillColor(sf::Color(250, 100, 100));
        coupButtons[i].setPosition(900, 80 + i * 80);

        coupTexts[i].setFont(font);
        coupTexts[i].setCharacterSize(18);
        coupTexts[i].setFillColor(sf::Color::White);
        coupTexts[i].setString("Coup");
        coupTexts[i].setPosition(900 + 25, 80 + i * 80 + 5);

        if (players[i]->getRoll() == "Baron") {
            investButtons[i].setSize(sf::Vector2f(100, 40));
            investButtons[i].setFillColor(sf::Color(100, 200, 250));
            investButtons[i].setPosition(1020, 80 + i * 80);

            investTexts[i].setFont(font);
            investTexts[i].setCharacterSize(18);
            investTexts[i].setFillColor(sf::Color::White);
            investTexts[i].setString("Invest");
            investTexts[i].setPosition(1020 + 20, 80 + i * 80 + 5);
        }   
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (size_t i = 0; i < players.size(); ++i) {
                    if (gatherButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Gather!\n";
                        players[i]->gather();
                    }
                    if (taxButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Tax!\n";
                        players[i]->tax();
                    }
                    if (bribeButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Bribe!\n";
                        players[i]->bride();
                    }
                    if (arrestButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Arrest!\n";
                        players[i]->arrest(*players[i]); // Example: arresting themselves
                    }
                    if (sanctionButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Sanction!\n";
                        players[i]->sanction(*players[i]); // Example: sanctioning themselves
                    }
                    if (coupButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Coup!\n";
                        players[i]->coup(*players[i]); // Example: coup against themselves
                    }
                    if (players[i]->getRoll() == "Baron" && investButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Invest!\n";
                       players[i]->invest();
                    }
                }
            }
        }

        window.clear(sf::Color(240, 240, 240));
        window.draw(title);
        for (size_t i = 0; i < players.size(); ++i) {
            window.draw(playerTexts[i]);
            window.draw(gatherButtons[i]);
            window.draw(gatherTexts[i]);
            window.draw(taxButtons[i]);
            window.draw(taxTexts[i]);
            window.draw(bribeButtons[i]);
            window.draw(bribeTexts[i]);
            window.draw(arrestButtons[i]);
            window.draw(arrestTexts[i]);
            window.draw(sanctionButtons[i]);
            window.draw(sanctionTexts[i]);
            window.draw(coupButtons[i]);
            window.draw(coupTexts[i]);
            if (players[i]->getRoll() == "Baron") {
                window.draw(investButtons[i]);
                window.draw(investTexts[i]);
            }
        }
        window.display();
    }
}