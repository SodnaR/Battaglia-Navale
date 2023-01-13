#include "../headers/Player.h"

Player::Player(){
    this->a_grid = AttackC();
    this->d_grid = DefenceC();
}

Player::Player(DefenceC d_grid){
    this->a_grid = AttackC(d_grid.getMapSize(), d_grid.shipsCounter());
    this->d_grid = DefenceC(d_grid);
}

Player::Player(const Player& refObject){
    this->a_grid = refObject.a_grid;
    this->d_grid = refObject.d_grid;
    this->ships = refObject.ships;
}

bool Player::validPosition(std::string tile, std::string toTile){
    try{
        if(tile.length() < 2 || tile.length() > 3) throw(tile);
        if(toTile.length() < 2 || toTile.length() > 3) throw(tile);
        if(!d_grid.valid(tile) || !d_grid.valid(toTile)) throw(tile);
        if(tile[0] != toTile[0] && tile.substr(1) != toTile.substr(1)) throw(tile);
    } catch(std::string invalid){
        return false;
    }
    return true;
}

bool Player::obstacles(std::string stern, std::string bow, Ship ship){
    std::string start = stern, end = bow;
    while(start != end){
        if(d_grid.getTile(start) != ' '){
            return true;
        }
        if(ship.getOrientation()){
            int y;
            if(start.length()==3){
                y = std::stoi(start.substr(1, 2));
                y++;
                start.replace(1, 2, std::to_string(y));
            } else {
                y = std::stoi(start.substr(1, 1));
                y++;
                start.replace(1, 1, std::to_string(y));
            }
        } else {
            start[0]++;
        }
    }
    return false;
}

char Player::addToChart(std::string tile, char id){
    d_grid.setTile(tile, id);
    return id;
}

Ship Player::addShip(std::string stern, std::string bow, Ship& ship){
    int y;
    if(!validPosition(stern, bow)) return ship;
    if(obstacles(stern, bow, ship)) return ship;
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
            d_grid.setTile(tile, ship.getId());
        }    
    } else {
        char x1 = stern[0], x2 = bow[0];
        for (char i = x1; i <= x2; i++){
            if(i=='j') i+=2;
            if(i=='w') i+=3;
            std::string tile(1, i);
            tile += std::to_string(y);
            ships.insert(std::pair<std::string, Ship>(tile, ship));
            d_grid.setTile(tile, ship.getId());
        }
    }
    return ship;
}

#include <iostream>

bool Player::shot(Ship bship, std::string tile, Player opposite){
    if(opposite.getDefenceGrid().getTile(tile) != ' '){
        a_grid.setTile(tile, 'x');
        opposite.getShip(tile).hit();
        std::cout<<"Armor abbassata a: "<<opposite.getShip(tile).getArmor()<<std::endl;
        Ship dummy = opposite.getShip(tile);
        if(dummy.getArmor() == 0){
            std::map<std::string, Ship>::iterator it = opposite.shipLegend().begin();
            while (it != opposite.shipLegend().end()){
                if(it->second == dummy){
                    a_grid.setTile(it->first, 'X');
                }
                it++;
            }
        }
    } else {
        a_grid.setTile(tile, 'O');
    }
    return true;
}

DefenceC Player::getDefenceGrid(){
    return d_grid;
}

AttackC Player::getAttackGrid(){
    return a_grid;
}

std::map<std::string, Ship> Player::shipLegend(){
    return ships;
}

Ship Player::getShip(std::string tile){
    return ships[tile];
}

std::string Player::getShipCenter(std::string ship_tile){
    return ships[ship_tile].getCenter();
}

std::ostream &operator<<(std::ostream &os, Player &player){
    std::string out = "La tua plancia:";
    out +=  player.getDefenceGrid().show_coordinate();
    out += "\nLa plancia nemica:";
    out += player.getAttackGrid().show_coordinate();
    os<<out;
    return os;
}