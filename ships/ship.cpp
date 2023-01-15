#include "../headers/ships.h"

Ship::Ship(int dim, std::string stern, std::string bow, char id){
    this->dim = dim;
    this->plate = dim;
    this->orient = findOrientation(stern, bow);
    this->center = locateCenter(stern, bow);
    this->id = id;
}

Ship::Ship(int dim, int stern[], int bow[], char id){
    this->dim = dim;
    this->plate = dim;
    this->orient = findOrientation(stern, bow);
    this->center = locateCenter(stern, bow);
    this->id = id;
}

int Ship::findOrientation(std::string stern, std::string bow){
    if(stern[0] == bow[0]) return 1;
    return 0;
}

int Ship::findOrientation(int stern[], int bow[]){
    if(stern[0] == bow[0]) return 1;
    return 0;
}

std::string Ship::locateCenter(std::string stern, std::string bow){
    if(stern.length() > 3 || bow.length() > 3) return "invalid";

    std::string out;
    int y;
    if(stern.length()==3){
        y = std::stoi(stern.substr(1, 2)); 
    } else {
        y = std::stoi(stern.substr(1, 1)); 
    }
    if(orient){
        int y2;
        if(bow.length()==3){
            y2 = std::stoi(bow.substr(1, 2));
        } else {
            y2 = std::stoi(bow.substr(1, 1));
        }
        out = (1, stern[0]);
        out += std::to_string((y + y2)/2);
    } else {
        char x1 = stern[0], x2 = bow[0];
        out = (1, ((x1 + x2)/2));
        out += std::to_string(y);
    }
    return out;
}

std::string Ship::locateCenter(int stern[], int bow[]){
    std::string start(1, 'a'+stern[0]), end(1, 'a'+bow[0]);
    start += std::to_string((stern[1] + 1));
    end += std::to_string((bow[1] + 1));
    return locateCenter(start, end);
}

int Ship::hit(){
    return --plate; 
}

int Ship::heal(){
    if(plate != 0)    return plate = dim;
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

std::string Ship::getCenter(){
    return center;
}

char Ship::getId(){
    return id;
}

std::string Ship::moved(std::string center){
    return this->center = center;
}


std::ostream &operator<<(std::ostream &os, Ship &ship){
    std::string out = "dimensione: " + std::to_string(ship.getDimension());
    out += " con armatura attuale: " + std::to_string(ship.getArmor());
    os<<out;
    return os;
}

bool operator==(Ship ship1, Ship ship2){
    if(ship1.getId() != ship2.getId()) return false;
    if(ship1.getArmor() != ship2.getArmor()) return false;
    if(ship1.getCenter() != ship2.getCenter()) return false;
    if(ship1.getDimension() != ship2.getDimension()) return false;
    if(ship1.getOrientation() != ship2.getOrientation()) return false;
    return true;
}

bool operator!=(Ship ship1, Ship ship2){
    return !operator==;
}
