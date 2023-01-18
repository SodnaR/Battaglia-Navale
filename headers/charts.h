#ifndef CHARTS_H
#define CHARTS_H

#include <cctype>
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

    ~Chart(){};

    bool valid(int col, int row);
    bool valid(std::string coordinate);
    bool thereIsChar(char id);
    std::string show();
    std::string show_coordinate();
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
    int bships;

public:
    //constructor
    DefenceC(int mapSize = 12, int bships = 0): Chart(mapSize){
        this->bships = bships;
    };

    //copy constructor
    DefenceC(const Chart& refObject, int bships = 0) : Chart(refObject){
        this->bships = bships;
    };

    int addShip();
    int removeShip();

    //getter
    int shipsCounter();
};

std::ostream &operator<<(std::ostream &os, DefenceC &chart);

class AttackC : public Chart{

private:
    static const char miss = 'O', hit = 'x', scan = 'Y';

public:
    //constructor
    AttackC(int mapSize = 12): Chart(mapSize){};

    //copy constructor
    AttackC(const Chart& refObject) : Chart(refObject){};

};

std::ostream &operator<<(std::ostream &os, AttackC &chart);

#endif