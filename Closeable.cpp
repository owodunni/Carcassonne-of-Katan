/* 
 * File:   Closeable.cpp
 * Author: Joel, Anna och Milton
 * 
 * Inkluderingsfil för den abstrakta superklassen Closeable (förslutningsbar). 
 * Innehåller det mesta av logiken för att kolla hur många fält som är 
 * sammankopplade, hur många gamepieces som är utplacerade mm.
 * 
 */

#include "Closeable.h"

using namespace std;

//------------------------------Field funktionalitet--------------------------------

void Closeable::set_number_of_connected_fields(int setNumber) {
    number_of_connected_fields = setNumber;
}

void Closeable::connect_field(Field* field, string direction) {
    if (direction == "opposite") {
        connected_opposite = field;
        closeable_number = connected_opposite->get_closeable_number();
        closeable_gamepiece = connected_opposite->get_closeable_gamepiece();
        closeable_closed = connected_opposite->get_closeable_closed();
    } else if (direction == "right") {
        connected_right = field;
        closeable_number = connected_right->get_closeable_number();
        closeable_gamepiece = connected_right->get_closeable_gamepiece();
        closeable_closed = connected_right->get_closeable_closed();
    } else if (direction == "left") {
        connected_left = field;
        closeable_number = connected_left->get_closeable_number();
        closeable_gamepiece = connected_left->get_closeable_gamepiece();
        closeable_closed = connected_left->get_closeable_closed();
    }
}

void Closeable::increase_number_of_connected_fields() {
    if (number_of_connected_fields == 1) {
        number_of_connected_fields =
                number_of_connected_fields + connected_neighbor->get_number_of_connected_fields();
        set_closeable_number(connected_neighbor->get_closeable_number());
        connected_neighbor->single_set_number_of_connected_fields(1);
    } else {
        double_set_number_of_connected_fields();
    }
}

void Closeable::single_set_number_of_connected_fields(int addNumber) {
    number_of_connected_fields = number_of_connected_fields + addNumber;
    if ((connected_neighbor != nullptr) &&
            (number_of_connected_fields != connected_neighbor->get_number_of_connected_fields())) {
        connected_neighbor->single_set_number_of_connected_fields(addNumber);
    }
    if ((connected_opposite != nullptr) &&
            (number_of_connected_fields != connected_opposite->get_number_of_connected_fields())) {
        connected_opposite->single_set_number_of_connected_fields(addNumber);
    }
    if ((connected_left != nullptr) &&
            (number_of_connected_fields != connected_left->get_number_of_connected_fields())) {
        connected_left->single_set_number_of_connected_fields(addNumber);
    }
    if ((connected_right != nullptr) &&
            (number_of_connected_fields != connected_right->get_number_of_connected_fields())) {
        connected_right->single_set_number_of_connected_fields(addNumber);
    }
}

void Closeable::double_set_number_of_connected_fields() {
    if ((connected_neighbor != nullptr) &&
            (get_connected_field_on_card()->get_neighborField() != nullptr)) {
        if (same_closeable_bool(get_connected_field_on_card()->get_neighborField())) {
            same_closeable_set_number_of_connected_fields();
        } else {
            different_closeable_set_number_of_connected_fields();
        }
    } else {
        number_of_connected_fields = number_of_connected_fields + connected_neighbor->get_number_of_connected_fields();
        get_connected_field_on_card()->set_number_of_connected_fields(number_of_connected_fields);
        set_closeable_number(connected_neighbor->get_closeable_number());
        get_connected_field_on_card()->set_closeable_number(closeable_number);
        connected_neighbor->single_set_number_of_connected_fields(2);
    }
}

int Closeable::get_number_of_connected_fields() const {
    return number_of_connected_fields;
}

Field* Closeable::get_connected_field_on_card() const {
    if (connected_opposite != nullptr) {
        return connected_opposite;
    }
    if (connected_left != nullptr) {
        return connected_left;
    }
    if (connected_right != nullptr) {
        return connected_right;
    } else {
        return nullptr;
    }
}

Field* Closeable::get_neighborField() const {
    return connected_neighbor;
}

bool Closeable::same_closeable_bool(Field* secondField) const {
    return (connected_neighbor->get_closeable_number() == secondField->get_closeable_number());
}

void Closeable::same_closeable_set_number_of_connected_fields() {
    if (closeable_number != connected_neighbor->get_closeable_number()) {
        number_of_connected_fields = number_of_connected_fields + connected_neighbor->get_number_of_connected_fields();
        closeable_number = connected_neighbor->get_closeable_number();
        get_connected_field_on_card()->set_closeable_number(closeable_number);
        connected_neighbor->equal_number_of_connected_fields(number_of_connected_fields);
    }
}

void Closeable::equal_number_of_connected_fields(int setNumber) {
    number_of_connected_fields = setNumber;
    if ((connected_neighbor != nullptr) &&
            (number_of_connected_fields != connected_neighbor->get_number_of_connected_fields())) {
        connected_neighbor->equal_number_of_connected_fields(setNumber);
    }
    if ((connected_opposite != nullptr) &&
            (number_of_connected_fields != connected_opposite->get_number_of_connected_fields())) {
        connected_opposite->equal_number_of_connected_fields(setNumber);
    }
    if ((connected_left != nullptr) &&
            (number_of_connected_fields != connected_left->get_number_of_connected_fields())) {
        connected_left->equal_number_of_connected_fields(setNumber);
    }
    if ((connected_right != nullptr) &&
            (number_of_connected_fields != connected_right->get_number_of_connected_fields())) {
        connected_right->equal_number_of_connected_fields(setNumber);
    }
}

int Closeable::get_closeable_number() const {
    return closeable_number;
}

void Closeable::set_closeable_number(int setNumber) {
    closeable_number = setNumber;
}

void Closeable::different_closeable_set_number_of_connected_fields() {
    number_of_connected_fields =
            connected_neighbor->get_number_of_connected_fields() +
            get_connected_field_on_card()->get_neighborField()->get_number_of_connected_fields();
    equal_number_of_connected_fields(number_of_connected_fields);
    set_closeable_number(connected_neighbor->get_closeable_number());
    equal_closeable_number(closeable_number);
}

void Closeable::equal_closeable_number(int setNumber) {
    closeable_number = setNumber;
    if ((connected_neighbor != nullptr) &&
            (closeable_number != connected_neighbor->get_closeable_number())) {
        connected_neighbor->equal_closeable_number(setNumber);
    }
    if ((connected_opposite != nullptr) &&
            (closeable_number != connected_opposite->get_closeable_number())) {
        connected_opposite->equal_closeable_number(setNumber);
    }
    if ((connected_left != nullptr) &&
            (closeable_number != connected_left->get_closeable_number())) {
        connected_left->equal_closeable_number(setNumber);
    }
    if ((connected_right != nullptr) &&
            (closeable_number != connected_right->get_closeable_number())) {
        connected_right->equal_closeable_number(setNumber);
    }
}

void Closeable::connect_neighbor(Field* neighbor) {
    connected_neighbor = neighbor;
    bool_connected = true;
    if (!(connected_neighbor->get_bool_connected())) {
        connected_neighbor->connect_neighbor(this);
    }
}

bool Closeable::get_bool_connected() const {
    return bool_connected;
}

void Closeable::update_number_of_gamepieces() {
    if (closeable_gamepiece != connected_neighbor->get_closeable_gamepiece()) {
        if (number_of_connected_fields == 1) {
            set_number_of_gamepieces();
            set_closeable_gamepiece();
        } else if ((number_of_connected_fields == 2) &&
                (get_connected_field_on_card()->get_neighborField() == nullptr)) {
            set_number_of_gamepieces();
            set_closeable_gamepiece();
            get_connected_field_on_card()->set_number_of_gamepieces();
            get_connected_field_on_card()->set_closeable_gamepiece();
        } else if ((number_of_connected_fields == 2) &&
                (get_connected_field_on_card()->get_neighborField() != nullptr) &&
                (get_connected_field_on_card()->get_neighborField()->get_closeable_gamepiece() ==
                connected_neighbor->get_closeable_gamepiece())) {
            set_number_of_gamepieces();
            set_closeable_gamepiece();
            get_connected_field_on_card()->set_number_of_gamepieces();
            get_connected_field_on_card()->set_closeable_gamepiece();
        } else {
            double_update_number_of_gamepieces();
        }
    }
}

int Closeable::get_number_of_gamepieces(int player) const {
    if (player == 1) {
        return number_of_gamepieces_player1;
    } else {
        return number_of_gamepieces_player2;
    }
}

void Closeable::set_number_of_gamepieces() {
    if (connected_neighbor != nullptr) {
        number_of_gamepieces_player1 = connected_neighbor->get_number_of_gamepieces(1);
        number_of_gamepieces_player2 = connected_neighbor->get_number_of_gamepieces(2);
    } else if (got_neighbor_on_card()) {
        number_of_gamepieces_player1 = get_connected_field_on_card()->get_number_of_gamepieces(1);
        number_of_gamepieces_player2 = get_connected_field_on_card()->get_number_of_gamepieces(2);
    }
}

void Closeable::set_number_of_gamepieces(int number1, int number2) {
    number_of_gamepieces_player1 = number1;
    number_of_gamepieces_player2 = number2;
}

void Closeable::set_closeable_gamepiece() {
    if (connected_neighbor != nullptr) {
        closeable_gamepiece = connected_neighbor->get_closeable_gamepiece();
    } else {
        closeable_gamepiece = get_connected_field_on_card()->get_closeable_gamepiece();
    }
}

void Closeable::set_closeable_gamepiece(int number) {
    closeable_gamepiece = number;
}

int Closeable::get_closeable_gamepiece() const {
    return closeable_gamepiece;
}

void Closeable::double_update_number_of_gamepieces() {
    number_of_gamepieces_player1 = connected_neighbor->get_number_of_gamepieces(1) +
            get_connected_field_on_card()->get_neighborField()->get_number_of_gamepieces(1);
    number_of_gamepieces_player2 = connected_neighbor->get_number_of_gamepieces(2) +
            get_connected_field_on_card()->get_neighborField()->get_number_of_gamepieces(2);
    connected_neighbor->equal_number_of_gamepieces(number_of_gamepieces_player1, number_of_gamepieces_player2, closeable_gamepiece);
    get_connected_field_on_card()->
            equal_number_of_gamepieces(number_of_gamepieces_player1, number_of_gamepieces_player2, closeable_gamepiece);
}

void Closeable::equal_number_of_gamepieces(int player1, int player2, int closeable_counter) {
    number_of_gamepieces_player1 = player1;
    number_of_gamepieces_player2 = player2;
    closeable_gamepiece = closeable_counter;
    if ((connected_neighbor != nullptr) &&
            (closeable_gamepiece != connected_neighbor->get_closeable_gamepiece())) {
        connected_neighbor->
                equal_number_of_gamepieces(number_of_gamepieces_player1, number_of_gamepieces_player2, closeable_gamepiece);
    }
    if ((connected_opposite != nullptr) &&
            (closeable_gamepiece != connected_opposite->get_closeable_gamepiece())) {
        connected_opposite->
                equal_number_of_gamepieces(number_of_gamepieces_player1, number_of_gamepieces_player2, closeable_gamepiece);
    }
    if ((connected_left != nullptr) &&
            (closeable_gamepiece != connected_left->get_closeable_gamepiece())) {
        connected_left->
                equal_number_of_gamepieces(number_of_gamepieces_player1, number_of_gamepieces_player2, closeable_gamepiece);
    }
    if ((connected_right != nullptr) &&
            (closeable_gamepiece != connected_right->get_closeable_gamepiece())) {
        connected_right->
                equal_number_of_gamepieces(number_of_gamepieces_player1, number_of_gamepieces_player2, closeable_gamepiece);
    }
}

void Closeable::add_gamepiece_player1() {
    closeable_gamepiece = ++counter;
    if (got_neighbor_on_card()) {
        get_connected_field_on_card()->equal_number_of_gamepieces(1, 0, closeable_gamepiece);
        equal_number_of_gamepieces(1, 0, closeable_gamepiece);
    } else {
        equal_number_of_gamepieces(1, 0, closeable_gamepiece);
    }
}

void Closeable::add_gamepiece_player2() {
    closeable_gamepiece = ++counter;
    if (got_neighbor_on_card()) {
        get_connected_field_on_card()->equal_number_of_gamepieces(0, 1, closeable_gamepiece);
        equal_number_of_gamepieces(0, 1, closeable_gamepiece);
    } else {
        equal_number_of_gamepieces(0, 1, closeable_gamepiece);
    }
}

bool Closeable::got_gamepieces() const {
    bool neighbor = false;
    bool otherNeighbor = false;
    if ((connected_neighbor->get_number_of_gamepieces(1) != 0) ||
            (connected_neighbor->get_number_of_gamepieces(2) != 0)) {
        neighbor = true;
    }
    if ((get_connected_field_on_card()->get_neighborField()->get_number_of_gamepieces(1) != 0) ||
            (get_connected_field_on_card()->get_neighborField()->get_number_of_gamepieces(1) != 0)) {
        otherNeighbor = true;
    }
    if (neighbor || otherNeighbor) {
        return true;
    }
}

bool Closeable::allowed_to_put_gamepiece() const {
    if (got_gamepieces()) {
        return false;
    } else {
        return true;
    }
}

bool Closeable::is_closed() const {
    return whole_closed;
}

void Closeable::set_closed() {
    if ((number_of_connected_fields % 2 == 0) &&
            (got_neighbor_on_card())) {
        if (get_connected_field_on_card()->get_neighborField() != nullptr) {
            if (connected_neighbor->get_closeable_closed() !=
                    get_connected_field_on_card()->get_neighborField()->get_closeable_closed()) {
                both_sides_closed();
            } else {
                set_whole_closed();
                closeable_closed = connected_neighbor->get_closeable_closed();
                get_connected_field_on_card()->set_closeable_closed(closeable_closed);
            }
        } else {
            closeable_closed = connected_neighbor->get_closeable_closed();
            get_connected_field_on_card()->set_closeable_closed(closeable_closed);
        }
    } else if ((number_of_connected_fields % 2 == 0) &&
            (!(got_neighbor_on_card()))) {
        set_whole_closed();
        closeable_closed = connected_neighbor->get_closeable_closed();
    } else {
        closeable_closed = connected_neighbor->get_closeable_closed();
        if (got_neighbor_on_card()) {
            get_connected_field_on_card()->set_closeable_closed(closeable_closed);
        }
    }
}

void Closeable::both_sides_closed() {
    if (connected_neighbor->got_neighbor_on_card()) {
        if (connected_neighbor->get_connected_field_on_card()->get_neighborField() != nullptr) {
            connected_neighbor->get_connected_field_on_card()->both_sides_closed();
        } else {
            set_whole_closeable_closed();
            whole_closed = false;
        }
    } else {
        set_whole_closed();
    }
}

void Closeable::set_whole_closeable_closed() {
    if (get_connected_field_on_card()->get_neighborField() != nullptr) {
        get_connected_field_on_card()->set_closeable_closed(closeable_closed);
        get_connected_field_on_card()->get_neighborField()->set_closeable_closed(closeable_closed);
        get_connected_field_on_card()->get_neighborField()->set_whole_closeable_closed();
    } else {
        get_connected_field_on_card()->set_closeable_closed(closeable_closed);
    }
}

bool Closeable::got_neighbor_on_card() const {
    return ((connected_opposite != nullptr) || (connected_right != nullptr) || (connected_left != nullptr));
}

int Closeable::get_closeable_closed() const {
    return closeable_closed;
}

void Closeable::set_whole_closed() {
    whole_closed = true;
     if ((connected_neighbor != nullptr) && (!(connected_neighbor->get_whole_closed()))) {
         connected_neighbor->set_whole_closed();
     }
     if ((connected_opposite != nullptr) && (!(connected_opposite->get_whole_closed()))) {
         connected_opposite->set_whole_closed();
     }
     if ((connected_left != nullptr) && (!(connected_left->get_whole_closed()))) {
         connected_left->set_whole_closed();
     }
     if ((connected_right != nullptr) && (!(connected_right->get_whole_closed()))) {
         connected_right->set_whole_closed();
     }
}

void Closeable::clear_gamepieces() {
    closeable_gamepiece = ++counter;
    if (got_neighbor_on_card()) {
        get_connected_field_on_card()->equal_number_of_gamepieces(0, 0, closeable_gamepiece);
        equal_number_of_gamepieces(0, 0, closeable_gamepiece);
    } else {
        equal_number_of_gamepieces(0, 0, closeable_gamepiece);
    }
}

bool Closeable::get_whole_closed() const {
    return whole_closed;
}

void Closeable::set_closeable_closed(int number) {
    closeable_closed = number;
}

//------------------------------Gamepiece funktionalitet--------------------------------

/*
 * place_gamepiece 
 */
bool Closeable::place_gamepiece(Gamepiece& gamepiece) {
    if ((number_of_gamepieces_player1 == 0) && (number_of_gamepieces_player2 == 0)) {
        if (this->is_closed())
            return false;
        //else, ska placera ut
        if (gamepiece.get_player()->get_index() == 1) {
            this->add_gamepiece_player1();
            return true;
        } else if (gamepiece.get_player()->get_index() == -1) {
            cout << "De e FUKKAT! //Oskar Nordmark" << endl;
            return false;
        } else {
            this->add_gamepiece_player2();
            return true;
        }
    }
    return false; //gick ej att placera ut
}

//------------------------------Poäng funktionalitet--------------------------------

/*
 * give_points
 */
void Closeable::give_points() {
    if (number_of_gamepieces_player1 > number_of_gamepieces_player2) {
        if (this->is_closed())
            global_player1->increase_score(number_of_connected_fields);
        else
            global_player1->increase_score(number_of_gamepieces_player1);

    } else if (number_of_gamepieces_player1 < number_of_gamepieces_player2) {
        if (this->is_closed())
            global_player2->increase_score(number_of_connected_fields);
        else {
            global_player2->increase_score(number_of_gamepieces_player2);
        }
    }
    global_player1->increase_gamepieces(number_of_gamepieces_player1);
    global_player2->increase_gamepieces(number_of_gamepieces_player2);
    this->clear_gamepieces();
}
