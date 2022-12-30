#include "headers/charts.h"

#include <vector>

Chart::Chart(int mapSize){
    for (int i = 0; i < mapSize; i++)
    {
        std::vector<char> line;
        for (int j = 0; i < mapSize; j++)
        {
            line.push_back(" ");
        }
        this->chart.push_back(line);
    }
}