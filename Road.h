/* 
 * File:   Road.h
 * Author: Alexander
 * 
 * Underklass till field. Representerar alla väg-fält. 
 *
 */

#ifndef ROAD_H
#define ROAD_H
#include "Closeable.h"
#include "Player.h"
#include "Gamepiece.h"

class Road : public Closeable {
public:
    Road() = default; // konstruktor
    ~Road() = default; //destruktor
    Road(const Road&) = default; //Kopieringskonstruktor
    Road(Road&&) = default; // move-kopieringskonstruktor
    Road& operator=(const Road&) = default; //tilldelningsoperator
    Road& operator=(Road&&) = default; //move-tilldelningsoperator
    Road* clone();

    bool is_compatible(Field*)const;


};

#endif