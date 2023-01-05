#ifndef SHIPS_H
#define SHIPS_H

#include <string>

class Ship{

private:
    int plate, 
        dim;
        
    void sink();

public:
    Ship(int start);

    bool hit();
};

class Battleship : public Ship{

private:
    std::string center;

    std::string locateCenter(std::string stern, std::string bow);
    bool supported();

public:

    Battleship(std::string stern, std::string bow) : Ship(5){
        center = locateCenter(stern, bow);
    };

    void fire();
};

class Support : public Ship{

private:
    std::string center;

    std::string locateCenter(std::string stern, std::string bow);
    bool supported();

public:
    Support(std::string stern, std::string bow) : Ship(3){
        center = locateCenter(stern, bow);
    };

    void move_heal();
};

class Submarine : public Ship{

private:
    std::string center;
    
    std::string locateCenter(std::string stern, std::string bow);
    bool supported();

public:
    Submarine(std::string stern, std::string bow) : Ship(1){
        std::string locateCenter(std::string stern, std::string bow);
    }

    void move_scan();
};

#endif