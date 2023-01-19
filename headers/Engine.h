#ifndef	ENGINE_H
#define ENGINE_H
#include "headers/player.h"
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <string>

void insertShips(Player& p1, Player& p2, std::string file_name);
void Vreplay(Player& p1, Player& p2, std::string file_name);
void Freplay(Player& p1, Player& p2, std::string file_name);

#endif
