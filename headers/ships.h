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
    virtual char getId();
    
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
    const char id = 'C';
    std::string center;

    std::string locateCenter(std::string stern, std::string bow);
    std::vector<int> locateCenter(int stern[], int bow[]);

    std::string toTile(std::vector<int>);

    bool supported();

public:

    Battleship(std::string stern, std::string bow) : Ship(5, stern, bow, id){
        center = locateCenter(stern, bow);
    };
    Battleship(int stern[], int bow[]) : Ship(5, stern, bow, id){
        center = toTile(locateCenter(stern, bow));
    }

    void fire();

    //getter
    char getId();
    std::string getCenter();
    int getOrientation();
};

class Support : public Ship{

private:
    const char id = 'S';
    std::string center;

    std::string locateCenter(std::string stern, std::string bow);
    std::vector<int> locateCenter(int stern[], int bow[]);

    bool supported();

public:
    Support(std::string stern, std::string bow) : Ship(3, stern, bow, id){
        center = locateCenter(stern, bow);
    };

    void move_heal();
    
    //getter
    char getId();
    std::string getCenter();
    int getOrientation();
};

class Submarine : public Ship{

private:
    const char id = 'E';
    std::string center;
    
    std::string locateCenter(std::string stern, std::string bow);
    std::vector<int> locateCenter(int stern[], int bow[]);
    bool supported();

public:
    Submarine(std::string stern, std::string bow) : Ship(1, 0, id){
        center = locateCenter(stern, bow);
    }
    
    void move_scan();
    
    //getter
    char getId();

};

#endif