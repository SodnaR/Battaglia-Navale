#include "../headers/ships.h"

Ship::Ship(int dim, std::string stern, std::string bow, char id){
    this->dim = dim;
    this->plate = dim;
    this->orient = findOrientation(stern, bow);
    this->id = id;
    for (int i = 0; i < dim; i++)
    {
        shot.push_back(false);
    }
}

Ship::Ship(int dim, int stern[], int bow[], char id){
    this->dim = dim;
    this->plate = dim;
    this->orient = findOrientation(stern, bow);
    this->id = id;
    for (int i = 0; i < dim; i++)
    {
        shot.push_back(false);
    }
    
}

Ship::Ship(int dim, int orient, char id){
    this->dim = dim;
    this->plate = dim;
    this->orient = orient;
    this->id = id;
    for (int i = 0; i < dim; i++)
    {
        shot.push_back(false);
    }
    
}

int Ship::findOrientation(std::string stern, std::string bow){
    if(stern[0] == bow[0]) return 1;
    return 0;
}

int Ship::findOrientation(int stern[], int bow[]){
    if(stern[0] == bow[0]) return 1;
    return 0;
}

int Ship::hit(){
    --plate;
    return plate; 
}


int Ship::getDimension(){
    return dim;
}

int Ship::getArmor(){
    return plate;
}

int Ship::getOrientation(){
    return orient;
}

char Ship::getId(){
    return id;
}

std::ostream &operator<<(std::ostream &os, Ship &ship){
    std::string out = "dimensione: " + std::to_string(ship.getDimension());
    out += " con armatura attuale: " + std::to_string(ship.getArmor());
    os<<out;
    return os;
}
