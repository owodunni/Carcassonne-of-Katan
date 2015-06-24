/* 
 * File:   Gamepad.cpp
 * Author: Oskar, Joel, Alexander
 * 
 * Beskrivning
 * Klassen för själva spelplanen. Håller koll på alla utlagda kort
 * och ger enkla funktioner för att kunna placera ut nya kort och spelpjäser* 
 */


#include "Gamepad.h"
#include <iostream>
#include <math.h>

/*
 * default konstruktor
 * 
 * laddar in alla bilder och placerar starkortet mitt på spelplanen
 */
Gamepad::Gamepad() {

    background_texture.loadFromFile("bg1200.jpg");
    background.setTexture(background_texture);
    background.setTextureRect(GAMEPAD_RECT);

    stad.loadFromFile("stad.jpg");
    stad_stad_stad_stad.loadFromFile("stad_stad_stad_stad.jpg");
    stad_vag_stad_vag.loadFromFile("stad_vag_stad_vag.jpg");
    vag_vag_vag.loadFromFile("vag_vag_vag.jpg");
    vag_null_stadstad.loadFromFile("vag_null_stadstad.jpg");
    null_stad_stad_stad.loadFromFile("null_stad_stad_stad.jpg");
    null_stad_stadstad.loadFromFile("null_stad_stadstad.jpg");
    null_vag_null_stad.loadFromFile("null_vag_null_stad.jpg");
    null_vag_stad_stad.loadFromFile("null_vag_stad_stad.jpg");
    vagvag_vagvag.loadFromFile("vagvag_vagvag.jpg");
    vagvag_stad.loadFromFile("vagvag_stad.jpg");
    vagvag_stadstad.loadFromFile("vagvag_stadstad.jpg");
    vag_null_vag.loadFromFile("vag_null_vag.jpg");
    null_vag_vag.loadFromFile("null_vag_vag.jpg");

    //sätta alla kortpekare
    for (int n = 0; n < CARDS_X; n++) {
        for (int m = 0; m < CARDS_Y; m++) {
            playing_cards[n][m] = new Card();
        }
    }

    Card* starting_card = new Card(null_vag_stad_stad, new Town, new Road, new Town, new Desert, "left", "", "up", "");
    int middle_x = floor(CARDS_X / 2);
    int middle_y = floor(CARDS_Y / 2);
    starting_card->set_corner_position(middle_x * CARD_SIZE, middle_y * CARD_SIZE);
    playing_cards[middle_x][middle_y] = starting_card;

    srand(time(NULL));
}

/*
 * draw
 * 
 * ritar ut alla korten på spelplanen på den angivna ytan
 */
void Gamepad::draw(sf::RenderWindow& window) const {

    window.draw(background);

    for (int n = 0; n < CARDS_X; n++)
        for (int m = 0; m < CARDS_Y; m++) {
            playing_cards[n][m]->draw(window);
        }
}

/*
 * place_gamepiece
 */
bool Gamepad::place_gamepiece(Gamepiece& piece, int x_coord, int y_coord) {
    //försöka vi placera på något annat än senaste kortet? 
    if (not(last_card->get_bounding_rect().contains(x_coord, y_coord)))
        return false;
    //else 
    //kolla vilket fält och uppdatera position för spelpjäsen
    string field_string;
    int top_x = last_card->get_bounding_rect().left;
    int top_y = last_card->get_bounding_rect().top; 
    int x = x_coord - top_x; 
    int y = y_coord - top_y;
    if (x >= y) {
        if (x + y >= 80) {
            field_string = "right";
            piece.set_center_position(top_x + 75, top_y + 40); 
        } else {
            field_string = "up";
            piece.set_center_position(top_x + 40, top_y + 5);
        }
    } else {// y > x
        if (x + y >= 80) {
            field_string = "down";
            piece.set_center_position(top_x + 40, top_y + 75);
        } else {
            field_string = "left";
            piece.set_center_position(top_x + 5, top_y + 40);
        }
    }
    
    int x_index = floor(x_coord / CARD_SIZE);
    int y_index = floor(y_coord / CARD_SIZE);
    return playing_cards[x_index][y_index]->place_gamepiece(field_string, piece);
}

/*
 * place_card
 * 
 * placerar ut det specificerade kortet på den plats på spelbrädet som 
 * innehåller den aktuella koordinaten. Ingen kontroll av om det är tillåtet att 
 * placera det nya kortet på den positionen utförs.  
 */
bool Gamepad::place_card(Card* new_card, int x_coord, int y_coord) {
    //kolla om platsen är upptagen
    int x_index = floor(x_coord / CARD_SIZE);
    int y_index = floor(y_coord / CARD_SIZE);
    if (playing_cards[x_index][y_index]->is_visible())
        return false;

    // kolla om ngn närliggande är besatt
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    if (x_index > 0)
        left = playing_cards[x_index - 1][y_index]->is_visible();
    if (x_index < CARDS_X - 1)
        right = playing_cards[x_index + 1][y_index]->is_visible();
    if (y_index > 0)
        up = playing_cards[x_index][y_index - 1]->is_visible();
    if (y_index < CARDS_Y - 1)
        down = playing_cards[x_index][y_index + 1]->is_visible();

    if (!(left or right or up or down))
        return false;

    // Kolla om närliggande är kompatibla
    bool compatible = true;

    if (left)
        compatible = compatible && playing_cards[x_index - 1][y_index]->is_compatible(new_card, "right");
    if (right)
        compatible = compatible && playing_cards[x_index + 1][y_index]->is_compatible(new_card, "left");
    if (up)
        compatible = compatible && playing_cards[x_index][y_index - 1]->is_compatible(new_card, "down");
    if (down)
        compatible = compatible && playing_cards[x_index][y_index + 1]->is_compatible(new_card, "up");

    if (!compatible)
        return false;

    //else, kortet är kompatibelt, vi ska nu placera ut det och koppla ihop det    
    new_card->set_corner_position(x_index * CARD_SIZE, y_index * CARD_SIZE);

    if (left)
        new_card->connect(playing_cards[x_index - 1][y_index], "left");
    if (right)
        new_card->connect(playing_cards[x_index + 1][y_index], "right");
    if (up)
        new_card->connect(playing_cards[x_index][y_index - 1], "up");
    if (down)
        new_card->connect(playing_cards[x_index][y_index + 1], "down");

    last_card = new_card;
    playing_cards[x_index][y_index] = new_card;
    return true;
}

/*
 * give_points
 */
void Gamepad::give_points() {
    for (int x = 0; x < CARDS_X; ++x) {
        for (int y = 0; y < CARDS_Y; ++y) {
            if (playing_cards[x][y]->is_visible()) {
                playing_cards[x][y]->give_points();
            }
        }
    }
}

/*
 * make_random_card
 * 
 * returnerar ett slumpmässigt valt nytt kort
 */
Card* Gamepad::make_random_card() {
    Card* tmp = nullptr;
    int rand_value;
    do {
        rand_value = rand() % 14 + 1;
    } while (rand_value == last_random_index);
    last_random_index = rand_value;

    switch (rand_value) {
        case 1: tmp = new Card(stad, new Desert, new Desert, new Desert, new Town, "", "", "", ""); //
            break;
        case 2: tmp = new Card(stad_stad_stad_stad, new Town, new Town, new Town, new Town, "", "", "", ""); //
            break;
        case 3: tmp = new Card(stad_vag_stad_vag, new Road, new Road, new Town, new Town, "", "", "right", "left"); //
            break;
        case 4: tmp = new Card(vag_vag_vag, new Desert, new Road, new Road, new Road, "", "", "", ""); //
            break;
        case 5: tmp = new Card(vag_null_stadstad, new Town, new Desert, new Town, new Road, "left", "", "up", ""); //
            break;
        case 6: tmp = new Card(null_stad_stad_stad, new Town, new Town, new Town, new Desert, "", "", "", ""); //
            break;
        case 7: tmp = new Card(null_stad_stadstad, new Town, new Town, new Town, new Desert, "left", "", "up", ""); //
            break;
        case 8: tmp = new Card(null_vag_null_stad, new Town, new Road, new Desert, new Desert, "", "", "", ""); //
            break;
        case 9: tmp = new Card(null_vag_stad_stad, new Town, new Road, new Town, new Desert, "left", "", "up", ""); //
            break;
        case 10: tmp = new Card(vagvag_vagvag, new Road, new Road, new Road, new Road, "left", "right", "up", "down"); //
            break;
        case 11: tmp = new Card(vagvag_stad, new Desert, new Road, new Town, new Road, "", "right", "", "down"); //
            break;
        case 12: tmp = new Card(vagvag_stadstad, new Town, new Road, new Town, new Road, "left", "right", "up", "down"); //
            break;
        case 13: tmp = new Card(vag_null_vag, new Desert, new Desert, new Road, new Road, "", "", "right", "left"); //
            break;
        case 14: tmp = new Card(null_vag_vag, new Desert, new Road, new Road, new Desert, "", "left", "down", ""); //
            break;
        default: tmp = new Card(null_vag_vag, new Desert, new Road, new Road, new Desert, "", "left", "down", ""); //
    }
    return tmp;
}
