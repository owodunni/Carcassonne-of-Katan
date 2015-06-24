/* 
 * File:   Field.h
 * Author: Joel och Anna
 * 
 * Inkluderingsfil för fältklassen. Innehåller variabler för varje fälts pekare
 * till eventuella sammankopplade fält. Innehåller även datatyper för att se
 * hur många gamepieces som är utplacerade på ett stort fält, hur många fält 
 * som är sammankopplade och om fältet är stängt eller inte. 
 *
 */

#ifndef FIELD_H
#define FIELD_H
#include <string>
#include <iostream>
#include "Player.h"
#include "Gamepiece.h"
#include "simpleGUI.h"

using namespace std;

class Field {
public:

    Field() = default; //Konstruktor
    ~Field() = default; //Destruktor
    Field(const Field&) = default;
    Field(Field&&) = default; //Move-kopiering
    Field& operator=(const Field&) = default; //Tilldelningskonstruktor
    Field& operator=(Field&&) = default; // Move-tilldelning

    //Fancy funktionalitet
    virtual Field* clone() = 0;
    virtual bool is_compatible(Field*)const = 0;

    //Field funktionalitet
    virtual void set_number_of_connected_fields(int) = 0;
    virtual void connect_field(Field*, string) = 0;
    virtual void increase_number_of_connected_fields() = 0;
    virtual void single_set_number_of_connected_fields(int) = 0;
    virtual void double_set_number_of_connected_fields() = 0;
    virtual int get_number_of_connected_fields() const = 0;
    virtual Field* get_connected_field_on_card() const = 0;
    virtual Field* get_neighborField() const = 0;
    virtual bool same_closeable_bool(Field*) const = 0;
    virtual void same_closeable_set_number_of_connected_fields() = 0;
    virtual void equal_number_of_connected_fields(int) = 0;
    virtual int get_closeable_number() const = 0;
    virtual void set_closeable_number(int) = 0;
    virtual void different_closeable_set_number_of_connected_fields() = 0;
    virtual void equal_closeable_number(int) = 0;
    virtual void connect_neighbor(Field*) = 0;
    virtual bool get_bool_connected() const = 0;
    virtual void update_number_of_gamepieces() = 0;
    virtual int get_number_of_gamepieces(int) const = 0;
    virtual void set_number_of_gamepieces() = 0;
    virtual void set_number_of_gamepieces(int, int) = 0;
    virtual void set_closeable_gamepiece() = 0;
    virtual void set_closeable_gamepiece(int) = 0;
    virtual int get_closeable_gamepiece() const = 0;
    virtual void double_update_number_of_gamepieces() = 0;
    virtual void equal_number_of_gamepieces(int, int, int) = 0;
    virtual void add_gamepiece_player1() = 0;
    virtual void add_gamepiece_player2() = 0;
    virtual bool got_gamepieces() const = 0;
    virtual bool allowed_to_put_gamepiece() const = 0;

    virtual bool is_closed() const = 0;
    virtual void set_closed() = 0;
    virtual void both_sides_closed() = 0;
    virtual void set_whole_closeable_closed() = 0;
    virtual bool got_neighbor_on_card() const = 0;
    virtual int get_closeable_closed() const = 0;
    virtual void set_whole_closed() = 0;
    virtual void clear_gamepieces() = 0;
    virtual bool get_whole_closed() const = 0;
    virtual void set_closeable_closed(int) = 0;

    //Gamepiece funktionalitet
    virtual bool place_gamepiece(Gamepiece& gamepiece) = 0;

    //Poäng funktionalitet
    virtual void give_points() = 0;
    
protected:
    Field* connected_neighbor = nullptr;
    Field* connected_opposite = nullptr;
    Field* connected_left = nullptr;
    Field* connected_right = nullptr;

    int number_of_connected_fields = 1;
    int number_of_gamepieces_player1 = 0;
    int number_of_gamepieces_player2 = 0;

    bool whole_closed = false;
    bool bool_connected = false;
    
};

#endif 