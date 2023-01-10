#ifndef SHIPS_H
#define SHIPS_H

#include <string>
#include <vector>

class Ship{

private:
    int plate, 
        dim,
        orient;

    void sink();

public:
    Ship(int dim, int orient);

    bool hit();
    void heal();

    
    //getter
    int getDimension();
    int getArmor();
    int getOrientation();

};

class Battleship : public Ship{

private:
    std::string center;

    std::string locateCenter(std::string stern, std::string bow);
    std::vector<int> locateCenter(int stern[], int bow[]);

    int findOrientation(std::string stern, std::string bow);
    int findOrientation(int stern[], int bow[]);

    std::string toTile(std::vector<int>);

    bool supported();

public:

    Battleship(std::string stern, std::string bow) : Ship(5, findOrientation(stern, bow)){
        center = locateCenter(stern, bow);
    };
    Battleship(int stern[], int bow[]) : Ship(5, findOrientation(stern, bow)){
        center = toTile(locateCenter(stern, bow));
    }

    void fire();

    //getter
    std::string getCenter();
    int getOrientation();
};

class Support : public Ship{

private:
    std::string center;

    std::string locateCenter(std::string stern, std::string bow);
    std::vector<int> locateCenter(int stern[], int bow[]);

    bool supported();
    int findOrientation(std::string stern, std::string bow);

public:
    Support(std::string stern, std::string bow) : Ship(3, findOrientation(stern, bow)){
        center = locateCenter(stern, bow);
    };

    void move_heal();
    
    //getter
    std::string getCenter();
    int getOrientation();
};

class Submarine : public Ship{

private:
    std::string center;
    
    std::string locateCenter(std::string stern, std::string bow);
    std::vector<int> locateCenter(int stern[], int bow[]);
    bool supported();

public:
    Submarine(std::string stern, std::string bow) : Ship(1, 0){
        std::string locateCenter(std::string stern, std::string bow);
    }

    void move_scan();
};

#endif