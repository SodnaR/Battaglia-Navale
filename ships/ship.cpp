#include "../headers/ships.h"

Ship::Ship(int dim, int orient){
    this->dim = dim;
    this->plate = dim;
    this->orient = orient;
}

int Ship::getOrientation(){
    return orient;
}