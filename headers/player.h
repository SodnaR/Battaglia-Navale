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
    std::map<std::string, Ship> ships;
    
    bool validPosition(std::string tile, std::string toTile);
    bool obstacles(std::string stern, std::string bow, Ship ship);
    char addToChart(std::string tile, char id);
    
public:
    //constructor
    Player();
    Player(DefenceC d_grid);

    //copy constructor
    Player(const Player& refObject);

    Ship addShip(std::string stern, std::string bow, Ship& ship);
    Ship addShip(int stern[], int bow[], Ship& ship);

    //getter
    std::map<std::string, Ship> shipLegend();
    AttackC getAttackGrid();
    DefenceC getDefenseGrid();

};

std::ostream &operator<<(std::ostream &os, Player &player);

#endif
