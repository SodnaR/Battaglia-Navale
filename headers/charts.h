#ifndef CHARTS_H
#define CHARTS_H

#include <string>
#include <vector>

class Chart{

private:
    int mapSize;
    std::vector<std::vector<char>> chart;

    int letterToCoordinate(std::string coordinate);

public:
    Chart(int mapSize = 12);
    Chart(const Chart & refObject, int mapSize = 12);

    bool valid(int col, int row);
    bool valid(std::string coordinate);
    std::string show();
    void clear();

    //Getter
    std::vector<std::vector<char>> getChart();
    char getTile(int col, int row);
    char getTile(std::string coordinate);
    int getMapSize();

    //Setter
    char setTile(int col, int row, char sub);
    char setTile(std::string tile, char sub);
};

std::ostream &operator<<(std::ostream &os, Chart &chart);
bool operator==(Chart map1, Chart map2);
bool operator!=(Chart map1, Chart map2);

class DefenseC : public Chart{
    
private:
    const char bShip = 'C', sShip = 'S', sub = 'E';
    int ships;

public:
    DefenseC(int mapSize, int ships = 6): Chart(mapSize){
        this->ships = ships;
    };
    DefenseC(const Chart & refObject, int ships = 6) : Chart(refObject){
        this->ships = ships;
    };

    int shipsCounter();
};

class AttackC : public Chart{

private:
    const char miss = 'O', hit = 'x', scan = 'Y';
    int ships; 

public:
    AttackC(int mapSize, int ships = 6): Chart(mapSize){
        this->ships = ships;
    };
    AttackC(const Chart & refObject, int ships = 6) : Chart(refObject){
        this->ships = ships;
    };

    int shipsCounter();
    attack(DefenseC enemyChart);
};

#endif