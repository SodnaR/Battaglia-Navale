#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <random>
#include <ctime>

#include<thread>
#include<chrono>

#include "./player.h"

extern int bship_custom, sship_custom, eship_custom;
extern int map_custom;
extern int turn_custom;

extern std::vector<Battleship> bships;
extern std::vector<Support> sships;
extern std::vector<Submarine> eships;

void setCustomGame(int mapSize, int b_ships, int s_ship, int e_ship, int turns);
void setCustomGame(std::ifstream& log);
void gen_Ships(std::ofstream& log, Player& player);
void insert_Ships(Player& p1, Player& p2, string file_name);
void turn(std::ofstream& log, Player& player, Player& opponent);
void playerTurn(std::ofstream& log, Player& p1, Player& p2);
void vReplay(Player& p1, Player& p2, string file_name);
void fReplay(Player& p1, Player& p2, string file_name);

std::pair<std::string, std::string> gen_coordinate(int dim);

#endif // !ENGINE_H