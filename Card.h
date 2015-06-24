/* Fil: Card.h
 * 
 * Inkluderingsfil
 * 
 * Skapad av Joel och Alexander.
 * 
 * Den här koden är färdig med enda undantaget att den nu är anpassad för 
 * en just nu icke-existerande klass "Field". Använder just nu en struct i
 * klassen Card. 
 * 
 * Stödet för grafiken är skrivet av Oskar, anges i aktuella funktioner 
 * 
 * TODO: Ordna korrekt kopieringstilldelning, destruktor etc, 
 * 
 */

#ifndef CARD_H
#define	CARD_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Road.h"
#include "town.h"
#include "Desert.h"

class Card {
public:

    //Konstruktorer och destruktorer
    Card() = default;
    Card(
            const sf::Texture& card_texture,
            Field*,
            Field*,
            Field*,
            Field*,
            const std::string& = "",
            const std::string& = "",
            const std::string& = "",
            const std::string& = ""
            );
    ~Card();
    Card(const Card& otherCard) = delete; //Kopieringskonstruktor
    Card& operator=(const Card& otherCard) = delete; //kopieringstilldelning
    Card(Card&& rhs) = delete; //flyttkonstruktor
    Card& operator=(Card&& rhs) = delete; //flyttilldelning

    //Field funkionalitet
    bool is_compatible(const Card* other, const string& direction) const;
    void connect(Card* other, const string& direction);
    Field* get_field(const string& direction) const;
    bool place_gamepiece(const string& direction, Gamepiece& gamepiece);
    void give_points();
    //bool is_closed();

    //Card funkionalitet
    void rotate_left();
    void rotate_right();
    //void swap(Card&);

    //Grafik funktionalitet

    bool is_visible() const {
        return visible_;
    }
    void draw(sf::RenderWindow& window) ;
    void set_color(const sf::Color& color);
    void set_corner_position(int new_x, int new_y);
    void set_center_position(int new_x, int new_y);
    sf::FloatRect get_bounding_rect() const;

private:
    //hjälpfunktioner
    static string opposite_direction(const std::string&);
    static string convert_direction(const std::string&, const std::string&);

    Field* fieldUp_ = nullptr; //fyra pekare pï¿½ de olika fï¿½lten
    Field* fieldDown_ = nullptr;
    Field* fieldLeft_ = nullptr;
    Field* fieldRight_ = nullptr;

    // för grafiken, @author Oskar
    sf::Sprite sprite_;
    bool visible_ = false;
    Gamepiece gamepiece_;
    bool gamepiece_visible_ = false;
};

#endif	/* CARD_H */

