/* 
 * File:   main.h
 * Author: Oskar
 *
 * Innehåller variabler som ska vara globala i filen main.cpp
 */

#ifndef MAIN_H
#define	MAIN_H

#include <SFML/Graphics.hpp>

//spelstatus, flaggor 
static int current_player; 
static bool placing_card;  
static bool game_ended; 

// för textutskrift av vinst-meddelande
sf::Text victory_message; 
sf::Font font; 

//objekt för att visa nya kortet vid musepekaren
static sf::Clock my_clock; 
static sf::Time elapsed_time; 
static bool incorrect_card_placement = false; 

#endif	/* MAIN_H */

