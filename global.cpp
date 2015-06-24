/* 
 * File:   global.cpp
 * Author: Oskar
 * 
 * Globala varariabler som ska gå att komma åt från olika filer
 * En snabb lösning för att kunna dela ut poäng till spelarna, skapa unika heltalsvärden 
 * via "counter" samt även visa antalet kort som är kvar att spela ut. 
 */

#include "Player.h"

int counter = 0; //för unika siffror i field

Player* global_player1 = nullptr; 
Player* global_player2 = nullptr; 

int num_of_cards = 1; 
