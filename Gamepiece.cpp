/* 
 * File:   Gamepiece.cpp
 * Author: Oskar
 * 
 * Enkel klass för spelpjäser. Varje spelpjäs känner till vilken spelaren den
 * tillhör och har enkla funktioner för grafiken.  
 */

#include "Gamepiece.h"

Gamepiece::Gamepiece(const Player& player) : owner_(&player) {
    shape_ = sf::CircleShape(5);
    shape_.setFillColor(owner_->get_color());
}

Gamepiece::Gamepiece(const Gamepiece& orig) {
 owner_ = orig.owner_;
 shape_ = orig.shape_;  
}

Gamepiece::~Gamepiece() {
    owner_ = nullptr; 
}

/*Gamepiece& Gamepiece::operator=(const Gamepiece& rhs) {
    Gamepiece tmp(rhs); 
    return tmp; 
}*/

// vanliga funktioner
void Gamepiece::draw(sf::RenderWindow& window) const {
    window.draw(shape_);
}

void Gamepiece::set_corner_position(int new_x, int new_y) {
    shape_.setPosition(new_x, new_y);
}

void Gamepiece::set_center_position(int new_x, int new_y) {
    int w = shape_.getGlobalBounds().width;
    int h = shape_.getGlobalBounds().height;
    shape_.setPosition(new_x - w / 2, new_y - h / 2);
}


