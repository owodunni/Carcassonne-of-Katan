/* 
 * File:   Gamepad.h
 * Author: Oskar
 * 
 * Klassen för själva spelplanen. Håller koll på alla utlagda kort
 * och ger enkla funktioner för att kunna placera ut nya kort och spelpjäser
 * samt slumpa fram nya kort att spela med. 
 * 
 * Har internt en matris för att lagra alla kort. Storleken på matrisen 
 * bestäms av konstanterna i simpleGUI.h
 * Denna klass ansvarar även för att läsa in alla bilder för som behövs 
 * till korten. 
 */


#ifndef GAMEPAD_H
#define	GAMEPAD_H

#include "simpleGUI.h"
#include "Card.h"
#include "Gamepiece.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Field.h"
#include "Road.h"
#include "Desert.h"
#include "town.h"

class Gamepad {
public:
    Gamepad();
    Gamepad(const Gamepad& orig) = default;
    virtual ~Gamepad() = default;

    void draw(sf::RenderWindow& window) const; 
    bool place_card(Card* new_card, int x_coord, int y_coord);
    bool place_gamepiece(Gamepiece& new_gamepiece, int x_coord, int y_coord);
    void give_points(); 

    Card* make_random_card(); 

private:
    Card* playing_cards [CARDS_X][CARDS_Y];
    Card* last_card;
    int last_random_index = 9; 

    //textur för bakgrundsbilden
    sf::Texture background_texture;
    sf::Sprite background;

    //texturer för alla kort-bilder
    sf::Texture stad;
    sf::Texture stad_stad_stad_stad;
    sf::Texture stad_vag_stad_vag;
    sf::Texture vag_vag_vag;
    sf::Texture vag_null_stadstad;
    sf::Texture null_stad_stad_stad;
    sf::Texture null_stad_stadstad;
    sf::Texture null_vag_null_stad;
    sf::Texture null_vag_stad_stad;
    sf::Texture vagvag_vagvag;
    sf::Texture vagvag_stad;
    sf::Texture vagvag_stadstad;
    sf::Texture vag_null_vag;
    sf::Texture null_vag_vag;
};

#endif	/* GAMEPAD_H */

