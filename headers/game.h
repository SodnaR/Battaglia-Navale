#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <map>

#include <random>
#include <cstdlib>
#include <ctime>

#include<thread>
#include<chrono>

#include "./player.h"

std::pair<std::string, std::string> gen_coordinate(int dim);

Player botVsbot(int mapSize = 12, int b_ships = 3, int s_ship = 3, int e_ship = 2, int turns = 300);


#endif
