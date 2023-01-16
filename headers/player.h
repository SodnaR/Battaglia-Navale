#ifndef PLAYER_H 
#define PLAYER_H

#include <string>
#include <vector>
#include <map>
#include <cctype>

#include "./charts.h"
#include "./ships.h"

class Player{

private:
    std::string name;
    AttackC a_grid;
    DefenceC d_grid;
    std::map<std::string, Ship*> ships;
    
    bool validPosition(std::string tile, std::string toTile);
    bool obstacles(std::string stern, std::string bow, Ship* ship);
    char addToChart(std::string tile, char id);
    
    bool move(std::string stern, std::string bow, Ship* ship);
    bool heal(Ship* ship);
    bool scan(Ship* ship, Player opposite);
    
protected:
    static int nextId;

public:
    //constructor
    Player(std::string name = std::to_string(++nextId));
    Player(DefenceC d_grid, std::string name = std::to_string(++nextId));

    //copy constructor
    Player(const Player& refObject);

    ~Player(){};

    bool addShip(std::string stern, std::string bow, Ship& ship);
    Ship addShip(int stern[], int bow[], Ship& ship);

    bool removeShip(Ship* ship);

    bool shot(Ship* bship, std::string tile, Player &opposite);
    bool move_heal(Ship* sship, std::string tile);
    bool move_scan(Ship* eship, std::string tile, Player &opposite);

    //getter
    std::string getUsername();
    AttackC getAttackGrid();
    DefenceC getDefenceGrid();
    std::map<std::string, Ship*> shipLegend();
    Ship* getShip(std::string tile);
    std::string getShipCenter(std::string ship_tile);

    //setter
    std::string setUsername(std::string username);
};

std::ostream &operator<<(std::ostream &os, Player &player);

#endif
