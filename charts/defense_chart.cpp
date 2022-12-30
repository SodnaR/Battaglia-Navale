#include "headers/charts.h"

DefenseC::DefenseC(int ships = 6){
    this->ships = ships;
}

DefenseC::DefenseC(const Chart & refObject, int ships = 6){
    this->ships = ships;
}