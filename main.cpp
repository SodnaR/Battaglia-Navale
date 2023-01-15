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
        std::cout << word <<" :: "<< ship->getArmor()<<endl;
    }
}

const pair<string, string>  s1("a1", "a5"),
                            s2("b2", "f2"),
                            s3("n7", "n11"),
                            s4("i4", "i8"),

                            s5("c3", "c5"),
                            s6("g7", "g9"),
                            s7("h1", "h3"),
                            s8("i9", "m9"),

                            s9("d9", "d9"),
                            s0("f5", "f5");


int main(){
    Player p1, p2;

    Battleship bs1(s1.first, s1.second), bs2(s2.first, s2.second), bs3(s3.first, s3.second), bs4(s4.first, s4.second);
    Support    ss1(s5.first, s5.second), ss2(s6.first, s6.second), ss3(s7.first, s7.second), ss4(s8.first, s8.second);
    Submarine  es1(s9.first, s9.second), es2(s0.first, s0.second);

    p1.addShip(s1.first, s1.second, bs1);
    p2.addShip(s2.first, s2.second, bs2);
    p1.addShip(s3.first, s3.second, bs3);
    p2.addShip(s4.first, s4.second, bs4);

    p1.addShip(s5.first, s5.second, ss1);
    p2.addShip(s6.first, s6.second, ss2);
    p1.addShip(s7.first, s7.second, ss3);
    p2.addShip(s8.first, s8.second, ss4);

    p1.addShip(s9.first, s9.second, es1);
    p2.addShip(s0.first, s0.second, es2);

    cout<<"Player 1:\n"<<p1<<endl<<"------------------------------------------------"<<endl;
    cout<<"Player 2:\n"<<p2<<endl<<"------------------------------------------------"<<endl;

    showmap(p1);

    //p1.move_heal(p1.getShip(s5.first), "m7");
    p1.move_scan(p1.getShip(s9.first), "h7", p2);

    cout<<"Player 1:\n"<<p1<<endl<<"------------------------------------------------"<<endl;
    
    return 0;
}
