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
//#include "HPP/main.hpp"

using namespace coup;
TEST_CASE("Game Initialization") {
    Game game{};
    CHECK(game.players().size() == 0);
    Governor gov(game, "gov_1");
    Spy spy(game, "spy_1");
    Baron baron(game, "baron_1");
    General gen(game, "general_1");
    Judge judge(game, "judge_1");
    Merchant merchant(game, "mer_1");
    CHECK(game.getNumOfPlayers() == 6);
    CHECK_THROWS_AS(game.winner(), std::runtime_error); // Game not over
    CHECK_THROWS_AS(General(game, "general_2"), std::runtime_error); // More than 6 players

    std::vector<std::string> players = game.players();
    CHECK(players.back() == "mer_1");
    CHECK(gov.getIsAlived() == true);
    game.removePlayer(&gov);
    CHECK(game.getNumOfPlayers() == 5);
    
    CHECK(game.turn()=="gov_1");

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

    SUBCASE("Unvalid Player Actions") {
        CHECK_THROWS_AS(spy.gather(), std::runtime_error); // Not gov's turn
        CHECK_THROWS_AS(gov.coup(spy), std::runtime_error); // Don't have enough coins
       
    }
    SUBCASE("Try gather or tax after sanction"){
        for(int i = 0; i < 4; ++i) {
            gov.gather();
            spy.gather();
            baron.tax();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        
            
        CHECK(game.turn()=="gov_1");
        CHECK(gov.coins() == 4);
        gov.sanction(spy);
        
        
        
        CHECK_THROWS_AS(spy.gather(), std::runtime_error); // Blocked by sanction
        CHECK_THROWS_AS(spy.tax(), std::runtime_error); // Not gov's turn
 
     }

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
        
        CHECK(spy.coins() == 10);
        CHECK_THROWS_AS(spy.gather(), std::runtime_error); // Have to coup

        spy.coup(judge);
        CHECK(judge.getIsAlived() == false);

        CHECK_THROWS_AS(baron.arrest(judge), std::runtime_error); // Arrest a dead player
  
    }

    SUBCASE("Test spy ability") {
        for(int i = 0; i <= 3; ++i) {
            gov.gather();
            spy.tax();
            baron.gather();
            gen.gather();
            judge.gather();
            merchant.gather();
        }
        CHECK(gov.coins() == 4);
        CHECK(spy.getCoins(gov) == 4); // Spy can see gov's coins
        spy.prventArrest(gov);
        CHECK_THROWS_AS(gov.arrest(gen), std::runtime_error); // gov can't arrest 

        gov.gather();
        spy.tax();

        CHECK(baron.coins() == 4);
        CHECK(judge.coins() == 4);

        baron.arrest(judge);

        CHECK(baron.coins() == 5);
        CHECK(judge.coins() == 3);    

        CHECK_THROWS_AS(gen.arrest(judge), std::runtime_error); // gov can't arrest the same player twice

    }

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

    SUBCASE("Test Governor ability"){
        CHECK(gov.coins() == 0);
        gov.tax();
        CHECK(gov.coins() == 3); //gov should have 3 coins after tax
        spy.tax();
        CHECK(spy.coins() == 2);

        gov.undo(spy);
        CHECK(spy.coins() == 0); //Spy should have 0 coins after undo

       

        baron.tax();
        gen.arrest(baron);
        CHECK(baron.coins() == 1); //Baron should have 1 coins after arrest
         CHECK_THROWS_AS(gov.undo(baron), std::runtime_error);// gov cant undo when baron dont have enough coins

        judge.gather();
         CHECK_THROWS_AS(gov.undo(judge), std::runtime_error);// gov cant undo when the last move is not tax

    }

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
        CHECK(merchant.coins() == 5);

        gov.arrest(merchant);
        CHECK(merchant.coins() == 3); //Merchant should have 3 coins after arrest
        CHECK(gov.coins() == 4);
    }

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
        CHECK(gov.coins() == 1); //Sanction  cost 3 coins
        spy.sanction(judge);
        CHECK(spy.coins() == 0); // Sanction on Judg  cost 4 coins

        baron.bribe();
        baron.tax();
        baron.tax();
        CHECK(baron.coins() == 4); //Baron should have 4 coins after tax

        gen.bribe();

        judge.undo(gen);

        CHECK_THROWS_AS(gen.tax(), std::runtime_error); 
        CHECK(gen.coins() == 0); //Gen should have 0 coins after undo

        CHECK(game.turn() == "judge_1"); 
    }

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




