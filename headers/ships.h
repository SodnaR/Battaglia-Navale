#ifndef SHIPS_H
#define SHIPS_H

#include <string>
#include <vector>

class Ship{

private:
    int plate, 
        dim;
    std::string center;

    void sink();
    bool valid(std::string tile);

    int findOrientation(std::string stern, std::string bow);
    int findOrientation(int stern[], int bow[]);

    std::string locateCenter(std::string stern, std::string bow);
    std::string locateCenter(int stern[], int bow[]);

protected:
    int orient;
    char id;

public:
    Ship(int dim, std::string stern, std::string bow, char id);
    Ship(int dim, int stern[], int bow[], char id);
    Ship(int dim = 0, std::string center = " ", char id = ' ');

    Ship(Ship* ship);

    int hit();
    void heal();
    
    //getter
    int getDimension();
    int getArmor();
    int getOrientation();
    std::string getCenter();
    char getId();
    std::vector<bool> getStatus();
    bool getSingleStatus(int part);

};

std::ostream &operator<<(std::ostream &os, Ship &ship);
bool operator==(Ship ship1, Ship ship2);
bool operator!=(Ship ship1, Ship ship2);

struct Battleship : public Ship{

private:
    char cavallo = 'C';

public:

    Battleship(std::string stern, std::string bow, char id = 'C') : Ship(5, stern, bow, id){
    }
    Battleship(int stern[], int bow[], char id = 'C') : Ship(5, stern, bow, id){
    }

};

struct Support : public Ship{

private:

public:
    Support(std::string stern, std::string bow, char id = 'S') : Ship(3, stern, bow, id){
    };

};

struct Submarine : public Ship{

private:

public:
    Submarine(std::string stern, std::string bow, char id = 'E') : Ship(1, stern, id){
    }

};

#endif