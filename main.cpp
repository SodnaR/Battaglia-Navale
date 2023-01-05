#include <iostream>
#include <vector>
using namespace std;

#include "headers/charts.h"

int main(){
    AttackC attack1, attack2;
    attack1.setTile(2, 10, 'A');
    cout<<attack1;
    return 0;
}