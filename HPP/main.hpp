#ifndef MAIN_HPP
#define MAIN_HPP
#include <vector>
#include <string>
using namespace std;
//using namespace coup;
void mainwin(int& numPlayers, vector<string>& players);
void signIn(int& numPlayers, vector<string>& players);
void get_members(int& numPlayers, vector<string>& players);
enum class GameRolls { 
    Baron, General, Governor, Judge, Merchant, Spy 
};
GameRolls drawCard(){
    int randomNum = rand() % 6; // Random number between 0 and 5
    switch (randomNum) {
        case 0: return GameRolls::Baron;
        case 1: return GameRolls::General;
        case 2: return GameRolls::Governor;
        case 3: return GameRolls::Judge;
        case 4: return GameRolls::Merchant;
        case 5: return GameRolls::Spy;
    }
    return GameRolls::Baron; // Default case, should not happen
}


#endif