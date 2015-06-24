/* 
 * File:   global.h
 * Author: Oskar
 *
 * Globala varariabler som ska gå att komma åt från olika filer
 * En snabb lösning för att kunna dela ut poäng till spelarna, skapa unika heltalsvärden 
 * via "counter" samt även visa antalet kort som är kvar att spela ut. 
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#include "Player.h"

extern int num_of_cards; 
extern int counter; 

extern Player* global_player1; 
extern Player* global_player2;

#endif	/* GLOBAL_H */

