/* 
 * File:   Info_Panel.h
 * Author: Oskar
 *
 * Klassen för att panelen som finns i GUI:t. Får en storlek i enighet 
 * med konstanterna i simpleGUI.h och ger enkla funktioner för att rita ut
 * och uppdatera det aktuella kortet. 
 */

#ifndef INFO_PANEL_H
#define	INFO_PANEL_H

#include "simpleGUI.h"
#include "Player.h"
#include "Gamepiece.h"
#include "Card.h"
#include <SFML/Graphics.hpp>
#include "global.h"

class Info_Panel {
public:
    Info_Panel() = default;
    Info_Panel(const Player& player1, const Player& player2); 
    Info_Panel(const Info_Panel& orig) = default; 
    virtual ~Info_Panel() = default;
    
    void set_current_card(Card* new_card); 
    Card* get_current_card() const; 
    void draw(sf::RenderWindow& window, int current_player, bool show_card);
    void rotate_card_left(); 
    void rotate_card_right(); 
    
private:
    const Player* player1_; 
    const Player* player2_; 
    Gamepiece piece1_; 
    Gamepiece piece2_; 
    sf::Text name1_; 
    sf::Text name2_; 
    sf::Text gamepieces1_;
    sf::Text gamepieces2_;
    sf::Text points1_; 
    sf::Text points2_;
    sf::Text num_of_cards_;
    
    Card* current_card_; 
    
    sf::RectangleShape background_; 

    sf::Font font_;
    sf::Texture null_texture_; 
    sf::Sprite null_sprite_; 
};

#endif	/* INFO_PANEL_H */

