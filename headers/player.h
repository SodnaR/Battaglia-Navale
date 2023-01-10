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
public:
    //constructor
    Player(Chart map);
    Player(DefenceC d_grid);

    //copy constructor
    Player(const Player& refObject);

    Ship* addShip(std::string stern, std::string bow, Ship* ship);
    Ship* addShip(int stern[], int bow[], Ship* ship);

    //getter
    std::map<std::string, Ship*> ShipLegend();
    AttackC getAttackGrid();
    DefenceC getDefenseGrid();


};

std::ostream &operator<<(std::ostream &os, Player &player);

#endif
