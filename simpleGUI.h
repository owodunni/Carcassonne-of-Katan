/* 
 * File:   simpleGUI.h
 * Author: Oskar
 * 
 * Innehåller grundläggande konstanter för hur GUI:t ska vara 
 *
 */

#ifndef SIMPLEGUI_H
#define	SIMPLEGUI_H

#include "Player.h" 
#include <string>
#include <SFML/Graphics.hpp> //IntRect
#include <SFML/System.hpp> // Clock, Time

using namespace std;

//grundläggande konstanta storheter
const int NUM_OF_CARDS= 25; 
const int CARD_SIZE = 80;
const int CARDS_X = 9;
const int CARDS_Y = 7; 
const int PANEL_WIDTH = 160;
const int PANEL_BORDER_WIDTH = 5;
const int WIDTH = CARDS_X * CARD_SIZE + PANEL_WIDTH + PANEL_BORDER_WIDTH;
const int HEIGHT = CARDS_Y * CARD_SIZE;
const sf::IntRect GAMEPAD_RECT(0, 0, CARDS_X * CARD_SIZE, CARDS_Y * CARD_SIZE);  

#endif	/* SIMPLEGUI_H */

