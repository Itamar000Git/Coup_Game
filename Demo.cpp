//itamarbabai98@gmail.com

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
using namespace std;
using namespace coup;

int main() {
    Game game_1{};
    
    Governor governor(game_1, "Moshe");

    Spy spy(game_1, "Yossi");
    Baron baron(game_1, "Meirav");
    General general(game_1, "Reut");
    Judge judge(game_1, "Gilad");

    vector<string> players = game_1.players();
    
    // Expected output:
    // Moshe
    // Yossi
    // Meirav
    // Reut
    // Gilad
    for(string name : players){
        cout << name << endl;
    }

    // Expected output: Moshe
    cout << game_1.turn() << endl;

    governor.gather();
    spy.gather();
    baron.gather();
    general.gather();
    judge.gather();

    
    // Expected exception - Not spy's turn
    try{
        spy.gather();
    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    governor.gather();
    spy.tax();

    // Expected exception - Judge cannot undo tax 
    try{
        judge.undo(governor);

    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    cout << governor.coins() << endl; // Expected: 2
    cout << spy.coins() << endl; // Expected: 3

     governor.undo(spy); // Governor undo tax 
     cout << spy.coins() << endl; // Expected: 1

    baron.tax();
    general.gather();
    judge.gather(); 

    governor.tax();
    spy.gather();
    baron.invest(); // Baron traded its 3 coins and got 6 
    general.gather();
    judge.gather();
    
    cout << baron.coins() << endl; // Expected: 6

    governor.tax();
    spy.gather();
    baron.gather();
    general.gather();
    judge.gather();

    governor.tax();
    spy.gather();
    cout << baron.coins() << endl; // Expected: 7
    baron.coup(governor); // Coup against governor 
    
    general.gather();
    judge.gather();
    
    players = game_1.players();
    // Since no one blocked the Baron, the expected output is:
    // Yossi
    // Meirav
    // Reut
    // Gilad
    for (string name : players) {
        cout << name << endl;
    }

    cout<<"///////////Extra Demo///////////"<<endl;
    cout<<game_1<<endl;

    cout<<"///////Arresting judge"<<endl;
    spy.arrest(judge); // Spy arrest judge
    //cout<<"name: "<<judge.getName()<<", roll: "<<judge.getRoll()<<", num of coins: "<<judge.coins()<<endl; // Expected: 4
    //cout<<"name: "<<spy.getName()<<", roll: "<<spy.getRoll()<<", num of coins: "<<spy.coins()<<endl; // Expected: 5
    cout<<endl;
    cout<<game_1<<endl;

    cout<<"/////////Trying to arrest the same player"<<endl;
    try{
        baron.arrest(judge); // Baron arrest judge
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }


    //cout<<game_1.turn()<<endl; // Expected: Meirav (Baron)
    cout<<endl;

    baron.gather(); // Baron arrest spy
    cout<<endl;



    cout<<"/////////Spy prvent from general to arrest a player"<<endl;
    spy.prventArrest(general); // Spy prvent from general to arrest a player

    try{
        general.arrest(baron); // General arrest baron 
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    cout<<game_1<<endl;


    cout<<"/////Show bride"<<endl; 
    general.bride(); // General bride
    cout<<endl;

    cout<<"/////Trying to bride with less then 4 coins "<<endl;
    try{
        general.bride(); // General bride
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;

    general.tax(); // General tax
    cout<<general.coins()<<endl; // Expected: 3
    cout<<game_1.turn()<<endl; // Expected: Gilad (Judge)

    judge.tax(); // Judge tax
  
    cout<<"try to prevent the spy from briding"<<endl;
    cout<<game_1<<endl;
   // cout<<game_1.turn()<<endl; // Expected: Yossi (spy)
    //cout<<spy.coins()<<endl; // Expected: 4
    spy.bride(); // Spy bride
    cout<<endl;

    cout<<"/////After bride"<<endl;
    cout<<game_1<<endl;
    //cout<<spy.coins()<<endl; // Expected: 0
    //cout<<game_1.turn()<<endl; // Expected: Yossi (spy)
    cout<<"/////Trting to preform second move"<<endl;
    judge.judgPreventBride(spy); // Judge prevent spy from briding
    try{
        spy.gather(); 
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;

    cout<<"/////After one round yossi can gather again"<<endl;
   // cout<<spy.coins()<<endl; // Expected: 0
    //cout<<game_1.turn()<<endl; // Expected: Meirav (Baron)
    baron.gather(); // Baron gather
    general.gather();
    judge.gather();

    //cout<<game_1.turn()<<endl; // Expected: yossi (spy)
    spy.gather(); 


    cout<<endl;
    cout<<"/////Trying reach a coup with judge"<<endl;
    baron.tax(); // Baron invest
    general.tax(); // General tax
    judge.tax(); // Judge gather
    spy.tax(); // Spy tax

    baron.invest(); // Baron invest
    general.tax(); // General tax
    judge.tax(); // Judge gather
    spy.tax(); // Spy tax

    cout<<game_1<<endl;
    baron.invest(); // Baron invest
    general.tax(); // General tax
    cout<<"/////Trying to gather when judge have to coup"<<endl;
    try{
        judge.gather(); // Judge gather
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    cout<<"/////Trying to coup dead player"<<endl;
    try{
        judge.coup(governor); // Judge coup spy
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    judge.coup(baron); // Judge coup spy
    cout<<endl;
    cout<<game_1<<endl;

    spy.tax(); // Spy tax

    cout<<"/////Trying to play with dead player"<<endl;
    try{
        baron.gather(); 
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    general.coup(spy); // General coup spy
    judge.tax(); // Judge tax
    general.tax(); // General gather
    judge.tax(); // Judge tax
    general.tax(); // General gather
    judge.tax(); // Judge tax
    general.tax(); // General gather
    cout<<endl;

    cout<<game_1<<endl;
    judge.coup(general); // Judge coup general

    cout<<endl; 
    cout<<game_1<<endl;

}
