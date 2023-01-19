#ifndef PLAYER_H 
#define PLAYER_H

#include <string>
#include <vector>
#include <map>
#include <cctype>

#include <memory>

#include "./charts.h"
#include "./ships.h"

class Player{

private:
    //private variables
    std::string name;
    AttackC a_grid;
    DefenceC d_grid;
    std::map<std::string, std::shared_ptr<Ship>> ships;
    
    //private functions
    bool validPosition(std::string tile, std::string toTile);
    bool obstacles(std::string stern, std::string bow, std::shared_ptr<Ship> ship);
    char addToChart(std::string tile, char id);    
    bool move(std::string stern, std::string bow, std::shared_ptr<Ship> ship);
    bool heal(std::shared_ptr<Ship> ship);
    bool scan(std::shared_ptr<Ship> ship, Player opposite);
    
protected:
    //protected vari
    static int nextId;

public:
    //constructor
    Player(std::string name = "bot" + std::to_string(nextId++));
    Player(DefenceC d_grid, std::string name = "bot" + std::to_string(nextId++));

    //copy constructor
    Player(const Player& refObject);

    //destructor
    ~Player(){};

    //public functions
    bool addShip(std::string stern, std::string bow, Ship& ship);
    bool removeShip(std::shared_ptr<Ship> ship);
    bool shot(std::shared_ptr<Ship> bship, std::string tile, Player &opposite);
    bool move_heal(std::shared_ptr<Ship> sship, std::string tile);
    bool move_scan(std::shared_ptr<Ship> eship, std::string tile, Player &opposite);

    //getter
    std::string getUsername();
    AttackC getAttackGrid();
    DefenceC getDefenceGrid();
    std::map<std::string, std::shared_ptr<Ship>> shipLegend();
    std::shared_ptr<Ship> getShip(std::string tile);
    std::string getShipCenter(std::string ship_tile);

    //setter
    std::string setUsername(std::string username = std::to_string(++nextId));
};

std::ostream &operator<<(std::ostream &os, Player &player);

#endif
