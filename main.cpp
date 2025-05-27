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
using namespace coup;

/**
 * @brief Entry point of the Coup game GUI application.
 * Initializes the game, prompts for player information via GUI,
 * creates players, starts the game board display, deletes players, and exits.
 * @return int Returns 0 on successful execution.
 */
int main() {

    Game game_2{};
    int numPlayers = 0;
    std::vector<std::string> playerNames;
    mainwin(numPlayers, playerNames); // Call the main window function to get the number of players and their names
    
    std::vector<Player*> players(numPlayers);
    for (int i = 0; i < numPlayers; ++i) { // initialize the players vector
        players[i] = nullptr;
    }
    for (int i = 0; i < numPlayers; ++i) {
        players[i]=drawCard(playerNames[i], game_2); // Create a new player with a random role
    }


     displayCoupBoard(players,game_2); // Display the game board with the players


   
    for (auto player : players) { // Clean up the dynamically allocated players
        delete player;
    }

   return 0;
}

/**
 * @brief Draws a random card (player role) for a player.
 * @param name The name of the player.
 * @param game The game instance.
 * @return A pointer to the created Player object.
 */
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
   
}

/**
 * @brief Displays the main window for the game.
 * Prompts the user to start the game,and moves to the sign-in screen.
 * @param numPlayers Reference to the number of players.
 * @param players Reference to the vector of player names.
 * @throws std::runtime_error if the font fails to load. 
 * 
 */
void mainwin(int& numPlayers, std::vector<string>& players) {
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


/**
 * @brief Prompts the user to enter the number of players and their names.
 * Gets the number of players and their names from the user.
 * @param numPlayers Reference to the number of players.
 * @param players Reference to the vector of player names.
 * @throws std::runtime_error if the font fails to load.
 * Shows an error message if the input is invalid.
 */
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

    sf::Text prompt("Enter number of players (2 - 6):", font, 22); //Prompt text
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
                    if (c >= '2' && c <= '6') { //if the input valid update selected number
                        inputText = c;
                        selectedNumber = c - '0';
                        validInput = true;
                        errorText.setString("");
                        inputDisplay.setString(inputText);
                    } else { //if the input not valid show an error
                        inputText = "";
                        inputDisplay.setString("");
                        errorText.setString("Only numbers between 2 and 6 are allowed.");
                        validInput = false;
                    }
                }
            }

            // Check for Enter key press
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (validInput) {
                    numPlayers = selectedNumber; //update number of player refernce
                    window.close();
                    get_members(numPlayers, players); //call the get member method
                } else {
                    errorText.setString("Please enter a valid number (2-6).");
                }
            }

            // Check for mouse movement
            if (event.type == sf::Event::MouseMoved) {
                if (button.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    button.setFillColor(sf::Color(120, 120, 200));
                else
                    button.setFillColor(sf::Color(180, 180, 250));
            }

            // Check for mouse button press
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


/**
 * @brief Prompts the user to enter player names.
 * @param num Reference to the number of players.
 * @param players Reference to the vector of player names.
 * @throws std::runtime_error if the font fails to load.
 * Shows an error message if the input is invalid.
 */
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
        // Update prompt text with the current player number
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
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // Check if the button is clicked
                    if (current.empty()) { // Check if the input is empty
                        errorMsg = "Name cannot be empty."; 
                        errorClock.restart();
                    } else if (unique.count(current)) { // Check if the name is already used
                        errorMsg = "Name already used.";
                        errorClock.restart();
                    } else {
                        names.push_back(current); // Add the name to the list
                        unique.insert(current);
                        current.clear();
                        inputText.setString("");
                        index++;
                        if (index == num) { // If all names are entered
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


/**
 * @brief Displays the number of coins a player has in a separate window.
 * @param player Pointer to the Player object.
 * @throws std::runtime_error if the font fails to load.
 */
    void displayCoins(const Player* player){
        sf::RenderWindow window(sf::VideoMode(300, 200), "Player Coins");
        sf::Font font;
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cerr << "Failed to load font\n";
            return;
        }

        sf::Text text("Coins: " + std::to_string(player->coins()), font, 24); // Display the number of coins
        text.setFillColor(sf::Color::Black);
        text.setPosition(50, 50);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) { // Show the number of coins until the user closes the window
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color(255, 255, 255));
            window.draw(text);
            window.display();
        }
        window.close();
    }

/**
 * @brief Updates the coin texts for each player.
 * @param coinTexts Vector of sf::Text objects for displaying coins.
 * @param players Vector of Player pointers.
 * @throws std::runtime_error if the font fails to load.
 */
    void updateCoinTexts(std::vector<sf::Text>& coinTexts, const vector<Player*>& players) {
        for (size_t i = 0; i < players.size(); ++i) {
            coinTexts[i].setString("Coins: " + std::to_string(players[i]->coins())); // Update the coin text for each player
        }
    }

/**
 * @brief Updates the alive texts for each player.
 * @param aliveTexts Vector of sf::Text objects for displaying alive status.
 * @param players Vector of Player pointers.
 * @throws std::runtime_error if the font fails to load.
 * */
    void updateAliveTexts(std::vector<sf::Text>& aliveTexts,const vector<Player*>& players){
        for (size_t i = 0; i < players.size(); ++i) { // Update the alive text for each player
            if (players[i]->getIsAlived()) {
                aliveTexts[i].setString("Alive"); 
                aliveTexts[i].setFillColor(sf::Color::Green);
            } else {
                aliveTexts[i].setString("Dead");
                aliveTexts[i].setFillColor(sf::Color::Red);

            }
        }
    }

/**
 * @brief Displays the Coup game board with player information and actions.
 * @param players Vector of Player pointers.
 * @param game Reference to the Game object.
 * @throws std::runtime_error if the font fails to load.
 * Shows the game board with player names, coins, and action buttons.
 * Handles user interactions for various actions like gathering, taxing, bribing, etc.
 */
void displayCoupBoard(const std::vector<Player*>& players, Game &game) {
    sf::RenderWindow window(sf::VideoMode(1550, 250 + players.size() * 80), "Coup Board");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    sf::Text playerTurnText("Player Turn: " + game.turn(), font, 24);
    playerTurnText.setFillColor(sf::Color::Black);
    playerTurnText.setPosition(50, 250 + players.size() * 80 - 80);

    sf::Text playerLastArrested("Last Arrested: " + game.lastArrested(), font, 24);
    playerLastArrested.setFillColor(sf::Color::Black);
    playerLastArrested.setPosition(50, 250 + players.size() * 80 - 50);

    sf::Text title("Coup Board", font, 30);
    title.setFillColor(sf::Color::Black);
    title.setPosition(750 - title.getGlobalBounds().width / 2, 20);
    std::vector<sf::Text> coinTexts(players.size());
    std::vector<sf::Text> playerTexts(players.size());
    std::vector<sf::Text> aliveTexts(players.size());
 
    std::vector<sf::CircleShape> blockToBribeCircles(players.size());
    std::vector<sf::CircleShape> preventArrestCircles(players.size());
    std::vector<sf::CircleShape> sanctionedCircles(players.size());




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
    std::vector<sf::RectangleShape> showCoinsButtons(players.size());
    std::vector<sf::Text> showCoinsTexts(players.size());
    std::vector<sf::RectangleShape> prevArrestButtons(players.size());
    std::vector<sf::Text> prevArrestTexts(players.size());
    std::vector<sf::RectangleShape> undoButtons(players.size());
    std::vector<sf::Text> undoTexts(players.size());
    std::vector<sf::RectangleShape> skipButtons(players.size());
    std::vector<sf::Text> skipTexts(players.size());


    
    for (size_t i = 0; i < players.size(); ++i) { // Loop through each player to update their information
        std::string playerInfo = players[i]->getName() + " - " + players[i]->getRoll();

        if (players[i]->getIsAlived()) {
            aliveTexts[i].setString("Alive");
             aliveTexts[i].setFillColor(sf::Color::Green);
        } else {
            aliveTexts[i].setString("Dead");
            aliveTexts[i].setFillColor(sf::Color::Red);
        }
 
        // Set up the text and buttons for each player
        aliveTexts[i].setFont(font);
        aliveTexts[i].setCharacterSize(20);
        aliveTexts[i].setPosition(130, 80 + i * 80);

        playerTexts[i].setFont(font);
        playerTexts[i].setCharacterSize(20);
        playerTexts[i].setFillColor(sf::Color::Black);
        playerTexts[i].setString(playerInfo);
        playerTexts[i].setPosition(200, 80 + i * 80);

        coinTexts[i].setFont(font);
        coinTexts[i].setCharacterSize(18);
        coinTexts[i].setFillColor(sf::Color::Blue);
        coinTexts[i].setString("Coins: " + std::to_string(players[i]->coins()));
        coinTexts[i].setPosition(350, 80 + i * 80);

        gatherButtons[i].setSize(sf::Vector2f(110, 40));
        gatherButtons[i].setFillColor(sf::Color (50, 50, 150));
        gatherButtons[i].setPosition(450, 80 + i * 80);

        gatherTexts[i].setFont(font);
        gatherTexts[i].setCharacterSize(18);
        gatherTexts[i].setFillColor(sf::Color::White);
        gatherTexts[i].setString("Gather");
        gatherTexts[i].setPosition(450 + 25, 80 + i * 80 + 5);

        taxButtons[i].setSize(sf::Vector2f(110, 40));
        taxButtons[i].setFillColor(sf::Color (50, 150, 50));
        taxButtons[i].setPosition(570, 80 + i * 80);

        taxTexts[i].setFont(font);
        taxTexts[i].setCharacterSize(18);
        taxTexts[i].setFillColor(sf::Color::White);
        taxTexts[i].setString("Tax");
        taxTexts[i].setPosition(570 + 35, 80 + i * 80 + 5);

        bribeButtons[i].setSize(sf::Vector2f(110, 40));
        bribeButtons[i].setFillColor(sf::Color (150, 50, 50));
        bribeButtons[i].setPosition(690, 80 + i * 80);

        bribeTexts[i].setFont(font);
        bribeTexts[i].setCharacterSize(18);
        bribeTexts[i].setFillColor(sf::Color::White);
        bribeTexts[i].setString("Bribe");
        bribeTexts[i].setPosition(690 + 25, 80 + i * 80 + 5);

        arrestButtons[i].setSize(sf::Vector2f(110, 40));
        arrestButtons[i].setFillColor(sf::Color (100, 100, 100));
        arrestButtons[i].setPosition(810, 80 + i * 80);

        arrestTexts[i].setFont(font);
        arrestTexts[i].setCharacterSize(18);
        arrestTexts[i].setFillColor(sf::Color::White);
        arrestTexts[i].setString("Arrest");
        arrestTexts[i].setPosition(810 + 25, 80 + i * 80 + 5);

        sanctionButtons[i].setSize(sf::Vector2f(110, 40));
        sanctionButtons[i].setFillColor(sf::Color (100, 50, 150));
        sanctionButtons[i].setPosition(930, 80 + i * 80);

        sanctionTexts[i].setFont(font);
        sanctionTexts[i].setCharacterSize(18);
        sanctionTexts[i].setFillColor(sf::Color::White);
        sanctionTexts[i].setString("Sanction");
        sanctionTexts[i].setPosition(930 + 10, 80 + i * 80 + 5);

        coupButtons[i].setSize(sf::Vector2f(110, 40));
        coupButtons[i].setFillColor(sf::Color (150, 0, 0));
        coupButtons[i].setPosition(1050, 80 + i * 80);

        coupTexts[i].setFont(font);
        coupTexts[i].setCharacterSize(18);
        coupTexts[i].setFillColor(sf::Color::White);
        coupTexts[i].setString("Coup");
        coupTexts[i].setPosition(1050 + 25, 80 + i * 80 + 5);

        skipButtons[i].setSize(sf::Vector2f(110, 40));
        skipButtons[i].setFillColor(sf::Color (30, 120, 30));
        skipButtons[i].setPosition(1170, 80 + i * 80);

        skipTexts[i].setFont(font);
        skipTexts[i].setCharacterSize(18);
        skipTexts[i].setFillColor(sf::Color::White);
        skipTexts[i].setString("Skip");
        skipTexts[i].setPosition(1170 + 27, 80 + i * 80 + 5);

        // Set up the buttons and texts for the Baron unique actions
        if (players[i]->getRoll() == "Baron") {
            investButtons[i].setSize(sf::Vector2f(110, 40));
            investButtons[i].setFillColor(sf::Color (200, 100, 0));
            investButtons[i].setPosition(1290, 80 + i * 80);

            investTexts[i].setFont(font);
            investTexts[i].setCharacterSize(18);
            investTexts[i].setFillColor(sf::Color::White);
            investTexts[i].setString("Invest");
            investTexts[i].setPosition(1290 + 25, 80 + i * 80 + 5);
        }

        // Set up the buttons and texts for the Spy unique actions
        if (players[i]->getRoll() == "Spy") {
            showCoinsButtons[i].setSize(sf::Vector2f(110, 40));
            showCoinsButtons[i].setFillColor(sf::Color (0, 100, 150));
            showCoinsButtons[i].setPosition(1290, 80 + i * 80);

            showCoinsTexts[i].setFont(font);
            showCoinsTexts[i].setCharacterSize(18);
            showCoinsTexts[i].setFillColor(sf::Color::White);
            showCoinsTexts[i].setString("Coins");
            showCoinsTexts[i].setPosition(1290 + 20, 80 + i * 80 + 5);

            prevArrestButtons[i].setSize(sf::Vector2f(110, 40));
            prevArrestButtons[i].setFillColor(sf::Color (100, 100, 150));
            prevArrestButtons[i].setPosition(1410, 80 + i * 80);

            prevArrestTexts[i].setFont(font);
            prevArrestTexts[i].setCharacterSize(18);
            prevArrestTexts[i].setFillColor(sf::Color::White);
            prevArrestTexts[i].setString("PrevArrest");
            prevArrestTexts[i].setPosition(1410 + 10, 80 + i * 80 + 5);
        }

        // Set up the buttons and texts for the Governor, General, Judge unique actions
        if (players[i]->getRoll() == "Governor" || players[i]->getRoll() == "General" || players[i]->getRoll() == "Judge") {
            undoButtons[i].setSize(sf::Vector2f(110, 40));
            undoButtons[i].setFillColor(sf::Color (50, 100, 150));
            undoButtons[i].setPosition(1290, 80 + i * 80);

            undoTexts[i].setFont(font);
            undoTexts[i].setCharacterSize(18);
            undoTexts[i].setFillColor(sf::Color::White);
            undoTexts[i].setString("Undo");
            undoTexts[i].setPosition(1290 + 25, 80 + i * 80 + 5);
        }

        // Create the circles for block to bribe, prevent arrest, and sanctioned
         sf::CircleShape blockToBribeCircle(10);
        blockToBribeCircle.setPosition(20, 80 + i * 80 + 5);
        if (players[i]->isBlockToBribe()) {
            blockToBribeCircle.setFillColor(sf::Color(255, 165, 0)); // Orange
        } else {
            blockToBribeCircle.setFillColor(sf::Color(200, 200, 200)); // Gray
        }
        blockToBribeCircles[i] = blockToBribeCircle;

        // Prevent Arrest Circle
        sf::CircleShape preventArrestCircle(10);
        preventArrestCircle.setPosition(50, 80 + i * 80 + 5);
        if (players[i]->getPreventToArrest()) {
            preventArrestCircle.setFillColor(sf::Color::Blue); // Blue
        } else {
            preventArrestCircle.setFillColor(sf::Color(200, 200, 200)); // Gray
        }
        preventArrestCircles[i] = preventArrestCircle;

        // Sanctioned Circle
        sf::CircleShape sanctionedCircle(10);
        sanctionedCircle.setPosition(80, 80 + i * 80 + 5);
        if (players[i]->getIsBlocked()) {
            sanctionedCircle.setFillColor(sf::Color::Magenta); // Magenta
        } else {
            sanctionedCircle.setFillColor(sf::Color(200, 200, 200)); // Gray
        }
        sanctionedCircles[i] = sanctionedCircle;
    
    }


    // Set up the legend box and its contents to explayin the colors
    sf::RectangleShape legendBox(sf::Vector2f(200, 120));
    legendBox.setFillColor(sf::Color(240, 240, 240));
    legendBox.setOutlineColor(sf::Color::Black);
    legendBox.setOutlineThickness(2);
    legendBox.setPosition(1350, 250 + players.size() * 80 - 180);

    sf::Text legendTitle("Legend", font, 20);
    legendTitle.setFillColor(sf::Color::Black);
    legendTitle.setPosition(1360, 250 + players.size() * 80 - 170);

    sf::CircleShape legendBlockToBribe(10);
    legendBlockToBribe.setFillColor(sf::Color(255, 165, 0)); // Orange
    legendBlockToBribe.setPosition(1360, 250 + players.size() * 80 - 140);

    sf::Text legendBlockToBribeText("Block to Bribe", font, 16);
    legendBlockToBribeText.setFillColor(sf::Color::Black);
    legendBlockToBribeText.setPosition(1380, 250 + players.size() * 80 - 140);

    sf::CircleShape legendPreventArrest(10);
    legendPreventArrest.setFillColor(sf::Color::Blue); // Blue
    legendPreventArrest.setPosition(1360, 250 + players.size() * 80 - 115);

    sf::Text legendPreventArrestText("Prevent Arrest", font, 16);
    legendPreventArrestText.setFillColor(sf::Color::Black);
    legendPreventArrestText.setPosition(1380, 250 + players.size() * 80 - 115);

    sf::CircleShape legendSanctioned(10);
    legendSanctioned.setFillColor(sf::Color::Magenta); // Magenta
    legendSanctioned.setPosition(1360, 250 + players.size() * 80 - 90);

    sf::Text legendSanctionedText("Sanctioned", font, 16);
    legendSanctionedText.setFillColor(sf::Color::Black);
    legendSanctionedText.setPosition(1380, 250 + players.size() * 80 - 90);

   
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                try{
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                // for each player check if the mouse is over the buttons
                for (size_t i = 0; i < players.size(); ++i) { 
                    // Check if the mouse is over the gather button
                    if (gatherButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Gather!\n";
                        players[i]->gather(); // Call the gather method
                        
                    }

                    // Check if the mouse is over the tax button
                    if (taxButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Tax!\n";
                        players[i]->tax(); // Call the tax method
                    }
                    // Check if the mouse is over the bribe button
                    if (bribeButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Bribe!\n";
                        players[i]->bribe();// Call the bribe method
                    }
                    // Check if the mouse is over the arrest button
                    if (arrestButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (players[i]->getName() != game.turn()) { // Check if it's the player's turn
                            throw std::runtime_error("This is not your turn");
                        }
                        Player* target = selectPlayerForAction(players, players[i]); // Select a target for the action
                        if (target != nullptr) {
                            std::cout << players[i]->getName() << " performed Arrest on " << target->getName() << "!\n";
                            players[i]->arrest(*target); // Call the arrest method on the selected target

                        }
                            
                        
                    }
                    // Check if the mouse is over the sanction button
                    if (sanctionButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                       
                        if (players[i]->getName() != game.turn()) { // Check if it's the player's turn
                            throw std::runtime_error("This is not your turn");
                          }
                        Player* target = selectPlayerForAction(players, players[i]);// Select a target for the action
                        if (target != nullptr) {
                            std::cout << players[i]->getName() << " performed Sanction on " << target->getName() << "!\n";
                            players[i]->sanction(*target); // Call the sanction method on the selected target
                            // update the status circles
                            updateStatusCircles(blockToBribeCircles, preventArrestCircles, sanctionedCircles, players);

                        }
                     
                    }
                    // Check if the mouse is over the coup button
                    if (coupButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        
                        if (players[i]->getName() != game.turn()) { // Check if it's the player's turn
                            throw std::runtime_error("This is not your turn");
                        }
                        Player* target = selectPlayerForAction(players, players[i]);// Select a target for the action
                        if (target != nullptr) {
                            std::cout << players[i]->getName() << " performed Coup on " << target->getName() << "!\n";
    
                            players[i]->coup(*target,true); // Call the coup method on the selected target
                            // update the status circles
                            updateStatusCircles(blockToBribeCircles, preventArrestCircles, sanctionedCircles, players);

                            int numAlive = 0;
                            for(int i=0;i<players.size();i++){ // check how many players are alive
                                if(players[i]->getIsAlived()){
                                    numAlive++;
                                }
                            }
                            if(numAlive==1){ // if only one player is alive
                                cout<<"Game Over"<<endl;
                                string str= game.winner(); // get the winner
                                endGame(str);
                                window.close();
                            }
                            // update the status circles
                            updateStatusCircles(blockToBribeCircles, preventArrestCircles, sanctionedCircles, players);

                        }
                        
                    }
                    // Check if the mouse is over the invest button (only for Baron)
                    if (players[i]->getRoll() == "Baron" && investButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Invest!\n";
                        players[i]->invest(); // Call the invest method
                    }
                    // Check if the mouse is over the show coins button (only for Spy)
                    if (players[i]->getRoll() == "Spy" && showCoinsButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        Player* target = selectPlayerForAction(players, players[i]);// Select a target for the action
                        if (target != nullptr) {
                            std::cout << players[i]->getName() << " performed Show coinds on " << target->getName() << "!\n";
                             displayCoins(target); // Show the coins of the selected target
                        }
                    }
                    // Check if the mouse is over the prev arrest button (only for Spy)
                    if (players[i]->getRoll() == "Spy" && prevArrestButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    
                         Player* target = selectPlayerForAction(players, players[i]);// Select a target for the action
                        if (target != nullptr) {
                            std::cout << players[i]->getName() << " performed PrevArrest on " << target->getName() << "!\n";
                            
                            target->setPreventToArrest(true); // Call the prev arrest method
                            // update the status circles
                            updateStatusCircles(blockToBribeCircles, preventArrestCircles, sanctionedCircles, players);

                        }
                    }
                    // Check if the mouse is over the undo button (only for Governor, General, Judge)
                    if (players[i]->getRoll() == "Governor" && undoButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                         Player* target = selectPlayerForAction(players, players[i]);// Select a target for the action
                        if (target != nullptr) {
                            std::cout << players[i]->getName() << " performed Undo on " << target->getName() << "!\n";
                            
                            players[i]->undo(*target);// Call the undo method on the selected target (dinamic call from the virtual table)
                        }
                    }
                    // Check if the mouse is over the undo button (only for Governor, General, Judge)
                    if (players[i]->getRoll() == "General" && undoButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                       
                        Player* target = selectPlayerForAction(players, players[i]);// Select a target for the action
                        if (target != nullptr) {
                            std::cout << players[i]->getName() << " performed Undo on " << target->getName() << "!\n";
                            
                            players[i]->undo(*target);// Call the undo method on the selected target (dinamic call from the virtual table)
                        }
                    }
                    // Check if the mouse is over the undo button (only for Governor, General, Judge)
                    if (players[i]->getRoll() == "Judge" && undoButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        
                        Player* target = selectPlayerForAction(players, players[i]);// Select a target for the action
                        if (target != nullptr) {
                            std::cout << players[i]->getName() << " performed Undo on " << target->getName() << "!\n";
                            
                            players[i]->undo(*target);// Call the undo method on the selected target (dinamic call from the virtual table)
                        }
                    }
                    // Check if the mouse is over the skip button
                    if (skipButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << players[i]->getName() << " performed Skip!\n";
                        players[i]->skipTurn();// Call the skip method
                    }
               
                }
                // Update the coin texts alive texts and status circles
                updateCoinTexts(coinTexts, players);
                updateAliveTexts(aliveTexts, players);
                playerTurnText.setString("Player Turn: " + game.turn());
                playerLastArrested.setString("Last Arrested: " + game.lastArrested());
                updateStatusCircles(blockToBribeCircles, preventArrestCircles, sanctionedCircles, players);
               
            }catch (const std::exception &e) { //catch any exception and display the error message
                displayError(e.what());
                 playerTurnText.setString("Player Turn: " + game.turn());
            }

            }
        }

    
        window.clear(sf::Color(240, 240, 240));
        // Draw the title and all the player texts, buttons, and status circles
        window.draw(title);
        for (size_t i = 0; i < players.size(); ++i) {
            window.draw(aliveTexts[i]);
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
            window.draw(coinTexts[i]);
            window.draw(skipButtons[i]);
            window.draw(skipTexts[i]);
            window.draw(blockToBribeCircles[i]);
            window.draw(preventArrestCircles[i]);
            window.draw(sanctionedCircles[i]);
            window.draw(legendBox);
            window.draw(legendTitle);
            window.draw(legendBlockToBribe);
            window.draw(legendBlockToBribeText);
            window.draw(legendPreventArrest);
            window.draw(legendPreventArrestText);
            window.draw(legendSanctioned);
            window.draw(legendSanctionedText);

            // Draw the buttons and texts for the Baron unique actions
            if (players[i]->getRoll() == "Baron") {
                window.draw(investButtons[i]);
                window.draw(investTexts[i]);
            }
            // Draw the buttons and texts for the Spy unique actions
            if (players[i]->getRoll() == "Spy") {
                window.draw(showCoinsButtons[i]);
                window.draw(showCoinsTexts[i]);
                window.draw(prevArrestButtons[i]);
                window.draw(prevArrestTexts[i]);
            }
            // Draw the buttons and texts for the Governor, General, Judge unique actions
            if (players[i]->getRoll() == "Governor" || players[i]->getRoll() == "General" || players[i]->getRoll() == "Judge") {
                window.draw(undoButtons[i]);
                window.draw(undoTexts[i]);
            }
        }
         window.draw(playerTurnText);
        window.draw(playerLastArrested);
        window.display();
    }
}


/**
 * @brief Displays an error message in a separate window.
 * @param errorMessage The error message to display.
 * @throws std::runtime_error if the font fails to load.
 * This function creates a new window to show the error message and an "OK" button to close the window.
 */
void displayError(const std::string& errorMessage) {
    sf::RenderWindow errorWindow(sf::VideoMode(500, 200), "Error");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font for error window\n";
        return;
    }

    sf::Text errorText(errorMessage, font, 20);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(250 - errorText.getGlobalBounds().width / 2, 80);

    sf::RectangleShape button(sf::Vector2f(100, 40));
    button.setFillColor(sf::Color(180, 180, 250));
    button.setPosition(150, 130);

    sf::Text buttonText("OK", font, 18);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(200 - buttonText.getGlobalBounds().width / 2, 140);

    while (errorWindow.isOpen()) {
        sf::Event event;
        while (errorWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                errorWindow.close();

            if (event.type == sf::Event::MouseButtonPressed) { 
                sf::Vector2i mousePos = sf::Mouse::getPosition(errorWindow);
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // Check if the button is clicked
                    errorWindow.close();
                }
            }
           
        }

        errorWindow.clear(sf::Color(240, 240, 240));
        errorWindow.draw(errorText);
        errorWindow.draw(button);
        errorWindow.draw(buttonText);
        errorWindow.display();
    }
}

/**
 * @brief Display the players that can be selected for an action.
 * @param players Vector of Player pointers.
 * @param currentPlayer Pointer to the current player.
 * @return Pointer to the selected player or nullptr if no player is selected.
 * @throws std::runtime_error if the font fails to load.
 * This function creates a new window to show the players that can be selected for an action.
 * It displays the players' names and rolls, and allows the user to select one of them.
 * The selected player is returned, or nullptr if no player is selected.
 */
Player* selectPlayerForAction(const std::vector<Player*>& players, Player* currentPlayer) {
    sf::RenderWindow selectionWindow(sf::VideoMode(600, 400), "Select a Player");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font for selection window\n";
        return nullptr;
    }
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    std::vector<Player*> selectablePlayers;
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] == currentPlayer || !players[i]->getIsAlived()) { // Skip the current player and dead players
            continue; 
        }
        sf::RectangleShape button(sf::Vector2f(400, 50));
        button.setFillColor(sf::Color(180, 180, 250));
        button.setPosition(100, 50 + buttons.size() * 70);

        sf::Text buttonText(players[i]->getName() + " - " + players[i]->getRoll(), font, 20);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setPosition(120, 60 + buttons.size() * 70);
        buttons.push_back(button);
        buttonTexts.push_back(buttonText);
        selectablePlayers.push_back(players[i]);
    }
    while (selectionWindow.isOpen()) {
        sf::Event event;
        while (selectionWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                selectionWindow.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(selectionWindow);
                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectionWindow.close();
                        return selectablePlayers[i]; // Return the selected player
                    }
                }
            }
        }
        selectionWindow.clear(sf::Color(240, 240, 240));
        for (size_t i = 0; i < buttons.size(); ++i) {
            selectionWindow.draw(buttons[i]);
            selectionWindow.draw(buttonTexts[i]);
        }
        selectionWindow.display();
    }
    return nullptr;
}

/**
 * @brief Updates the status circles for each player based on their status.
 * @param blockToBribeCircles Vector of CircleShape for Block to Bribe status.
 * @param preventArrestCircles Vector of CircleShape for Prevent Arrest status.
 * @param sanctionedCircles Vector of CircleShape for Sanctioned status.
 * @param players Vector of Player pointers.
 */
void updateStatusCircles(std::vector<sf::CircleShape>& blockToBribeCircles,std::vector<sf::CircleShape>& preventArrestCircles,std::vector<sf::CircleShape>& sanctionedCircles,const std::vector<Player*>& players) {
    for (size_t i = 0; i < players.size(); ++i) {
        // Update Block to Bribe Circle
        if (players[i]->isBlockToBribe()) {
            blockToBribeCircles[i].setFillColor(sf::Color(255, 165, 0)); // Orange
        } else {
            blockToBribeCircles[i].setFillColor(sf::Color(200, 200, 200)); // Gray
        }

        // Update Prevent Arrest Circle
        if (players[i]->getPreventToArrest()) {
            preventArrestCircles[i].setFillColor(sf::Color::Blue); // Blue
        } else {
            preventArrestCircles[i].setFillColor(sf::Color(200, 200, 200)); // Gray
        }

        // Update Sanctioned Circle
        if (players[i]->getIsBlocked()) {
            sanctionedCircles[i].setFillColor(sf::Color::Magenta); // Magenta
        } else {
            sanctionedCircles[i].setFillColor(sf::Color(200, 200, 200)); // Gray
        }
    }
}

/**
 * @brief Gives the Genral the option to save himself.
 * @return true if the player wants to save himself, false otherwise.
 * @throws std::runtime_error if the font fails to load.
 * This function creates a new window to ask the player if they want to save themselves.
 * It displays a message and two buttons: "Yes" and "No".
 * The player can click on one of the buttons to make their choice.
 */
bool checkSavingGeneral(){
    sf::RenderWindow window(sf::VideoMode(400, 200), "Saving General");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return false;
    }

    sf::Text text("Do you want to save the General?", font, 24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(50, 50);

    sf::RectangleShape yesButton(sf::Vector2f(100, 40));
    yesButton.setFillColor(sf::Color(70, 130, 180));
    yesButton.setPosition(50, 120);

    sf::Text yesText("Yes", font, 22);
    yesText.setFillColor(sf::Color::White);
    yesText.setPosition(75, 127);

    sf::RectangleShape noButton(sf::Vector2f(100, 40));
    noButton.setFillColor(sf::Color(70, 130, 180));
    noButton.setPosition(250, 120);

    sf::Text noText("No", font, 22);
    noText.setFillColor(sf::Color::White);
    noText.setPosition(275, 127);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (yesButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                    return true; // Player wants to save themselves
                }
                if (noButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                    return false; // Player does not want to save themselves
                }
            }
        }

        window.clear(sf::Color(250, 250, 250));
        window.draw(text);
        window.draw(yesButton);
        window.draw(yesText);
        window.draw(noButton);
        window.draw(noText);
        window.display();
    }
    return false; // Default return value if window is closed without selection
}

/**
 * @brief Displays a "Game Over" window showing the winner's name.
 * @param str The name of the winner.
 * @throws std::runtime_error if the font fails to load.
 * This function creates a new window to show the game over message and the winner's name.
 * It displays a message and an "OK" button to close the window.
 */
void endGame(std::string str){
    sf::RenderWindow window(sf::VideoMode(400, 200), "Game Over");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    sf::Text text("The Winner is : " + str, font, 24); //Update the text to show the winner
    text.setFillColor(sf::Color::Green);
    text.setPosition(70, 50);

    sf::RectangleShape okButton(sf::Vector2f(100, 40));
    okButton.setFillColor(sf::Color(180, 180, 250));
    okButton.setPosition(150, 120);

    sf::Text okText("OK", font, 20);
    okText.setFillColor(sf::Color::White);
    okText.setPosition(175, 125);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) { //Show the window and check for events
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) { // Check if the mouse is clicked
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (okButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                }
            }
        }

        window.clear(sf::Color(250, 250, 250));
        window.draw(text);
        window.draw(okButton);
        window.draw(okText);
        window.display();
    }
}

