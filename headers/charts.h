#ifndef CHARTS_H
#define CHARTS_H

#include <string>
#include <vector>

class Chart{

private:
    std::vector<std::vector<char>> chart;

public:
    Chart(int mapSize = 12);
    Chart(const Chart & refObject, int mapSize = 12);

    std::string show();
    void clear();
    bool valid();
};

class AttackC : public Chart{

private:
    const char miss = 'O', hit = 'x', scan = 'Y';
    int ships; 

public:
    AttackC(int ships = 6): Chart(){
        this->ships = ships;
    };
    AttackC(const Chart & refObject, int ships = 6) : Chart(refObject){
        this->ships = ships;
    };

    int shipsCounter();
};

class DefenseC : public Chart{
    
private:
    const char bShip = 'C', sShip = 'S', sub = 'E';
    int ships;

public:
    DefenseC(int ships = 6): Chart(){
        this->ships = ships;
    };
    DefenseC(const Chart & refObject, int ships = 6) : Chart(refObject){
        this->ships = ships;
    };

    int shipsCounter();
};

#endif