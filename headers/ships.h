#ifndef SHIPS_H
#define SHIPS_H

#include <string>
#include <vector>

class Ship{

private:
    int plate, 
        dim;
    std::vector<bool> shot;

    void sink();
    bool valid(std::string tile);

    int findOrientation(std::string stern, std::string bow);
    int findOrientation(int stern[], int bow[]);

protected:
    int orient;
    char id;

public:
    Ship(int dim, std::string stern, std::string bow, char id);
    Ship(int dim, int stern[], int bow[], char id);
    Ship(int dim = 0, int orient = 0, char id = ' ');

    int hit();
    void heal();
    char getId();
    
    //getter
    int getDimension();
    int getArmor();
    int getOrientation();
    std::vector<bool> getStatus();
    bool getSingleStatus(int part);
};

std::ostream &operator<<(std::ostream &os, Ship &ship);

class Battleship : public Ship{

private:
    std::string center;

    std::string locateCenter(std::string stern, std::string bow);
    std::vector<int> locateCenter(int stern[], int bow[]);

    std::string toTile(std::vector<int>);

    bool supported();

public:

    Battleship(std::string stern, std::string bow, char id = 'C') : Ship(5, stern, bow, id){
        center = locateCenter(stern, bow);
    };
    Battleship(int stern[], int bow[], char id = 'C') : Ship(5, stern, bow, id){
        center = toTile(locateCenter(stern, bow));
    }

    void fire();

    //getter
    std::string getCenter();
};

class Support : public Ship{

private:
    std::string center;

    std::string locateCenter(std::string stern, std::string bow);
    std::vector<int> locateCenter(int stern[], int bow[]);

    bool supported();

public:
    Support(std::string stern, std::string bow, char id = 'S') : Ship(3, stern, bow, id){
        center = locateCenter(stern, bow);
    };

    void move_heal();
    
    //getter
    std::string getCenter();
};

class Submarine : public Ship{

private:
    std::string center;
    
    std::string locateCenter(std::string stern, std::string bow);
    std::vector<int> locateCenter(int stern[], int bow[]);
    bool supported();

public:
    Submarine(std::string stern, std::string bow, char id = 'E') : Ship(1, 0, id){
        center = locateCenter(stern, bow);
    }
    
    void move_scan();
    
    //getter

};

#endif