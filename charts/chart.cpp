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

Chart::Chart(const Chart& refObject){
    this->mapSize = refObject.mapSize;
    this->chart = refObject.chart;
}

/*letterToCoordinate
*   Trasfoma le coordinate dalla parte alfa alla numerica
*
*   Ritorna la posizione in base alla differenza dei caratteri
*/
int Chart::letterToCoordinate(std::string coordinate){
    char start = 'a';
    return coordinate[0] - start;
}


/*valid
*   Controlla se le coordinate son valide
*   
*   Controllo basato sulla base delle posizione della griglia
*/
bool Chart::valid(int col, int row){
    if(col < 0 || col > mapSize) return false;
    if(row < 0 || row > mapSize) return false;
    return true;
}

/*valid
*   Controlla se le coordinate son valide
*
*   Controllo della parte alfa del testo
*   Per poter usare anche la notazione alfanumerica
*/
bool Chart::valid(std::string tile){
    char end = 'a' + mapSize;
    if(tile[0] - end > 0 || tile[0] < 'a') return false;

    if(tile.length() <= 3){
        if(tile.length() == 3){
            int test = std::stoi(tile.substr(1, 2)) - 1;
            return valid(test, test);
        }
        if(tile.length() == 2){
            int test = std::stoi(tile.substr(1, 1)) - 1;
            return valid(test, test);
        }
    }
    else{ 
        return false;
    }

    return true;
}

/*show
*   Mostra la griglia attuale
*
*   Ritorna come stringa
*/
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

/*show_coordinate
*   Mostra la griglia attuale
*   +   Con le coordinate ai lati della griglia
*
*   Ritorna come stringa
*/
std::string Chart::show_coordinate(){
    char slot = 'A';
    std::string out = "\n";
    for (int i = 0, s = 0; i < mapSize; i++, s++){
        if(s==9) s+=2;
        if(s==21) s+=3;
        out += slot + s;
        for(int j = 0; j < mapSize; j++){
            out += "[";
            out += chart[i][j];  
            out += "]";
        }
        out += "\n";
    } 
    for(int i = 1; i <= mapSize; i++){
        if(i <= 10){
            out += "  ";
        } else {
            out += " ";
        }

        out += std::to_string(i);
    }
    out += "\n";
    return out;
}

/*clear
*   Reimposta la griglia al valore di partenza
*/
void Chart::clear(){
    for (int i = 0; i < mapSize; i++)
    {
        std::vector<char> line;
        for (int j = 0; j < mapSize; j++)
        {
            chart[i][j] = ' ';
        }
    }
}

/*getChart
*   Ritorna la griglia
*
*   Ritorna come vettore di vettori di char 
*/
std::vector<std::vector<char>> Chart::getChart(){
    return this->chart;
}

/*getTile
*   Ritorna il valore della casella scelta
*
*   Ritorna il valore in base alla casella in base numerica
*/
char Chart::getTile(int col, int row){
    return this->chart[col][row];
}

/*getTile
*   Ritorna il valore della casella scelta
*   
*   Ritorna il valore in base alla coordinata in base alfanumerica
*/
char Chart::getTile(std::string coordinate){
    int x, y;
    try{
        if(!valid(coordinate)) throw(coordinate);
        if(coordinate.length()==3){
            y = std::stoi(coordinate.substr(1, 2)) - 1;
        } else if (coordinate.length()==2){
            y = std::stoi(coordinate.substr(1, 1)) - 1;
        } else {
             throw(coordinate.length());
        }
        x = letterToCoordinate(coordinate);
    } catch(int invalid){
        return 0;
    } catch(std::string coordinate){
        return 1;
    }
    return getTile(x, y);
}

/*getMapSize
*   Ritorna il valore della grandezza della griglia
*/
int Chart::getMapSize(){
    return this->mapSize;
}

/*setTile
*   Imposta la casella con il valore con il valore desiderato
*
*   Usa le coordinate numeriche per individuare la locazione
*/
char Chart::setTile(int row, int col, char sub){
    if(valid(col, row)) this->chart[row][col] = sub;
    return sub;
}

/*setTile
*   Imposta la casella con il valore con il valore desiderato
*
*   Metodo con il quale si usa un linguaggio alfanumerico
*   presenti molti controlli sulle lettere
*   fa affidamento sul metodo: setTile con variabili numeriche
*/
char Chart::setTile(std::string tile, char sub){
    try{
        if(!valid(tile)) throw(tile);
        if(tile.length()==3){
            return setTile(letterToCoordinate(tile), (std::stoi(tile.substr(1, 2)) - 1), sub);
        } else if (tile.length()==2){
            return setTile(letterToCoordinate(tile), (std::stoi(tile.substr(1, 1)) - 1), sub);
        } else {
             throw(tile.length());
        }
    } catch(int invalid){
        return 0;
    } catch(std::string coordinate){
        return 1;
    }
}

std::ostream& operator<<(std::ostream& os, Chart& map){
    char slot = 'A';

    std::string out = "Map Size: "+ std::to_string(map.getMapSize()) +"\n";
    std::vector<std::vector<char>> ref = map.getChart();
    for (int i = 0, s = 0; i < map.getMapSize(); i++, s++){
        if(s==9) s+=2;
        if(s==21) s+=3;
        out += slot + s;
        for(int j = 0; j < map.getMapSize(); j++){
            out += "[";
            out += ref[i][j];  
            out += "]";
        }
        out += "\n";
    } 
    for(int i = 1; i <= map.getMapSize(); i++){
        if(i <= 10){
            out += "  ";
        } else {
            out += " ";
        }

        out += std::to_string(i);
    }
    out += "\n";
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

bool operator!=(Chart map1, Chart map2){
    return !operator==;
}