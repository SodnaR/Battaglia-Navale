#ifndef CHARTS_H
#define CHARTS_H

#include <string.h>

class Chart{

private:
    char chart[12][12];

    bool valid();

public:
    Chart::Chart();
    Chart::Chart(const Chart & refObject);

    std::string show();
    void clear();
};

class AttackC : public Chart{

private:
    char miss = "O",
         hit = "x",
         scan = "Y";
    int ships; 

public:
    AttackC::AttackC(int ships): Chart();
    AttackC::AttackC(const Chart & refObject, int ships) : Chart(refObject);

    std::string show(): show();
    void clear(): clear();

    int shipsCounter();
};

class DefenseC : public Chart{
    
private:
    char bShip = "C",
         sShip = "S",
         sub = "E";
    int ships;

    bool valid(): valid();

public:
    DefenseC::DefenseC(int ships): Chart();
    DefenseC::DefenseC(const Chart & refObject, int ships) : Chart(refObject);

    std::string show(): show();
    void clear(): clear();

    int shipsCounter();
};

#endif