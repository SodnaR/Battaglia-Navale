#include "../headers/charts.h"

int DefenceC::addShip(){
    return ++ships;
}

int DefenceC::shipsCounter(){
    return ships;
}

std::ostream &operator<<(std::ostream &os, DefenceC &chart){
    char slot = 'A';

    std::string out = "Map Size: "+ std::to_string(chart.getMapSize()) +"\n";
    std::vector<std::vector<char>> ref = chart.getChart();
    for (int i = 0, s = 0; i < chart.getMapSize(); i++, s++){
        if(s==9) s+=2;
        if(s==21) s+=3;
        out += slot + s;
        for(int j = 0; j < chart.getMapSize(); j++){
            out += "[";
            out += ref[i][j];  
            out += "]";
        }
        out += "\n";
    } 
    for(int i = 1; i <= chart.getMapSize(); i++){
        if(i <= 10){
            out += "  ";
        } else {
            out += " ";
        }

        out += std::to_string(i);
    }
    out += "\n";
    os << out;
    return os;
}

