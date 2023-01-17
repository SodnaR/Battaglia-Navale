#ifndef SHIPS_H
#define SHIPS_H

#include <string>
#include <vector>

class Ship{

private:
    int plate, 
        dim;
    std::string center;

    int findOrientation(std::string stern, std::string bow);
    int findOrientation(int stern[], int bow[]);


protected:
    int orient;
    char id;

public:
    Ship(int dim, std::string stern, std::string bow, char id);
    
    Ship(const Ship& refObject);

    ~Ship(){};
    
    std::string locateCenter(std::string stern, std::string bow);
    std::string locateCenter(int stern[], int bow[]);

    int hit();
    int heal();
    
    //getter
    int getDimension();
    int getArmor();
    int getOrientation();
    std::string getCenter();
    char getId();
    std::vector<bool> getStatus();
    bool getSingleStatus(int part);

    //setter
    std::string moved(std::string center);
};

std::ostream &operator<<(std::ostream &os, Ship &ship);
bool operator==(Ship ship1, Ship ship2);
bool operator!=(Ship ship1, Ship ship2);

struct Battleship : public Ship{

public:

    Battleship(std::string stern, std::string bow, char id = 'C') : Ship(5, stern, bow, id){
    }

    Battleship(const Battleship& refObject) : Ship(refObject){
    }; 

};


struct Support : public Ship{

public:
    Support(std::string stern, std::string bow, char id = 'S') : Ship(3, stern, bow, id){
    };

    Support(const Support& refObject) : Ship(refObject){
    }; 
};

struct Submarine : public Ship{

public:
    Submarine(std::string stern, std::string bow, char id = 'E') : Ship(1, stern, bow, id){
    }

    Submarine(const Submarine& refObject) : Ship(refObject){
    }; 

};

#endif