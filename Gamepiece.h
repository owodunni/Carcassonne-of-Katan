/* 
 * File:   Gamepiece.h
 * Author: Oskar
 * 
 * Enkel klass för spelpjäser. Varje spelpjäs känner till vilken spelaren den
 * tillhör och har enkla funktioner för grafiken. 
 */

#ifndef GAMEPIECE_H
#define	GAMEPIECE_H

#include "Player.h"
#include <SFML/Graphics.hpp>

class Gamepiece {
public:
    Gamepiece() = default;
    Gamepiece(const Player& player);
    Gamepiece(const Gamepiece& orig);
    ~Gamepiece();    
    Gamepiece& operator=(const Gamepiece&) = default;  

    void draw(sf::RenderWindow& window) const;
    void set_corner_position(int new_x, int new_y);
    void set_center_position(int new_x, int new_y);
    
    const Player* get_player() const {return owner_;}; 
    sf::Vector2f& get_coords() const {shape_.getPosition(); }

private:
    const Player* owner_; 
    sf::CircleShape shape_;



};

#endif	/* GAMEPIECE_H */

