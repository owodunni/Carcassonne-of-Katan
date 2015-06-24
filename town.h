/* 
 * File:   town.h
 * Author: Alexander
 * 
 * Underklass till field. Representerar alla stad-fält. 
 *
 */

#ifndef TOWN_H
#define TOWN_H
#include "Field.h"
#include "Closeable.h"
#include "Player.h"
#include "Gamepiece.h"

using namespace std;

class Town : public Closeable {
public:
    Town() = default; // konstruktor
    ~Town() = default; //destruktor
    Town(const Town&) = default; //Kopieringskonstruktor
    Town(Town&&) = default; // move-kopieringskonstruktor
    Town& operator=(const Town&) = default; //tilldelningsoperator
    Town& operator=(Town&&) = default; //move-tilldelningsoperator
    Town* clone();

    bool is_compatible(Field*)const;


};
#endif