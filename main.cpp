#include <iostream>
#include <vector>
using namespace std;

#include "headers/charts.h"

int main(){
    AttackC attack1(21);

    attack1.setTile(2, 10, 'A');
    attack1.setTile(3, 11, 'A');
    attack1.setTile(1, 1, 'A');
    attack1.setTile(6, 10, 'A');
    attack1.setTile("h4", 'A');
    attack1.setTile(2, 1, 'A');
    attack1.setTile(4, 4, 'A');
    attack1.setTile(3, 7, 'A');
    attack1.setTile(7, 5, 'A');
    cout<<attack1;
    attack1.clear();
    cout<<attack1;


    cout<<attack1.show();

    return 0;
}