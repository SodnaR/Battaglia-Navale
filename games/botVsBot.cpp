/*Ideatori: Sartori
*           Zambon Francesco
*           Zanella Samuele
*
*
*Autore:    Zanella Samuele
*/
#include "game.h"

/*botVsbot
*   Funzione principale dove si scontrano due giocatori comandati dalla IA
*   Inizializza una partita standard o custom a piacimento del giocatore
*   
*   Ritorna il giocatore vincitore
*   + In caso di parità una situazione neutra di pareggio
*/
Player botVsbot(int mapSize, int b_ships, int s_ship, int e_ship, int turns){
    std::ofstream log("log_bot.txt");
    setCustomGame(mapSize, b_ships, s_ship, e_ship, turns);
    log << map_custom << " " << bship_custom << " " << sship_custom << " " << eship_custom << " " << turn_custom << std::endl;
    log << "Player1" << std::endl;  

    //Creazione dei bot in automatico
    Player bot1(map_custom);
    gen_Ships(log, bot1);
    Player bot2(map_custom);
    gen_Ships(log, bot2);
    
    //Inizio partita
    std::cout << std::endl << bot1 <<"--------------------------------"<< std::endl;
    std::cout << std::endl << bot2 <<"--------------------------------"<< std::endl;
	for(int i = 1; i <= turn_custom; i++){
        std::cout << std::endl << "TURNO " << i << std::endl << std::endl;
        //turno giocatore 1
        turn(log, bot1, bot2);
        std::this_thread::sleep_for(std::chrono::nanoseconds(100000));
        //turno giocatore 2
        turn(log, bot2, bot1);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        //Ouput Griglie
        std::cout << std::endl << bot1 <<"--------------------------------"<< std::endl;
        std::cout << std::endl << bot2 <<"--------------------------------"<< std::endl;
        //fine turno di gioco
        if(bot1.getDefenceGrid().shipsCounter() == 0){
            return bot2;
        }
        if(bot2.getDefenceGrid().shipsCounter() == 0){
            return bot1;
        }
    }
    log.close();
    return Player("PAREGGIO");
}
