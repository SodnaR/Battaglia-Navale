#ifndef PLAYER_H 
#define PLAYER_H

#include <string>
#include <vector>
#include <map>

#include "./charts.h"
#include "./ships.h"

class Player{

private:
    AttackC a_grid;
    DefenceC d_grid;
    std::map<std::string, Ship*> ships;
    
    bool validPosition(std::string tile, std::string toTile);
    bool obstacles(std::string stern, std::string bow, Ship* ship);
    char addToChart(std::string tile, char id);
    
    bool move(std::string stern, std::string bow, Ship* ship);
    bool heal(Ship* ship);
    
public:
    //constructor
    Player();
    Player(DefenceC d_grid);

    //copy constructor
    Player(const Player& refObject);

    Ship addShip(std::string stern, std::string bow, Ship& ship);
    Ship addShip(int stern[], int bow[], Ship& ship);

    bool shot(Ship* bship, std::string tile, Player opposite);
    bool move_heal(Ship* sship, std::string tile);

    //getter
    AttackC getAttackGrid();
    DefenceC getDefenceGrid();
    std::map<std::string, Ship*> shipLegend();
    Ship* getShip(std::string tile);
    std::string getShipCenter(std::string ship_tile);
};

std::ostream &operator<<(std::ostream &os, Player &player);

#endif
