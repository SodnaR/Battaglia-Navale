#include <iostream>
#include <vector>
#include <map>
#include <memory>
using namespace std;

/*Compilatore
*   g++ -o test main.cpp charts/chart.cpp charts/attack_chart.cpp charts/defense_chart.cpp player/player.cpp ships/ship.cpp ships/battleship.cpp ships/support.cpp ships/submarine.cpp
*
*/

#include "headers/player.h"

int main(){
    DefenceC defence;
    DefenceC d2 = defence;

    Player p2(defence);

    p2.addShip((string)"b1", (string)"b5", Ship(5, 0));
    return 0;
}