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

void showmap(Player player){
    map<string, Ship>::iterator it = player.shipLegend().begin();

    for (std::pair<std::string, Ship> element : player.shipLegend()) {
        // Accessing KEY from element
        std::string word = element.first;
        Ship ship = element.second;
        std::cout << endl << word <<" :: "<< ship.getArmor();
        ship.hit();
    }
}


int main(){
    Player p2;
    string t1 = "e1", t2 = "e6";
    Ship shipTest = Battleship(t1, t2);
    p2.addShip(t1, t2, shipTest);
    t1 = "c3"; t2 = "c5";
    Ship supportTest = Support(t1, t2);
    p2.addShip(t1, t2, supportTest);

    cout<<p2<<endl;

    return 0;
}
