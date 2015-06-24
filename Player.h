/* 
 * File:   Player.h
 * Author: Oskar
 *
 * Enkel klass för att hålla koll på spelarnas namn, antal spelpjäser de har 
 * kvar och poäng de har erhållit. 
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include <SFML/Graphics/Color.hpp>
#include <string>

class Player {
public:
    Player() = default;
    Player(const sf::Color& color, std::string& name, int index) 
    : color_(color), name_(name), index_(index) {};
    Player(const Player& orig) = default;
    virtual ~Player() = default;

    sf::Color get_color() const;
    std::string get_name() const;
    int get_index() const {return index_; }    
    int get_score() const {return score_; }
    void increase_score(int increment) {score_ += increment*10; }
    int get_gamepieces() const {return gamepieces_; }
    bool has_gamepieces() {return (gamepieces_ > 0); }
    void increase_gamepieces(int number) {gamepieces_ += number; }
    void decrease_gamepieces() {gamepieces_ --; } 

private:
    sf::Color color_;
    std::string name_;
    int index_ = -1; //ska ha värdet 1 eller 2 om korrekt 
    int score_ = 0; 
    int gamepieces_ = 7; 

};

#endif	/* PLAYER_H */

