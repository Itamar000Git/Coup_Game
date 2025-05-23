//itamarbabai98@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include "HPP/Game.hpp"
#include "HPP/Player.hpp"
#include "HPP/Governor.hpp"
#include "HPP/Spy.hpp"
#include "HPP/Baron.hpp"
#include "HPP/General.hpp"
#include "HPP/Judge.hpp"
#include "HPP/Merchant.hpp"

using namespace coup;
TEST_CASE("Game Initialization") {

    Game game{};

    CHECK(game.players().size() == 0); // No players yet
    CHECK_THROWS_AS(game.turn(), std::runtime_error); // Game not started

    Governor gov(game, "gov_1");

    CHECK_THROWS_AS(gov.gather(), std::runtime_error); // Game not started

    Spy spy(game, "spy_1");
    Baron baron(game, "baron_1");
    //Trying to create a player with already exists name.
    CHECK_THROWS_AS(Baron(game, "baron_1"), std::runtime_error); 

    General gen(game, "general_1");
    Judge judge(game, "judge_1");
    Merchant merchant(game, "mer_1");

    CHECK(game.getNumOfPlayers() == 6); // 6 players in the game

    //Trying to check the winner before the game is over
    CHECK_THROWS_AS(game.winner(), std::runtime_error); // Game not over

    //Trying to create a 7th player
    CHECK_THROWS_AS(General(game, "general_2"), std::runtime_error); // More than 6 players

    std::vector<std::string> players = game.players();

    CHECK(players.back() == "mer_1"); // Last player added
    CHECK(gov.getIsAlived() == true); // Gov is alive
    CHECK(game.turn()=="gov_1"); // Gov's turn

    game.removePlayer(&gov); // Gov is removed from the game

    CHECK(game.getNumOfPlayers() == 5); // 5 players left
    
    //The folowing case check if the turns are working correctly
    SUBCASE("Game Turn") { 
        game.nextTurn();
        CHECK(game.turn() == "spy_1");
        game.nextTurn();
        CHECK(game.turn() == "baron_1");
        game.nextTurn();
        CHECK(game.turn() == "general_1");
        game.nextTurn();
        CHECK(game.turn() == "judge_1");
        game.nextTurn();
        CHECK(game.turn() == "mer_1");
        game.nextTurn();
    }

}

TEST_CASE("Player Actions") {
    Game game{};

    Governor gov(game, "gov_1");
    Spy spy(game, "spy_1");
    Baron baron(game, "baron_1");
    General gen(game, "general_1");
    Judge judge(game, "judge_1");
    Merchant merchant(game, "mer_1");

    
    /**
     * Checking if it possible to make a move not in the turn.
     * And if it is possible to make a move that cost more coins than the player has.
     */
    SUBCASE("Invalid Player Actions") {
        CHECK_THROWS_AS(spy.gather(), std::runtime_error); // Not gov's turn
        CHECK_THROWS_AS(gov.coup(spy), std::runtime_error); // Don't have enough coins
       
    }
    /**
     * Trying to gather after sanction.
     * Trying to tax after sanction.
     */
    SUBCASE("Try gather or tax after sanction"){
        for(int i = 0; i < 4; ++i) {
            gov.gather();
            spy.gather();
            baron.tax();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        
            
        CHECK(game.turn()=="gov_1"); // Gov's turn
        CHECK(gov.coins() == 4); // Gov has 4 coins
        gov.sanction(spy);
        
        CHECK_THROWS_AS(spy.gather(), std::runtime_error); // Blocked by sanction
        CHECK_THROWS_AS(spy.tax(), std::runtime_error); // Blocked by sanction
 
     }

    /**
     * Trying to make a move with more than 10 coins.
     * Trying to arrest a dead player.
     */
    SUBCASE("Try to make a move with more than 10 coins") {
        for(int i = 0; i <= 4; ++i) {
            gov.gather();
            spy.tax();
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        gov.skipTurn();
        
        CHECK(spy.coins() == 10); // Spy has 10 coins
        CHECK_THROWS_AS(spy.gather(), std::runtime_error); // Have to coup

        spy.coup(judge);
        CHECK(judge.getIsAlived() == false); // Judge is dead

        CHECK_THROWS_AS(baron.arrest(judge), std::runtime_error); // Arrest a dead player
  
    }

    /**
     * Watch the coins of another player.
     * Trying to arrest a player with block to arrest.
     * Trying to arrest the same player twice.
     */
    SUBCASE("Test spy ability") {
        for(int i = 0; i <= 3; ++i) {
            gov.gather();
            spy.tax();
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        CHECK(gov.coins() == 4); // Gov has 4 coins
        CHECK(spy.watchNumOfCoins(gov) == 4); // Spy can see gov's coins
        spy.prventArrest(gov);
        CHECK_THROWS_AS(gov.arrest(gen), std::runtime_error); // gov blocked and can't arrest 

        gov.gather();
        spy.tax();

        CHECK(baron.coins() == 4);
        CHECK(judge.coins() == 4);

        baron.arrest(judge); // Baron can arrest judge

        CHECK(baron.coins() == 5); // Baron should have 5 coins after arrest
        CHECK(judge.coins() == 3); // Judge should have 3 coins after arrest   

        CHECK_THROWS_AS(gen.arrest(judge), std::runtime_error); // gov can't arrest the same player twice

    }

    /**
     * Trting to invest with baron without enough coins.
     * Checking if the invest method works correctly.
     * Checking if the tax method works correctly for baron
     */
    SUBCASE("Test baron ability"){
        for(int i = 0; i <= 2; ++i) {
            gov.gather();
            spy.gather();
            if(i==1){
                CHECK_THROWS_AS(baron.invest(), std::runtime_error); // Baron can't invest without enough coins
                baron.gather();
            }else{
                baron.gather();
            }
           
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        gov.gather();
        spy.gather();

         //After investing, baron should have 6 coins
        CHECK(baron.coins() == 3);
         baron.invest();
        CHECK(baron.coins() == 6);

        gen.sanction(baron);

        judge.gather();
        merchant.gather();
        gov.gather();
        spy.gather();

        CHECK(baron.coins() == 6);
        baron.tax();
        CHECK(baron.coins() == 7);// Baron should have 7 coins after tax when sanctioned
    }

    /**
     * Checking if the tax method works correctly for governor
     * Checking if the undo method works correctly for governor
     * Checking if the undo method works correctly when there is not enough coins
     * Checking if the undo method works correctly when the last move is not tax
     */
    SUBCASE("Test Governor ability"){
        CHECK(gov.coins() == 0);
        gov.tax();
        CHECK(gov.coins() == 3); //gov should have 3 coins after tax
        spy.tax();
        CHECK(spy.coins() == 2);

        gov.undo(spy);
        CHECK(spy.coins() == 0); //Spy should have 0 coins after undo

       

        baron.tax();
        gen.gather();
        judge.tax();
        merchant.arrest(judge);
        CHECK(judge.coins() == 1); //judg should have 1 coins after arrest
        CHECK_THROWS_AS(gov.undo(judge), std::runtime_error);// gov cant undo when judge dont have enough coins

        gov.gather();
        spy.gather();
        CHECK_THROWS_AS(gov.undo(spy), std::runtime_error);// gov cant undo when the last move is not tax

    }

    /**
     * Checking if in any turn merchant get free coin if he has more than 3 coins
     * Checking if merchant pay 2 coins after arrest
     */
    SUBCASE("Test Mearchant ability"){
        for(int i = 0; i <= 3; ++i) {
            gov.gather();
            spy.gather();   
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        CHECK(gov.coins() == 4);
        CHECK(spy.coins() == 4);
        CHECK(baron.coins() == 4);
        CHECK(gen.coins() == 4);
        CHECK(judge.coins() == 4);
        CHECK(merchant.coins() == 5);// Merchant should have 5 coins after gathering

        gov.arrest(merchant);
        CHECK(merchant.coins() == 3); //Merchant should have 3 coins after arrest
        CHECK(gov.coins() == 4);
    }

    /**
     * Checking if sanction a judge cost 4 coins
     * Checking if the undo method works correctly for judge
     * Checking if the bribe method blocked after undo
     */
    SUBCASE("Test Judge ability"){
        for(int i = 0; i <= 3; ++i) {
            gov.gather();
            spy.gather();   
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        gov.sanction(spy);
        CHECK(gov.coins() == 1); //Sanction  cost 3 coins for gov
        spy.sanction(judge);
        CHECK(spy.coins() == 0); // Sanction on Judg  cost 4 coins

        baron.bribe();
        baron.tax();
        baron.tax();
        CHECK(baron.coins() == 4); //Baron should have 4 coins after tax

        gen.bribe(); // gen bribe

        judge.undo(gen); //judge undo gen bribe

        CHECK_THROWS_AS(gen.tax(), std::runtime_error); // Gen can't tax after undo
        CHECK(gen.coins() == 0); //Gen should have 0 coins after undo

        CHECK(game.turn() == "judge_1"); // the turn move to the next player
    }

    /**
     * Checking if the arrest method not effective on general
     * Checking if the undo coup method works correctly for general
     */
    SUBCASE("Test General ability"){
        for(int i = 0; i <= 3; ++i) {
            gov.gather();
            spy.gather();   
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }

        CHECK(gov.coins() == 4);
        CHECK(gen.coins() == 4);

        gov.arrest(gen);
        CHECK(gen.coins() == 4); //General should have 4 coins after arrest
        CHECK(gov.coins() == 4); //Gov should have 4 coins after arrest

        spy.gather(); 
        baron.invest();
        gen.tax();
        judge.tax();
        merchant.tax();

        gov.gather();
        spy.gather(); 

        baron.coup(spy);
        CHECK(spy.getIsAlived() == false); //Spy should be dead
        CHECK(game.getNumOfPlayers() == 5); //Num of players should be 5
        gen.undo(baron);
    
        CHECK(spy.getIsAlived() == true);
        CHECK(game.getNumOfPlayers() == 6);
    }
}
/**
 * Trying to example all the edge cases
 */
TEST_CASE("Egde Cases"){
    Game game{};
    
    Governor gov(game, "gov_1");
    Spy spy(game, "spy_1");
    Baron baron(game, "baron_1");
    General gen(game, "general_1");
    Judge judge(game, "judge_1");
    Merchant merchant(game, "mer_1");

    /**
     * After arresting merchant (to make sure he has less than 3 coins), sanction him, prevent him to arrest,
     * Trying to do any action with merchant.
     * The only action that merchant can do is skip turn.
     */
    SUBCASE("Test soft lock - Block , less then 3 coins and prevent to arrest") {
        for(int i = 0; i <= 2; ++i) {
            gov.gather();
            spy.gather();   
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        
        CHECK(merchant.coins() == 3); 
        gov.arrest(merchant); //Merchant should have 1 coins after arrest
        CHECK(merchant.coins() == 1); //Merchant pay 2 coins after arrest

        std::cout<<spy.coins()<<std::endl;

        spy.sanction(merchant); //sanction merchant
        spy.prventArrest(merchant); //prevent merchant to arrest

        baron.gather();
        gen.gather();
        judge.gather();
        //Trying to do any action with merchant
        CHECK_THROWS_AS(merchant.gather(), std::runtime_error); 
        CHECK_THROWS_AS(merchant.tax(), std::runtime_error); 
        CHECK_THROWS_AS(merchant.arrest(spy), std::runtime_error); 
        CHECK_THROWS_AS(merchant.bribe(), std::runtime_error); 
        CHECK_THROWS_AS(merchant.sanction(spy), std::runtime_error); 
        CHECK_THROWS_AS(merchant.coup(spy), std::runtime_error); 

        merchant.skipTurn(); //the only action that merchant can do is skip turn

        CHECK(game.turn() == "gov_1"); 
    }

    /**
     * Checking if its possible to bribe multiple times
     */
    SUBCASE("Test multipul Bribe") {
        for(int i = 0; i <= 2; ++i) {
            gov.tax();
            spy.gather();   
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        gov.bribe();
        CHECK(gov.coins() == 5); //Gov should have 5 coins after bribe 9-4
        CHECK(game.turn() == "gov_1");
        gov.tax();

        gov.bribe();//Gov bribe again
        gov.tax();
        gov.bribe();
        gov.tax();
        gov.bribe();
        gov.tax();
        gov.bribe();
        gov.tax();
        gov.bribe();
        gov.tax();

        CHECK_THROWS_AS(gov.bribe(), std::runtime_error); //Gov can't bribe again
    }

    /**
     * Trying to play with a dead player
     */
    SUBCASE("Test game next turn over dead player") {
        for(int i = 0; i <= 3; ++i) {
            gov.tax();
            spy.tax();   
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        
        CHECK(gov.coins() == 12); // Gov should have 12 coins and have to coup
        gov.coup(judge);
        spy.tax();
        baron.gather();
        gen.gather();
       
        merchant.gather();

        gov.gather();
        spy.coup(merchant);
        baron.gather();
        gen.gather();
        CHECK_THROWS_AS(judge.gather(), std::runtime_error); //judge is dead
        CHECK_THROWS_AS(merchant.gather(), std::runtime_error); //Merchant is dead
        CHECK(game.turn() == "gov_1");
        gov.gather();

        CHECK(game.getNumOfPlayers() == 4); //Num of players should be 4
    
     }

    /**
    * Trying all action over dead player
    */
    SUBCASE("Test Actions over dead player"){
        for(int i = 0; i <= 3; ++i) {
            gov.tax();
            spy.tax();   
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }

        gov.coup(merchant);
        CHECK_THROWS_AS(gov.undo(merchant), std::runtime_error); //Spy can't gather over dead player
        CHECK_THROWS_AS(spy.prventArrest(merchant), std::runtime_error); //Spy can't gather over dead player
        CHECK_THROWS_AS(spy.watchNumOfCoins(merchant), std::runtime_error); //Spy can't watch coins over dead player
        CHECK_THROWS_AS(spy.arrest(merchant), std::runtime_error); //Spy can't arrest over dead player
        CHECK_THROWS_AS(spy.sanction(merchant), std::runtime_error); //Spy can't sanction over dead player
        CHECK_THROWS_AS(judge.undo(merchant), std::runtime_error); 

        spy.tax();
        baron.gather();
        gen.gather();
        judge.gather();
        gov.gather();
        CHECK_THROWS_AS(spy.coup(merchant), std::runtime_error); //Merchant is dead
        
     }

     /**
      * Trying all action not in turn
      */
    SUBCASE("Test Actions not in turn") {
        for(int i = 0; i <= 3; ++i) {
            gov.tax();
            spy.tax();   
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        gov.coup(judge);
        spy.tax();
        CHECK(game.turn() == "baron_1");
        CHECK_THROWS_AS(spy.coup(merchant), std::runtime_error); //Spy can't coup not in turn
        CHECK_THROWS_AS(spy.bribe(), std::runtime_error); //Spy can't bribe not in turn
        CHECK_THROWS_AS(spy.sanction(merchant), std::runtime_error); //Spy can't sanction not in turn
        CHECK_THROWS_AS(spy.arrest(merchant), std::runtime_error); //Spy can't arrest not in turn
        CHECK_THROWS_AS(spy.tax(), std::runtime_error); //Spy can't tax not in turn
        CHECK_THROWS_AS(spy.gather(), std::runtime_error); //Spy can't gather not in turn

     }

     /**
      * Trying to undo a move that not allowed to undo with this player
      */
     SUBCASE("Test Undo on wrong actions"){
        for(int i = 0; i <= 3; ++i) {
            gov.gather();
            spy.tax();   
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }

        CHECK_THROWS_AS(gov.undo(baron), std::runtime_error); //Gov cant undo gather
        CHECK_THROWS_AS(judge.undo(baron), std::runtime_error); //Judge cant undo gather
        CHECK_THROWS_AS(gen.undo(baron), std::runtime_error); //Gen cant undo gather


     }
     /**
      * Trying to coup a General and see if he can pay 5 coins to stay alive.
      * Coup the general with less than 5 coins again and see if he die.
      */
    SUBCASE("Test self save with genral"){ //maybe leave it for the end
        for(int i = 0; i <= 4; ++i) {
            gov.gather();
            spy.tax();   
            baron.gather();
            gen.gather();
            judge.tax();
            merchant.gather();
        }
        gov.gather();

        CHECK(gen.coins() == 5); //Gen should have 5 coins
        std::cout<<"###################please press yes in the gui##################"<<std::endl;
        spy.coup(gen,true); //need to press yes in the gui

        
        CHECK(gen.getIsAlived() == true); 

        baron.gather();
        gen.gather();

        CHECK(gen.coins() == 1); //Gen should have 0 coins
        judge.coup(gen,true); //not ask anything in the gui because gen dont have enough coins
        CHECK(gen.getIsAlived() == false); //Gen should be dead
        
     }
     /**
      * Trying to do any action on the same player that activate the action
      */
     SUBCASE("Test self actions"){
        for(int i = 0; i <= 4; ++i) {
            gov.gather();
            spy.tax();   
            baron.gather();
            gen.gather();
            judge.tax();
            merchant.gather();
        }
        gov.bribe();
        gov.tax();
        CHECK_THROWS_AS(gov.undo(gov), std::runtime_error); //Gov can't undo himself
        gov.gather();
        CHECK_THROWS_AS(spy.coup(spy), std::runtime_error); //Spy can't coup himself
        spy.coup(gov);


        CHECK_THROWS_AS( baron.sanction(baron), std::runtime_error); // Baron can't sanction himself
        CHECK_THROWS_AS( baron.arrest(baron), std::runtime_error); // Baron can't arrest himself
       
     }

     /**
      * Trying to do any action with no coins
      */
      SUBCASE("Test action with no coins"){
        CHECK_THROWS_AS(gov.sanction(spy), std::runtime_error); //Gov can't sanction with no coins
        CHECK_THROWS_AS(gov.arrest(spy), std::runtime_error); //Gov can't arrest with no coins
        CHECK_THROWS_AS(gov.coup(spy), std::runtime_error); //Gov can't coup with no coins
        
      }

    /**
     * Trying to undo a dead player actions
     */
    SUBCASE("Test undo to dead player action"){
        for(int i = 0; i <= 4; ++i) {
            gov.gather();
            spy.tax();   
            baron.gather();
            gen.gather();
            judge.tax();
            merchant.gather();
        }
        gov.gather();
        spy.coup(judge);
        CHECK_THROWS_AS(spy.prventArrest(judge), std::runtime_error); //Spy can't gather over dead player
        CHECK_THROWS_AS(spy.watchNumOfCoins(judge), std::runtime_error); //Spy can't watch coins over dead player
        CHECK_THROWS_AS(gov.undo(judge), std::runtime_error);//Gov can't undo dead player actions
        
    
    }
    /**
     * Trying to undo tax more than one turn back
     */
     SUBCASE("Test multipul undo for more then last turn"){
        for(int i = 0; i <= 4; ++i) {
            gov.gather();
            spy.tax();   
            baron.gather();
            gen.gather();
            judge.tax();
            merchant.gather();
        }
        CHECK(spy.coins() == 10);
        gov.undo(spy);
        CHECK(spy.coins() == 8);
        CHECK_THROWS_AS(gov.undo(spy), std::runtime_error); //Gov can't undo again
        
     }
        
}




