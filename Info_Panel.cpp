/* 
 * File:   Info_Panel.cpp
 * Author: Oskar
 * 
 * Klassen för panelen i högra delen av GUI:t
 */

#include "Info_Panel.h"
#include <sstream>

/*
 * Defaultonstruktor
 * 
 * Laddar in font och sätter alla variabler utom kortet som ska visas
 */
Info_Panel::Info_Panel(const Player& player1, const Player& player2)
: player1_(&player1), player2_(&player2) {

    null_texture_.loadFromFile("null.jpg");
    null_sprite_.setTexture(null_texture_);
    null_sprite_.setPosition(WIDTH - PANEL_WIDTH + CARD_SIZE / 2, CARD_SIZE / 2);

    num_of_cards_.setFont(font_);
    num_of_cards_.setCharacterSize(15);
    num_of_cards_.setString("");
    num_of_cards_.setPosition(WIDTH - PANEL_WIDTH + 5, 150);
    num_of_cards_.setColor(sf::Color::Black);

    font_.loadFromFile("BEBAS___.ttf");

    name1_.setFont(font_);
    name1_.setCharacterSize(20);
    name1_.setString(player1_->get_name());
    name1_.setPosition(WIDTH - PANEL_WIDTH + 5, 200);
    name1_.setColor(sf::Color::Black);

    piece1_ = Gamepiece(*player1_);
    piece1_.set_corner_position(WIDTH - PANEL_WIDTH + 15, 240);

    gamepieces1_.setFont(font_);
    gamepieces1_.setCharacterSize(15);
    gamepieces1_.setString("");
    gamepieces1_.setPosition(WIDTH - PANEL_WIDTH + 5, 260);
    gamepieces1_.setColor(sf::Color::Black);

    points1_.setFont(font_);
    points1_.setCharacterSize(15);
    points1_.setString("");
    points1_.setPosition(WIDTH - PANEL_WIDTH + 5, 280);
    points1_.setColor(sf::Color::Black);

    name2_.setFont(font_);
    name2_.setCharacterSize(20);
    name2_.setString(player2_->get_name());
    name2_.setPosition(WIDTH - PANEL_WIDTH + 5, 350);
    name2_.setColor(sf::Color::Black);

    piece2_ = Gamepiece(*player2_);
    piece2_.set_corner_position(WIDTH - PANEL_WIDTH + 15, 390);

    gamepieces2_.setFont(font_);
    gamepieces2_.setCharacterSize(15);
    gamepieces2_.setString("");
    gamepieces2_.setPosition(WIDTH - PANEL_WIDTH + 5, 410);
    gamepieces2_.setColor(sf::Color::Black);

    points2_.setFont(font_);
    points2_.setCharacterSize(15);
    points2_.setString("");
    points2_.setPosition(WIDTH - PANEL_WIDTH + 5, 430);
    points2_.setColor(sf::Color::Black);



    background_ = sf::RectangleShape(sf::Vector2f(PANEL_WIDTH, HEIGHT));
    background_.setPosition(WIDTH - PANEL_WIDTH, 0);
    background_.setFillColor(sf::Color::Yellow);
    background_.setOutlineThickness(PANEL_BORDER_WIDTH);
    background_.setOutlineColor(sf::Color::Black);
}

void Info_Panel::set_current_card(Card* new_card) {
    current_card_ = new_card;
    current_card_->set_center_position(WIDTH - PANEL_WIDTH + CARD_SIZE, CARD_SIZE);
}

Card* Info_Panel::get_current_card() const {
    return current_card_;
}

void Info_Panel::draw(sf::RenderWindow& window, int current_player, bool show_card) {
    if (current_player == 0) {
        name1_.setStyle(sf::Text::Underlined | sf::Text::Bold);
        name2_.setStyle(sf::Text::Regular);
    } else {
        name1_.setStyle(sf::Text::Regular);
        name2_.setStyle(sf::Text::Underlined | sf::Text::Bold);
    }

    std::stringstream ss;
    ss << "Pieces: " << player1_->get_gamepieces();
    gamepieces1_.setString(ss.str());

    std::stringstream ee;
    ee << "Score: " << player1_->get_score();
    points1_.setString(ee.str());

    std::stringstream dd;
    dd << "Pieces: " << player2_->get_gamepieces();
    gamepieces2_.setString(dd.str());

    std::stringstream ff;
    ff << "Score: " << player2_->get_score();
    points2_.setString(ff.str());

    //cout << num_of_cards << endl;
    std::stringstream gg;
    gg << "Remaining cards: " << (NUM_OF_CARDS - num_of_cards);
    num_of_cards_.setString(gg.str());

    window.draw(background_);
    if (show_card) {
        current_card_->set_center_position(WIDTH - PANEL_WIDTH + CARD_SIZE, CARD_SIZE);
        current_card_->draw(window);
    } else
        window.draw(null_sprite_);
    
    window.draw(num_of_cards_);

    window.draw(name1_);
    piece1_.draw(window);
    window.draw(gamepieces1_);
    window.draw(points1_);

    window.draw(name2_);
    piece2_.draw(window);
    window.draw(gamepieces2_);
    window.draw(points2_);
}

void Info_Panel::rotate_card_left() {
    current_card_->rotate_left();
}

void Info_Panel::rotate_card_right() {
    current_card_->rotate_right();
}