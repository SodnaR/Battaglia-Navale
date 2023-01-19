#include "headers/game.h"
using namespace std;

Player playerVsbot(){
    Player player, bot1;
    return bot1;
}

void playerVsplayer(){
    
}

int main(){
    Player winner;
    int players;
    string username;

    std::cout << "Benvenuti: prego inserire il numero di giocatori [Max 2]: ";
    cin >> players;
    std::cout <<flush; //flush forces the printing to the screen before it pauses
/*
    std::cout << "Regole custom: ";
    std::cout <<endl<< "Inserire la quantita' di corazzate: ";
    cin >> bship_custom;
    std::cout <<endl<< "Inserire la quantita' di suppoorti: ";
    cin >> sship_custom;
    std::cout <<endl<< "Inserire la quantita' di sottomarini: ";
    cin >> eship_costum;*/
    system("clear");

    switch (players)
    {
    case 0:
        winner = botVsbot(9);
        break;
    case 1:
        //winner = playerVsbot();
        break;
    case 2:
        //winner = playerVsplayer();
        break;
    case 9:
        //testGame();
        break;
    }

    std::cout << "The winner is:" <<winner.getUsername()<< std::endl;
    return 0;
}