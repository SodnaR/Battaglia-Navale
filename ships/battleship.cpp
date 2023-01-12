#include "../headers/ships.h"  

#include <bitset>
#include <iostream>
#include <stdexcept>
#include <string>

std::string Battleship::locateCenter(std::string stern, std::string bow){
    if(stern.length() > 3 || bow.length() > 3) return "invalid";

    std::string out;
    int y;
    if(stern.length()==3){
        y = std::stoi(stern.substr(1, 2)) - 1; 
    } else {
        y = std::stoi(stern.substr(1, 1)) - 1; 
    }
    if(orient){
        int y2;
        if(bow.length()==3){
            y2 = std::stoi(bow.substr(1, 2)) - 1;
        } else {
            y2 = std::stoi(bow.substr(1, 1)) - 1;
        }
        out = std::to_string(stern[0]);
        out += std::to_string((y + y2)/2);
    } else {
        char x1 = stern[0], x2 = bow[0];
        out = std::to_string((x1 + x2)/2);
        out += std::to_string(y);
    }
    return out;
}

char Battleship::getId(){
    return id;
}

std::string Battleship::getCenter(){
    return center;
}