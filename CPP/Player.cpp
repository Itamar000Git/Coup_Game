//itamarbabai98@gmail.com

#include <iostream>
#include <string>
#include <vector>
#include "../HPP/Game.hpp"
#include "../HPP/Player.hpp"
#include <cstring>

namespace coup
{  
    /**
     * @brief The Player class represents a player in the Coup game.
     * It contains information about the player's name, coins, role, and actions.
     * @throws std::runtime_error if this is not the player's turn (never will be when he is dead),
     *  if the player has too many coins, if the player is blocked, or if this is an after bribe action and blocked.
     */
    void Player::gather(){
    
        if(game.turn()!=name){ //this is not the player's turn
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){ //the player has too many coins and need to coup
            throw std::runtime_error("You have too many coins you need to coup");
        }
        if(isBlocked==true){ //the player is sanctioned and cant take gather
            throw std::runtime_error("You are blocked");
        }
        if(preventToArrest==true){ //abort the action if the player is prevented to arrest
            setPreventToArrest(false);
        }
        
        if(blockToBribe==true){ //the player is blocked by bribe
            setPreventToBribe(false); //abort the block
            freeMoves=0; //decrease the free moves
            game.nextTurn(); // move to the next player            
            //lastMove.push_back("gather"); 
            throw std::runtime_error("You are blocked by bribe");
        }
        starter(); //function that add a coin to the player if he is a merchant with more than 2 coins
        coinsNum++; //need to add check if there is a block
        std::cout <<"gather with: " << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        if(freeMoves>0){ // check if there is a free move relevant only after bribe
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
    
        lastMove.push_back("gather");
    }

    /**
     * @brief The player can tax 2 coins from the bank
     * @throws std::runtime_error if this is not the player's turn (never will be when he is dead),
     *  if the player has too many coins, if the player is blocked, or if this is an after bribe action and blocked.
     */
      void Player::tax(){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
        }
        if(isBlocked==true){
            throw std::runtime_error("You are blocked");
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            game.nextTurn();
            freeMoves=0;
            //lastMove.push_back("tax");
            throw std::runtime_error("You are blocked by bribe");
        }
        starter(); //function that add a coin to the player if he is a merchant with more than 2 coins

        coinsNum+=2; //tax 2 coins from the bank
        std::cout <<"tax with: " << name<< " that is"<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }  
        lastMove.push_back("tax");
     }

     /**
      * @brief The player can bribe with 4 coins and in return get 2 moves
      * @throws std::runtime_error if this is not the player's turn (never will be when he is dead),
      *  if the player has too many coins, if the player is blocked, or if this is an after bribe action and blocked,
      *  if the player has lest than 3 coins.
      */
    void Player::bribe(){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            
        }
        if(coinsNum<=3){ //the player has less than 3 coins
            throw std::runtime_error("You dont have enough coins");
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(isBlocked==true){ //abort the block when the player play a different action from gather or tax
            setIsBlocked(false);
        }
        if(blockToBribe==true){ //if in real time the player is blocked by bribe
            setPreventToBribe(false);
            freeMoves=0;

            game.nextTurn();
            
            lastMove.push_back("bribe");
            throw std::runtime_error("You are blocked by bribe");
        }
        starter(); //function that add a coin to the player if he is a merchant with more than 2 coins
        coinsNum=coinsNum-4; //bribe cost 4 coins
        freeMoves=1; //the player get 2 moves
        lastMove.push_back("bribe");

        std::cout <<"bride with: " << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
    }
  
    /**
     * @brief The player can arrest another player and take 1 coin from him
     * @param player The player to be arrested
     * @throws std::runtime_error if this is not the player's turn (never will be when he is dead),
     *  if the player has too many coins, if the player is the last arrested player, or if this is an after bribe action and blocked,
     *  if the player has less than 1 coin, if the arrested player is not the arresing one,
     *  if the arresting player prevet to arrest, if the arrested player is dead.
     */
    void Player::arrest( Player &player){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
        }
        if(preventToArrest==true){ //the player is prevented to arrest
            throw std::runtime_error("You are blocked");
        }
        if(this==&player){ //the player is arresting himself
            throw std::runtime_error("You cant arrest yourself");
        }
        if(player.getName()==game.lastArrested()){ //the player is the last arrested player
            throw std::runtime_error("You cant arrest the same player twice");
        }
        if(player.getIsAlived()==false){ //the player is dead
            throw std::runtime_error("You cant arrest a dead player");
        }
        int num=player.coins();
        if(num==0){ //the player has no coins
            throw std::runtime_error("You cant arrest a player with 0 coins");
        }
        if(isBlocked==true){
            setIsBlocked(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            freeMoves=0;
            game.nextTurn();
            lastMove.push_back("arrest");
            throw std::runtime_error("You are blocked by bribe");
        }
        starter(); //function that add a coin to the player if he is a merchant with more than 2 coins
        if(player.getRoll()=="General"){ //General get his coins back
           
            std::cout<<"General get his coins back"<<std::endl;
        }
        else if(player.getRoll()=="Merchant"){ //Merchant pay 2 coins to the bank instead
            if(num==1){
                throw std::runtime_error("You dont have enough coins to arrest Merchent ");
            }
            player.setLastCoinNum(num-2); //in case of merchant we need to pay 2 coins to the bank instead of 1
        }
        else{
            player.setLastCoinNum(num-1);//for all the other players we take 1 coin
            coinsNum=coinsNum+1; //add 1 coin to the arresting player
        }
        starter(); //function that add a coin to the player if he is a merchant with more than 2 coins
        game.setLastArrest(player.getName()); //set the last arrested player
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
        lastMove.push_back("arrest");
        std::cout << name<< " that is "<< role<<" arrest : "<< player.getName() <<" that is: "<< player.getRoll()<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
      
        
    }

    /**
     * @brief The player can sanction another player and prevent him from taking gather or tax actions
     * @param player The player to be sanctioned
     * @throws std::runtime_error if this is not the player's turn (never will be when he is dead),
     *  if the player has too many coins, or if this is an after bribe action and blocked, if the other player is dead,
     *  if its the same player, if the player dont have enough coins.
     */
    void Player::sanction( Player &player){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            
        }
        if(player.getIsAlived()==false){
            throw std::runtime_error("You cant sanction a dead player");
        }
        if(this==&player){ //the player is sanctioning himself
            throw std::runtime_error("You cant sanction yourself");
        }        
        int num=coins();
        int lim=3;
        if(player.getRoll()=="Judge"){ //for sanction a judge we need to pay 4 coins instead of 3
            lim=4;
        }
        if(num<lim){ //the player has less than 3 or 4 coins(depends on the role)
            throw std::runtime_error("You dont have enough coins");
        }
       
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(isBlocked==true){
            setIsBlocked(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            freeMoves=0;
            game.nextTurn();
            lastMove.push_back("arrest");
            throw std::runtime_error("You are blocked by bribe");
        }
        
        starter(); //function that add a coin to the player if he is a merchant with more than 2 coins
     
        coinsNum=coinsNum-lim; //pay 3 or 4 coins to the bank
        player.setIsBlocked(true); //set the player as blocked

        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
        lastMove.push_back("sanction");

        std::cout <<"sanction with:" << name<< " that is "<< role<<std::endl;
    }
   
    /**
     * @brief The player can coup another player and remove him from the game
     * @param player The player to be couped
     * @throws std::runtime_error if this is not the player's turn (never will be when he is dead),
     * if the player dont have enough coins to coup, if the player hoe being couped is dead,
     *  or if this is an after bribe action and blocked, if its the same player.
     */
    void Player::coup( Player &player,bool gui){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
            return;
        }
        if(coinsNum<7){ //the player has less than 7 coins
            throw std::runtime_error("You dont have enough coins");
            return;
        }
        if(player.getIsAlived()==false){
            throw std::runtime_error("You cant coup a dead player");
            return;
        }
        if(this==&player){
            throw std::runtime_error("You cant coup yourself");
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(isBlocked==true){
            setIsBlocked(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            game.nextTurn();
            freeMoves=0;
            lastMove.push_back("coup");
            throw std::runtime_error("You are blocked by bribe");
            return;
        }
        starter(); //function that add a coin to the player if he is a merchant with more than 2 coins
        coinsNum=coinsNum-7; //coup cost 7 coins
        if(gui==true){ //when using the gui we use a different function to set the player as dead
             player.setIsAlivedGui(false); //in case of genral he can save himself
        }
        else{
            player.setIsAlived(false); //in case of genral he can save himself

        }
        
        std::cout <<"coup with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;
        std::cout<<"Player: "<< player.getName() << " is dead"<<std::endl;
        game.removePlayer(&player);
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn();
        }
        lastMove.push_back("coup");
    }

    /**
     * @brief The player can skip his turn and add a coin to his coins, when the player sanctioned ,
     * and have less than 3 coins, and prevented to arrest, he can skip his turn.
     * @throws std::runtime_error if this is not the player's turn (never will be when he is dead),
     *  if the player has too many coins, or if this is an after bribe action and blocked.
     */
    void Player::skipTurn(){
        if(game.turn()!=name){
            throw std::runtime_error("This is not your turn");
        }
        if(coinsNum>=10){
            throw std::runtime_error("You have too many coins you need to coup");
            
        }
        if(preventToArrest==false||isBlocked==false||coinsNum>=3){
            throw std::runtime_error("You can use skip just in spatial event!");
        }
        if(preventToArrest==true){
            setPreventToArrest(false);
        }
        if(isBlocked==true){
            setIsBlocked(false);
        }
        if(blockToBribe==true){
            setPreventToBribe(false);
            freeMoves=0;
            game.nextTurn();
            lastMove.push_back("arrest");
            throw std::runtime_error("You are blocked by bribe");
        }
        if(freeMoves>0){
            freeMoves--;
        }
        else{
            game.nextTurn(); //move to the next player
        }
        starter(); //function that add a coin to the player if he is a merchant with more than 2 coins
        lastMove.push_back("skip");
        std::cout <<"skip with:" << name<< " that is "<< role<<std::endl;
        std::cout<<"Num of coins is: "<<coinsNum<<std::endl;

    }
}