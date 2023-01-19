#ifndef GAME_H
#define GAME_H

#include "./engine.h"

Player botVsbot(int mapSize = 12, int b_ships = 3, int s_ship = 3, int e_ship = 2, int turns = 300);
Player playerVsbot(std::string username, int mapSize = 12, int b_ships = 1, int s_ship = 1, int e_ship = 1, int turns = 300);


#endif
