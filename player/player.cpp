#include "../headers/Player.h"

Player::Player(Chart map){
    this->a_grid = AttackC(map);
    this->d_grid = DefenceC(map);
}

Player::Player(DefenceC d_grid){
    this->a_grid = AttackC(d_grid.getMapSize(), d_grid.shipsCounter());
    this->d_grid = DefenceC(d_grid);
}
Ship* Player::addShip(std::string stern, std::string bow, Ship* ship){
    int y;
    if(stern.length()==3){
        y = std::stoi(stern.substr(2, 2)) - 1; 
    } else {
        y = std::stoi(stern.substr(2, 1)) - 1; 
    }
    if(ship->getOrientation()){
        int y2;
        if(bow.length()==3){
            y2 = std::stoi(bow.substr(2, 2)) - 1;
        } else {
            y2 = std::stoi(bow.substr(2, 1)) - 1;
        }
        for (int i = y; i < y2; i++){
            std::string tile = std::to_string(stern[0]);
            tile += std::to_string(i);
            ships[tile] = ship;
        }    
    } else {
        char x1 = stern[0], x2 = bow[0];
        for (char i = x1; i < x2; i++){
            if(i=='j') i+=2;
            if(i=='w') i+=3;
            std::string tile = std::to_string(i);
            tile += std::to_string(y);
            ships[tile] = ship;
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
