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
    //constructor
    Chart(int mapSize = 12);

    //copy constructor
    Chart(const Chart& refObject);

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

class DefenceC : public Chart{
    
private:
    static const char bShip = 'C', sShip = 'S', sub = 'E';
    int ships;

public:
    //constructor
    DefenceC(int mapSize = 12, int ships = 6): Chart(mapSize){
        this->ships = ships;
    };

    //copy constructor
    DefenceC(const Chart& refObject, int ships = 6) : Chart(refObject){
        this->ships = ships;
    };

    int shipsCounter();
};

std::ostream &operator<<(std::ostream &os, DefenceC &chart);

class AttackC : public Chart{

private:
    static const char miss = 'O', hit = 'x', scan = 'Y';
    int ships; 

public:
    //constructor
    AttackC(int mapSize = 12, int ships = 6): Chart(mapSize){
        this->ships = ships;
    };

    //copy constructor
    AttackC(const Chart& refObject, int ships = 6) : Chart(refObject){
        this->ships = ships;
    };

    int shipsCounter();
    attack(DefenceC enemyChart);
};

std::ostream &operator<<(std::ostream &os, AttackC &chart);

#endif