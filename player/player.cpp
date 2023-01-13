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

bool Player::obstacles(std::string stern, std::string bow, Ship* ship){
    std::string start = stern, end = bow;
    do{
        if(d_grid.getTile(start) != ' '){
            return true;
        }
        if(ship->getOrientation()){
            int y;
            if(start.length()==3){
                y = std::stoi(start.substr(1, 2));
                y++;
                start.replace(1, 2, std::to_string(y));
            } else {
                y = std::stoi(start.substr(1, 1));
                y++;
                start.replace(1, 2, std::to_string(y));
            }
        } else {
            start[0]++;
        }
    }while(start != end);
    return false;
}

char Player::addToChart(std::string tile, char id){
    d_grid.setTile(tile, id);
    return id;
}

bool Player::move(std::string stern, std::string bow, Ship* ship){
    std::string center = ship->getCenter();
    std::map<std::string, Ship*>::iterator it = ships.begin();
    while (it != ships.end()){
        if(it->second->getCenter() == ship->getCenter()){
            ships.erase(it->first);
            d_grid.setTile(it->first, ' ');
        }
        it++;
    }

    int y;
    if(stern.length()==3){
        y = std::stoi(stern.substr(1, 2)); 
    } else {
        y = std::stoi(stern.substr(1, 1)); 
    }
    if(ship->getOrientation()){
        int y2;
        if(bow.length()==3){
            y2 = std::stoi(bow.substr(1, 2));
        } else {
            y2 = std::stoi(bow.substr(1, 1));
        }
        for (int i = y; i <= y2; i++){
            std::string tile(1, stern[0]);
            tile += std::to_string(i); 
            ships.insert(std::pair<std::string, Ship*>(tile, ship));
            d_grid.setTile(tile, ship->getId());
        }    
    } else {
        char x1 = stern[0], x2 = bow[0];
        for (char i = x1; i <= x2; i++){
            std::string tile(1, i);
            tile += std::to_string(y);
            ships.insert(std::pair<std::string, Ship*>(tile, ship));
            d_grid.setTile(tile, ship->getId());
        }
    }
    ship->moved(ship->locateCenter(stern, bow));
    return true;
}

bool Player::heal(Ship* ship){
    std::string center = ship->getCenter();
    int x = center[0] - 'a', y;
    std::string tile;
    if(center.length() == 3){
        y = std::stoi(center.substr(1, 2)) - 1;
    } else{
        y = std::stoi(center.substr(1, 1)) - 1;
    }
    for (int i = (x > 0) ? (x - 1) : 0; i <= (x + 1); i++){
        for(int j = (y - 1); j <= (y + 1) && j < d_grid.getMapSize(); j++){
            tile = (1, ('a' + i));
            tile += std::to_string(j);
            if(ships.find(tile) != ships.end()){
                getShip(tile)->heal();
            }
        }
    }
    return true;
}

Ship Player::addShip(std::string stern, std::string bow, Ship& ship){
    Ship *shipPointer = &ship;
    int y;
    if(!validPosition(stern, bow)) return ship;
    if(obstacles(stern, bow, shipPointer)) return ship;
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
            ships.insert(std::pair<std::string, Ship*>(tile, shipPointer));
            d_grid.setTile(tile, ship.getId());
        }    
    } else {
        char x1 = stern[0], x2 = bow[0];
        for (char i = x1; i <= x2; i++){
            std::string tile(1, i);
            tile += std::to_string(y);
            ships.insert(std::pair<std::string, Ship*>(tile, shipPointer));
        }
    }
    return ship;
}

bool Player::shot(Ship* bship, std::string tile, Player opposite){
    if(ships.find(tile) == ships.end()) return false;
    if(opposite.getDefenceGrid().getTile(tile) != ' '){
        a_grid.setTile(tile, 'x');
        opposite.getShip(tile)->hit();
        Ship* dummy = opposite.getShip(tile);
        if(dummy->getArmor() == 0){
            std::map<std::string, Ship*>::iterator it = opposite.shipLegend().begin();
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

bool Player::move_heal(Ship* sship, std::string tile){
    if(ships.find(tile) == ships.end()) return false;
    if(sship->getId() != 'S') return false;

    std::string stern, bow;
    int coord;
    if(tile.length() == 3){
        coord = std::stoi(tile.substr(1, 2));
    } else {
        coord = std::stoi(tile.substr(1, 1));
    }
    if(sship->getOrientation()){
        stern = (1, tile[0]);
        stern += std::to_string(coord - 1);
        bow = (1, tile[0]);
        bow += std::to_string(coord + 1);
    } else {
        stern = (1, tile[0] - 1);
        stern += std::to_string(coord);
        bow = (1, tile[0] + 1);
        bow += std::to_string(coord);
    }
    if(!validPosition(stern, bow)) return false;
    if(obstacles(stern, bow, sship)) return false;

    if(!move(stern, bow, sship)) return false;
    if(!heal(sship)) return false;

    return true;
}

DefenceC Player::getDefenceGrid(){
    return d_grid;
}

AttackC Player::getAttackGrid(){
    return a_grid;
}

std::map<std::string, Ship*> Player::shipLegend(){
    return ships;
}

Ship* Player::getShip(std::string tile){
    return ships[tile];
}

std::string Player::getShipCenter(std::string ship_tile){
    return ships[ship_tile]->getCenter();
}

std::ostream &operator<<(std::ostream &os, Player &player){
    std::string out = "La tua plancia:";
    out +=  player.getDefenceGrid().show_coordinate();
    out += "\nLa plancia nemica:";
    out += player.getAttackGrid().show_coordinate();
    os<<out;
    return os;
}