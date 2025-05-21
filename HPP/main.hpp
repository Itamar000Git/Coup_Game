//itamarbabai98@gmail.com

#ifndef MAIN_HPP
#define MAIN_HPP
#include <vector>
#include <string>
#include "Player.hpp"
#include "Game.hpp"
using namespace std;
using namespace coup;
namespace coup {
    class Player;
    
}
void mainwin(int& numPlayers, vector<string>& players);
void signIn(int& numPlayers, vector<string>& players);
void get_members(int& numPlayers, vector<string>& players);
void displayCoupBoard(const vector<Player*>& players, Game &game);
void displayError(const std::string& errorMessage);
Player* selectPlayerForAction(const std::vector<Player*>& players, Player* currentPlayer);
void updateAliveTexts(const std::vector<Player*>& aliveTexts,const vector<Player*>& players);
void updateStatusCircles(std::vector<sf::CircleShape>& blockToBribeCircles,
                         std::vector<sf::CircleShape>& preventArrestCircles,
                         std::vector<sf::CircleShape>& sanctionedCircles,
                         const std::vector<Player*>& players);
void displayCoins(const Player* player);
bool checkSavingGeneral();
enum class GameRolls { 
    Baron, General, Governor, Judge, Merchant, Spy 
};
coup::Player* drawCard(std::string name, Game &game);
 void updateCoinTexts(std::vector<sf::Text>& coinTexts, const vector<Player*>& players);
void endGame(std::string str);

#endif // MAIN_HPP