/* 
 * File:   Desert.cc
 * Author: Alexander och Milton
 * 
 * Underklass till field. Representerar alla gräs-fält. 
 *
 */

#include "Desert.h"
using namespace std;

/*
 * is_compatible 
 */
bool Desert::is_compatible(Field* other) const{
    Desert* temp = dynamic_cast<Desert*> (other);
    return (temp != nullptr);
}

/*
 *clone
 */
Desert* Desert::clone(){
    Desert* new_Desert = new Desert;
    return new_Desert;
}

