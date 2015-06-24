/* 
 * File:   Player.cpp
 * Author: Oskar och Milton
 * 
 */

#include "Player.h"

sf::Color Player::get_color() const {
    return color_;
}

std::string Player::get_name() const {
    return name_;
}