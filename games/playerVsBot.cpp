#include "../headers/game.h"

Player playerVsbot(std::string username, int mapSize, int b_ships, int s_ship, int e_ship, int turns){
    std::ofstream log("log.txt");
    setCustomGame(mapSize, b_ships, s_ship, e_ship, turns);
    log << map_custom << " " << bship_custom << " " << sship_custom << " " << eship_custom << " " << turn_custom << std::endl;

    //Creazione dei bot in automatico
    Player bot1(map_custom);
    gen_Ships(log, bot1);
    Player player1(map_custom, username);
    insert_Ships(log, player1);

    std::cout << player1 << std::endl;

    int coin = rand()%2;
    log << coin;
    for (int i = 1, j = coin; i <= (turn_custom*2); i++){
        if(j==0) j++; 
        std::cout << std::endl << "TURNO " << j << std::endl << std::endl;
        if(coin){
            playerTurn(log, player1, bot1);
            coin = 0;
        } else {
            turn(log, bot1, player1);
            coin = 1;
            j++;
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(100000));
    }
    //fine turno di gioco
    if(bot1.getDefenceGrid().shipsCounter() == 0){
        return player1;
    }
    if(player1.getDefenceGrid().shipsCounter() == 0){
        return bot1;
    }
    log.close();
    return Player("PAREGGIO");
}