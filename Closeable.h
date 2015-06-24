/* 
 * File:   Closeable.h
 * Author: Joel och Anna
 * 
 * Abstrakt superklass för stad och väg.
 *
 */

#ifndef CLOSEABLE_H
#define	CLOSEABLE_H
#include <iostream>
#include <string>
#include "Field.h"
#include "global.h"


using namespace std;

class Closeable : public Field {
public:

    Closeable() : closeable_number(++counter), closeable_gamepiece(++counter), closeable_closed(++counter){
    } //Konstruktor
    ~Closeable() = default; //Destruktor
    Closeable(const Closeable&) = default;
    Closeable(Closeable&&) = default; //Move-kopiering
    Closeable& operator=(const Closeable&) = default; //Tilldelningskonstruktor
    Closeable& operator=(Closeable&&) = default; // Move-tilldelning


    //Field funktionalitet
    void set_number_of_connected_fields(int);
    void connect_field(Field*, string);
    void increase_number_of_connected_fields();
    void single_set_number_of_connected_fields(int);
    void double_set_number_of_connected_fields();
    int get_number_of_connected_fields() const;
    Field* get_connected_field_on_card() const;
    Field* get_neighborField() const;
    bool same_closeable_bool(Field*) const;
    void same_closeable_set_number_of_connected_fields();
    void equal_number_of_connected_fields(int);
    int get_closeable_number() const;
    void set_closeable_number(int);
    void different_closeable_set_number_of_connected_fields();
    void equal_closeable_number(int);
    void connect_neighbor(Field*);
    bool get_bool_connected() const;
    void update_number_of_gamepieces();
    int get_number_of_gamepieces(int) const;
    void set_number_of_gamepieces();
    void set_number_of_gamepieces(int, int);
    void set_closeable_gamepiece();
    void set_closeable_gamepiece(int);
    int get_closeable_gamepiece() const;
    void double_update_number_of_gamepieces();
    void equal_number_of_gamepieces(int, int, int);
    void add_gamepiece_player1();
    void add_gamepiece_player2();
    bool got_gamepieces() const;
    bool allowed_to_put_gamepiece() const;
    bool is_closed() const;
    void set_closed();
    void both_sides_closed();
    void set_whole_closeable_closed();
    bool got_neighbor_on_card() const;
    int get_closeable_closed() const;
    void set_whole_closed();
    void clear_gamepieces();
    bool get_whole_closed() const;
    void set_closeable_closed(int);

    //Gamepiece funktionalitet
    bool place_gamepiece(Gamepiece& gamepiece);

    //Poäng funktionalitet
    void give_points();

protected:
    int closeable_number;
    int closeable_gamepiece;
    int closeable_closed;

};


#endif  /* CLOSEABLE_H */


