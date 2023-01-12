#include "../headers/Player.h"

Player::Player(){
    this->a_grid = AttackC();
    this->d_grid = DefenceC();
}

Player::Player(DefenceC d_grid){
    this->a_grid = AttackC(d_grid.getMapSize(), d_grid.shipsCounter());
    this->d_grid = DefenceC(d_grid);
}

bool Player::validPosition(std::string tile){
    try{
        if(tile.length() < 2 || tile.length() > 3) throw(tile);
        if(!d_grid.valid(tile)) throw(tile);
    } catch(std::string invalid){
        return false;
    }
    return true;
}

char Player::addToChart(std::string tile, char id){
    d_grid.setTile(tile, id);
    return id;
}

#include <iostream>

Ship Player::addShip(std::string stern, std::string bow, Ship& ship){
    int y;
    if(!validPosition(stern) || !validPosition(bow)) return ship;
    if(stern.length()==3){
        y = std::stoi(stern.substr(1, 2)); 
    } else {
        y = std::stoi(stern.substr(1, 1)); 
    }
    if(ship.getOrientation()){
        int y2;
        if(bow.length()==3){
            y2 = std::stoi(bow.substr(1, 2));
        } else {
            y2 = std::stoi(bow.substr(1, 1));
        }
        for (int i = y; i <= y2; i++){
            std::string tile(1, stern[0]);
            tile += std::to_string(i);
            ships.insert(std::pair<std::string, Ship>(tile, ship));
        }    
    } else {
        char x1 = stern[0], x2 = bow[0];
        for (char i = x1; i <= x2; i++){
            if(i=='j') i+=2;
            if(i=='w') i+=3;
            std::string tile(1, i);
            tile += std::to_string(y);
            ships.insert(std::pair<std::string, Ship>(tile, ship));
        }
    }
    return ship;
}

DefenceC Player::getDefenseGrid(){
    return d_grid;
}

AttackC Player::getAttackGrid(){
    return a_grid;
}


std::map<std::string, Ship> Player::shipLegend(){
    return ships;
}
