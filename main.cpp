/*Ideatori: Sartori Mattia
*           Zambon Francesco
*           Zanella Samuele
*
*Autore:    Zanella Samuele
*/
#include "game.h"
using namespace std;

int main(int argc, char** argv){
    Player winner;
    int players;
    string username;

    cout << "Selezionare modalità di gioco: ";
    cin >> players;
    cout <<flush;
    system("clear");

    switch (players)
    {
    case 0:
        winner = botVsbot();
        break;
    case 1:
        cout << "Inserire il proprio username: ";
        cin >> username;
        cout <<flush;
        system("clear");
        winner = playerVsbot(username);
        break;
    case 2:
        break;
    }

    std::cout << "The winner is:" <<winner.getUsername()<< std::endl;
    return 0;
}
