#include "../headers/charts.h"

int DefenceC::shipsCounter(){
    return ships;
}


std::ostream &operator<<(std::ostream &os, DefenceC &chart){
    return os;
}

