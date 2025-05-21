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


}




