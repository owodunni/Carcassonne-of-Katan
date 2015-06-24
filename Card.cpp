/* Fil: Card.cc
 * 
 * Implementeringsfil
 * 
 * Author: Joel, Alexander och Oskar 
 * 
 * Klassen för ett kort, håller reda på sina fyra fält, har funktioner för 
 * att placera ut spelpjäser, koppla ihop sig med andra kort mm samt grafiskt stöd
 */

#include "Card.h"

using namespace std;

/*
 * Skapar ett kort med angivna fält och textur (bild)
 */
Card::Card(
        const sf::Texture& card_texture,
        Field* up,
        Field* down,
        Field* left,
        Field* right,
        const string& upLink,
        const string& downLink,
        const string& leftLink,
        const string& rightLink) {

    fieldUp_ = up;
    fieldDown_ = down;
    fieldLeft_ = left;
    fieldRight_ = right;

    //länkar samman interna fält om dessa existerar.
    if (upLink != "") {
        fieldUp_->connect_field(get_field(upLink), convert_direction("up", upLink));
        fieldUp_->set_number_of_connected_fields(2);
    }
    if (downLink != "") {
        fieldDown_-> connect_field(get_field(downLink), convert_direction("down", downLink));
        fieldDown_->set_number_of_connected_fields(2);
    }
    if (leftLink != "") {
        fieldLeft_->connect_field(get_field(leftLink), convert_direction("left", leftLink));
        fieldLeft_->set_number_of_connected_fields(2);
    }
    if (rightLink != "") {
        fieldRight_->connect_field(get_field(rightLink), convert_direction("right", rightLink));
        fieldRight_->set_number_of_connected_fields(2);
    }
    sprite_.setTexture(card_texture);
    sprite_.setOrigin(card_texture.getSize().x / 2, card_texture.getSize().y / 2);
    visible_ = true;
}

Card::~Card() {
    delete fieldUp_;
    delete fieldDown_;
    delete fieldLeft_;
    delete fieldRight_;
}


/*
 * kompabilitet
 */
bool Card::is_compatible(const Card* other, const string& direction) const {
    return this->get_field(direction)->is_compatible(other->get_field(opposite_direction(direction)));
}

/*
 * Ihopkoppling
 */
void Card::connect(Card* other, const string& direction) {
    this->get_field(direction)->connect_neighbor(other->get_field(opposite_direction(direction)));
    this->get_field(direction)->update_number_of_gamepieces();
    this->get_field(direction)->increase_number_of_connected_fields();
    this->get_field(direction)->set_closed();
    if (this->get_field(direction)->is_closed()) {
        this->get_field(direction)->give_points();
    }
}

Field* Card::get_field(const string& direction) const {
    if (direction == "up") {
        return fieldUp_;
    } else if (direction == "right") {
        return fieldRight_;
    } else if (direction == "down") {
        return fieldDown_;
    } else if (direction == "left") {
        return fieldLeft_;
    }
}

void Card::give_points() {
    fieldUp_->give_points();
    fieldDown_->give_points();
    fieldLeft_->give_points();
    fieldRight_->give_points();
}

void Card::rotate_left() {
    Field* temp = fieldUp_;

    fieldUp_ = fieldRight_;
    fieldRight_ = fieldDown_;
    fieldDown_ = fieldLeft_;
    fieldLeft_ = temp;

    sprite_.rotate(-90); 
}

void Card::rotate_right() {

    Field* temp = fieldUp_;

    fieldUp_ = fieldLeft_;
    fieldLeft_ = fieldDown_;
    fieldDown_ = fieldRight_;
    fieldRight_ = temp;

    sprite_.rotate(90); 
}

/*
 * Ritar ut kortet på angiven yta
 */
void Card::draw(sf::RenderWindow& window) {
    window.draw(sprite_);
    if (gamepiece_visible_) {
        if(0 == (fieldUp_->get_number_of_gamepieces(1) +
                fieldUp_->get_number_of_gamepieces(2) +
                fieldDown_->get_number_of_gamepieces(1) +
                fieldDown_->get_number_of_gamepieces(2) +
                fieldRight_->get_number_of_gamepieces(1) +
                fieldRight_->get_number_of_gamepieces(2) +
                fieldLeft_->get_number_of_gamepieces(1) +
                fieldLeft_->get_number_of_gamepieces(2)))
            gamepiece_visible_ = false; 
        gamepiece_.draw(window);        
    }        
}

/*
 * Uppdaterar kortets färg
 */
void Card::set_color(const sf::Color& color) {
    sprite_.setColor(color);
}

/*
 * Uppdaterar positionen för kortets övre vänstra hörnet
 */
void Card::set_corner_position(int new_x, int new_y) {
    sprite_.setPosition(new_x + 0.5 * sprite_.getTextureRect().width, new_y + 0.5 * sprite_.getTextureRect().height);
}

/*
 * Uppdaterar positionen för kortets mittpunkt
 */
void Card::set_center_position(int new_x, int new_y) {
    sprite_.setPosition(new_x, new_y);
}

sf::FloatRect Card::get_bounding_rect() const {
    return sprite_.getGlobalBounds();
}

string Card::opposite_direction(const string& direction) {
    if (direction == "up") {
        return "down";
    } else if (direction == "down") {
        return "up";
    } else if (direction == "left") {
        return "right";
    } else {
        return "left";
    }
}

bool Card::place_gamepiece(const string& direction, Gamepiece& gamepiece) {

    if (get_field(direction)->place_gamepiece(gamepiece)) {
        gamepiece_ = gamepiece;
        gamepiece_visible_ = true;
        return true;
    }
    //else
    return false;
}

string Card::convert_direction(const string& current_location, const string& connected_direction) {
    if (current_location == "up") {
        if (connected_direction == "down") {
            return "opposite";
        } else if (connected_direction == "left") {
            return "right";
        } else if (connected_direction == "right") {
            return "left";
        }
    } else if (current_location == "down") {
        if (connected_direction == "up") {
            return "opposite";
        } else if (connected_direction == "right") {
            return "right";
        } else if (connected_direction == "left") {
            return "left";
        }
    } else if (current_location == "left") {
        if (connected_direction == "up") {
            return "left";
        } else if (connected_direction == "right") {
            return "opposite";
        } else if (connected_direction == "down") {
            return "right";
        }
    } else if (current_location == "right") {
        if (connected_direction == "up") {
            return "right";
        } else if (connected_direction == "left") {
            return "opposite";
        } else if (connected_direction == "down") {
            return "left";
        }
    }
}