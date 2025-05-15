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
enum class GameRolls { 
    Baron, General, Governor, Judge, Merchant, Spy 
};
coup::Player* drawCard(std::string name, Game &game);


#endif