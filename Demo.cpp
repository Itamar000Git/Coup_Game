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
    
    //(1) Expected output:
    // Moshe
    // Yossi
    // Meirav
    // Reut
    // Gilad
    cout<<"(1)"<<endl;
    for(string name : players){
        cout << name << endl;
    }
    cout<<endl;
    

    //(2) Expected output: Moshe
    cout<<"(2)"<<endl;
    cout << game_1.turn() << endl;

    cout<<endl;

    governor.gather();
    spy.gather();
    baron.gather();
    general.gather();
    judge.gather();

    cout<<endl;

    //(3) Expected exception - Not spy's turn
    cout<<"(3)"<<endl;
    try{
        spy.gather();
    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    cout<<endl;

    governor.gather();
    spy.tax();

    cout<<endl;

    //(4) Expected exception - Judge cannot undo tax 
    cout<<"(4)"<<endl;
    try{
        judge.undo(governor);

    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;

    cout<<"(5)"<<endl;
    cout << governor.coins() << endl; //(5) Expected: 2
    cout << spy.coins() << endl; //(5) Expected: 3

    cout << game_1 << endl; 

    governor.undo(spy); // Governor undo tax 

    cout<<"(6)"<<endl;
     cout << spy.coins() << endl; //(6) Expected: 1

    cout << endl;
    baron.tax();
    general.gather();
    judge.gather(); 

    governor.tax();
    spy.gather();
    baron.invest(); // Baron traded its 3 coins and got 6 
    general.gather();
    judge.gather();
    
    cout << endl;
    cout <<"(7)"<< endl;

    cout << baron.coins() << endl; //(7) Expected: 6

    cout << endl;
    governor.tax();
    spy.gather();
    baron.gather();
    general.gather();
    judge.gather();

    governor.tax();
    spy.gather();

    cout << endl;
    cout << "(8)" << endl;
    cout << baron.coins() << endl; //(8) Expected: 7

    cout << endl;
    baron.coup(governor); // Coup against governor 
    
    general.gather();
    judge.gather();
    
    players = game_1.players();
    //(9) Since no one blocked the Baron, the expected output is:
    // Yossi
    // Meirav
    // Reut
    // Gilad
    cout<<endl;
    cout << "(9)" << endl;

    for (string name : players) {
        cout << name << endl;
    }
    cout<<endl;
    cout<<"///////////Extra Demo///////////"<<endl;
    cout<<game_1<<endl;

    cout<<"///////Arresting judge"<<endl;
    spy.arrest(judge); // Spy arrest judge 
    cout<<endl;
    cout<<"(10)"<<endl;
    cout<<game_1<<endl; //(10) Expected 5 coins for spy and 4 coins for judge

    cout<<"/////////Trying to arrest the same player"<<endl; //(11)
    cout<<"(11)"<<endl;
    try{
        baron.arrest(judge); // Baron arrest judge
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }


    cout<<endl;

    baron.gather();
    cout<<endl;



    cout<<"/////////Spy prvent from general to arrest a player"<<endl; //(12)
    cout<<"(12)"<<endl;
    spy.prventArrest(general); // Spy prvent from general to arrest a player

    try{
        general.arrest(baron); // General arrest baron 
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    cout<<game_1<<endl;


    cout<<"/////Show bribe"<<endl; 
    general.bribe(); // General bribe
    cout<<endl;

    cout<<"/////Trying to bribe with less then 4 coins "<<endl;//(13)
    cout<<"(13)"<<endl;
    try{
        general.bribe(); // General bribe
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;

    general.tax(); // General tax
    cout<<endl;
    cout<<"(14)"<<endl;
    cout<<general.coins()<<endl; //(14) Expected: 3
    cout<<game_1.turn()<<endl; //(14) Expected: Gilad (Judge)
    cout<<endl;
    general.gather(); // General gather
    judge.tax(); // Judge tax
  
    cout<<"try to prevent the spy from briding"<<endl; //(15)
    cout<<"(15)"<<endl;
    cout<<game_1<<endl;
    spy.bribe(); // Spy bribe
    cout<<endl;

    cout<<"/////After bribe"<<endl;
    cout<<game_1<<endl;
    cout<<"/////Trting to preform second move"<<endl;
    judge.judgPreventBribe(spy); // Judge prevent spy from briding
    try{
        spy.gather(); 
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;

    cout<<"/////After one round yossi can gather again"<<endl;
   
    baron.gather(); // Baron gather
    general.gather();
    judge.gather();

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
    cout<<"/////Trying to gather when judge have to coup"<<endl; //(16)
    cout<<"(16)"<<endl;
    try{
        judge.gather(); // Judge gather
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    cout<<"/////Trying to coup dead player"<<endl;//(17)
    cout<<"(17)"<<endl;
    try{
        judge.coup(governor); // Judge coup governor
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    judge.coup(baron); // Judge coup spy
    cout<<endl;
    cout<<game_1<<endl;
    cout<<endl;

    cout<<"(18)"<<endl;
    cout<<spy.watchNumOfCoins(general)<<endl; // Spy get coins from baron (18)
    cout<<"/////Trying to see a dead player coins"<<endl;
    try{
        spy.watchNumOfCoins(governor); // Spy get coins from baron
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }



    spy.tax(); // Spy tax
    cout<<"(19)"<<endl;
    cout<<"/////Trying to play with dead player"<<endl; //(19)
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

    cout<<"Coup a general"<<endl;//(20)
    cout<<"(20)"<<endl;
  
    cout<<game_1<<endl;
    cout<<endl; 
    cout<<"/////////////////please press n at the folowing question///////////////"<<endl;
    judge.coup(general); // Judge coup general

    cout<<endl; 
    cout<<game_1<<endl;
    cout<<endl; 

    cout<<"(21)"<<endl;

    cout<<game_1.winner()<<endl; //(21) Expected: Gilad (Judge)


}
