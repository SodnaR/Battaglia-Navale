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
    map<string, Ship*>::iterator it = player.shipLegend().begin();

    for (std::pair<std::string, Ship*> element : player.shipLegend()) {
        // Accessing KEY from element
        std::string word = element.first;
        Ship* ship = element.second;
        std::cout << endl << word <<" :: "<< ship->getArmor();
    }
}


int main(){
    
    Player p1, p2;
    string t1 = "e1", t2 = "e5";
    Battleship shipTest = Battleship(t1, t2);
    Support supportTest = Support("h5", "l5");
    string center = shipTest.getCenter();
    
    p2.addShip(t1, t2, shipTest);
    p2.addShip("h5", "l5", supportTest);
    

    cout<<p2<<endl<<endl;
    /*
    if(p2.move_heal(p2.getShip("h5"), "m11")) cout<<"Corretto";
    cout<<p2<<endl<<endl;
    */
    return 0;
}
