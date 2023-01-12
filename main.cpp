#include <iostream>
#include <vector>
#include <map>
#include <iterator>
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

    Player p2;
    cout<<d2;

    string t1 = "a1", t2 = "e1";
    Ship shipTest = Battleship(t1, t2);
    p2.addShip(t1, t2, shipTest);

    map<string, Ship>::iterator it = p2.shipLegend().begin();

    for (std::pair<std::string, Ship> element : p2.shipLegend()) {
        // Accessing KEY from element
        std::string word = element.first;
        Ship ship = element.second;
        std::cout << endl << word <<" :: "<< ship.getArmor();
        ship.hit();
    }

    return 0;
}