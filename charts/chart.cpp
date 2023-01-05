#include "../headers/charts.h"


Chart::Chart(int mapSize){
    this->mapSize = mapSize;
    for (int i = 0; i < mapSize; i++)
    {
        std::vector<char> line;
        for (int j = 0; j < mapSize; j++)
        {
            line.push_back(' ');
        }
        chart.push_back(line);
    }
}

int Chart::letterToCoordinate(std::string coordinate){
    char start = 'a';
    return coordinate[0] - start;
}

bool Chart::valid(std::string coordinate){
    return false;
}

std::string Chart::show(){
    std::string output = "\n";
    for (int i = 0; i < mapSize; i++){
        for(int j = 0; j < mapSize; j++){
            output += "[";
            output += chart[i][j];  
            output += "]";
        }
        output += "\n";
    } 
    return output;
}

void Chart::clear(){
    chart.clear();
}

std::vector<std::vector<char>> Chart::getChart(){
    return this->chart;
}

char Chart::getTile(int col, int row){
    return this->chart[col][row];
}

int Chart::getMapSize(){
    return this->mapSize;
}

char Chart::setTile(int row, int col, char sub){
    this->chart[row][col] = sub;
    return sub;
}

char Chart::setTile(std::string tile, char sub){
    try{
        if(tile.length()==3){
            return setTile(letterToCoordinate(tile.substr(0, 1)), std::stoi(tile.substr(1, 2)), sub);
        } else if (tile.length()==2){
            return setTile(letterToCoordinate(tile.substr(0, 1)), std::stoi(tile.substr(1, 1)), sub);
        } else {
             throw(tile.length());
        }
    } catch(int invalid){
        return 0;
    }
}

std::ostream& operator<<(std::ostream& os, Chart& map){
    std::string out = map.getMapSize() + "\n";
    out += map.show();
    os << out;
    return os;
}

bool operator==(Chart map1, Chart map2){
    if(map1.getMapSize() != map2.getMapSize()) return false;
    for (int i = 0; i < map1.getMapSize(); i++)
    {
        for (int j = 0; j < map2.getMapSize(); j++)
        {
            if(map1.getTile(i, j) != map2.getTile(i, j)) return false;
        } 
    }
    return true;
}