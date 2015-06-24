/* 
 * File:   town.cc
 * Author: Alexander och Milton
 * 
 * Underklass till field. Representerar alla stad-fält. 
 *
 */

#include "town.h"
/*
 * is_compatible 
 */
bool Town::is_compatible(Field* other)const {
    Town* temp = dynamic_cast<Town*> (other);
    return (temp != nullptr);
}

Town* Town::clone(){
    Town* tmp = new Town;
    tmp->bool_connected = bool_connected; 
    tmp->connected_left = connected_left;
    tmp->connected_right = connected_right;
    tmp->connected_opposite = connected_opposite;
    tmp->connected_neighbor = connected_neighbor;
    tmp->number_of_connected_fields = number_of_connected_fields;
    tmp->closeable_closed = closeable_closed; 
    tmp->closeable_gamepiece = closeable_gamepiece; 
    tmp->closeable_number = closeable_number; 
    tmp->number_of_gamepieces_player1 = number_of_gamepieces_player1; 
    tmp->number_of_gamepieces_player2 = number_of_gamepieces_player2; 
    tmp->whole_closed = whole_closed;
    return tmp;
}