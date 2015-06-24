/* 
 * File:   Desert.h
 * Author: Joel och Anna
 * 
 * Inkluderingsfil för gräs (kallas här för desert pga. utebliven funktionalitet 
 * i själva spelet). 
 *
 */

#ifndef DESERT_H
#define DESERT_H
#include "Field.h"
#include "Player.h"
#include "Gamepiece.h"

class Desert : public Field {
public:
    Desert() = default; // konstruktor
    ~Desert() = default; //destruktor
    Desert(const Desert&) = default; //Kopieringskonstruktor
    Desert(Desert&&) = default; // move-kopieringskonstruktor
    Desert& operator=(const Desert&) = default; //tilldelningsoperator
    Desert& operator=(Desert&&) = default; //move-tilldelningsoperator

    //Fancy funktionalitet
    bool is_compatible(Field*)const;
    Desert* clone();
    
    //Field funktionalitet
    void set_number_of_connected_fields(int) {}
    void connect_field(Field*, string) {}
    void increase_number_of_connected_fields() {}
    void single_set_number_of_connected_fields(int) {}
    void double_set_number_of_connected_fields() {}
    int get_number_of_connected_fields() const {return 0;}
    Field* get_connected_field_on_card() const {return nullptr;}
    Field* get_neighborField() const {return nullptr;}
    bool same_closeable_bool(Field*) const {return false;}
    void same_closeable_set_number_of_connected_fields() {}
    void equal_number_of_connected_fields(int) {}
    int get_closeable_number() const {return 0;}
    void set_closeable_number(int) {}
    void different_closeable_set_number_of_connected_fields() {}
    void equal_closeable_number(int) {}
    void connect_neighbor(Field*) {}
    bool get_bool_connected() const {return false;}
    void update_number_of_gamepieces() {}
    int get_number_of_gamepieces(int) const {return 0;}
    void set_number_of_gamepieces(){}
    void set_number_of_gamepieces(int, int){}
    void set_closeable_gamepiece(){}
    void set_closeable_gamepiece(int){}
    int get_closeable_gamepiece() const {return 0;}
    void double_update_number_of_gamepieces(){}
    void equal_number_of_gamepieces(int, int, int){}
    void add_gamepiece_player1(){}
    void add_gamepiece_player2() {}
    bool got_gamepieces() const {return false;}
    bool allowed_to_put_gamepiece() const {return false;}
    bool is_closed() const {return false;}
    void set_closed(){}
    void both_sides_closed(){}
    void set_whole_closeable_closed(){}
    bool got_neighbor_on_card() const {return false;}
    int get_closeable_closed() const {return 0;}
    void set_whole_closed(){}
    void clear_gamepieces(){}
    bool get_whole_closed() const {return false;}
    void set_closeable_closed(int){}
    
    //Gamepiece funktionalitet
    bool place_gamepiece(Gamepiece& gamepiece) {return false; }
    
    //Poäng funktionalitet
    void give_points() {}
    
};
#endif