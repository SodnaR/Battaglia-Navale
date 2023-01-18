#include "../headers/player_copy.h"

#include <iostream>

/*nextId
* + variabile
*
*   Serve come identificatore del giocatore
*   Aggiornato alla creazione di ogni giocatore
*/
int Player::nextId = 0;

Player::Player(std::string name){
    this->name = "bot" + name;
    this->a_grid = AttackC();
    this->d_grid = DefenceC();
}

Player::Player(DefenceC d_grid, std::string name){
    this->name = "bot" + name;
    this->a_grid = AttackC(d_grid.getMapSize());
    this->d_grid = DefenceC(d_grid);
}

Player::Player(const Player& refObject){
    this->name = refObject.name;
    this->a_grid = refObject.a_grid;
    this->d_grid = refObject.d_grid;
    this->ships = refObject.ships;
}

/*validPosition
*   Controlla i valori dei e tra i tile della nave
*
*   Ritorna se i valori rispettano gli standard progettuali
*   - lunghezza designata di un tile (3)["n12"]
*   - se è presente all'interno della tabella
*   - la posizione fra i tile rispetta un asse [verticale, orizzontale]
*/
bool Player::validPosition(std::string tile, std::string toTile){
    try{
        if(tile.length() < 2 || tile.length() > 3) throw(tile);
        if(toTile.length() < 2 || toTile.length() > 3) throw(tile);
        if(!d_grid.valid(tile) || !d_grid.valid(toTile)) throw(tile);
        if(tile[0] != toTile[0] && tile.substr(1) != toTile.substr(1)) throw(tile);
    } catch(std::string invalid){
        return false;
    }
    return true;
}

/*obstacles
*   Controlla se tra le posizione ed i tile stessi son presenti solo spazi vuoti
*
*   Ritorna se quindi è possibile inserire la nave in un determinato spazio
*   - se tra la poppa e la prua non ci sono ostacoli
*/
bool Player::obstacles(std::string stern, std::string bow,  std::shared_ptr<Ship> ship){
    std::string start = stern, end = bow;
    while(start != end){
        if(d_grid.getTile(start) != ' '){
            return true;
        }
        if(ship->getOrientation()){
            int y;
            if(start.length()==3){
                y = std::stoi(start.substr(1, 2));
                y++;
                start.replace(1, 2, std::to_string(y));
            } else {
                y = std::stoi(start.substr(1, 1));
                y++;
                start.replace(1, 2, std::to_string(y));
            }
        } else {
            start[0]++;
        }
    }
    if(d_grid.getTile(end) != ' '){
        return true;
    }
    return false;
}

/*addToChart
*   Aggiunge alla griglia di difesa l'identificativo assegnato dalla nave
*/
char Player::addToChart(std::string tile, char id){
    d_grid.setTile(tile, id);
    return id;
}

/*move
*   Permette di spostare la nave tra i vari blocchi della tabella
*
*   Conseguente cambio di coordinate per ricercarla
*   Ritorna bool, in base all'esito e la possibilità nello spostamento
*/
bool Player::move(std::string stern, std::string bow, std::shared_ptr<Ship> ship){
    if(ship->getArmor() == 0) return false;
    std::string center = ship->getCenter();
    d_grid.setTile(center, ' ');
    ships.erase(center);
    std::map<std::string, std::shared_ptr<Ship>>::iterator it = ships.begin();
    while (it != ships.end()){
        if(it->second == ship){
            std::cout << it->first << std::endl;
                    d_grid.setTile(it->first, ' ');
                    ships.erase(it->first);
            }
        it++;
    }

    int y;
    if(stern.length()==3){
        y = std::stoi(stern.substr(1, 2)); 
    } else {
        y = std::stoi(stern.substr(1, 1)); 
    }
    if(ship->getOrientation()){
        int y2;
        if(bow.length()==3){
            y2 = std::stoi(bow.substr(1, 2));
        } else {
            y2 = std::stoi(bow.substr(1, 1));
        }
        for (int i = y; i <= y2; i++){
            std::string tile(1, stern[0]);
            tile += std::to_string(i); 
            d_grid.setTile(tile, ship->getId());
            ships.insert(std::pair<std::string, std::shared_ptr<Ship>>(tile, ship));
        }    
    } else {
        char x1 = stern[0], x2 = bow[0];
        for (char i = x1; i <= x2; i++){
            if(x1 >= 'j') x1 += 2;
            if(x1 >= 'w') x1 += 3;
            std::string tile(1, i);
            tile += std::to_string(y);
            d_grid.setTile(tile, ship->getId());
            ships.insert(std::pair<std::string, std::shared_ptr<Ship>>(tile, ship));
        }
    }
    ship->moved(ship->locateCenter(stern, bow));
    return true;
}

/*heal
*  Permette alle navi di ripristinare _plate
*
*  In un area 3x3 della tabella se presente una nave con armatura alterata la ripristina
*  - eccezione fatta per la stessa nave che invoca il metodo
*   Ritorna se bool, in base all'esito dell'azione  
*/
bool Player::heal(std::shared_ptr<Ship> ship){
    std::string center = ship->getCenter();
    std::string tile;
    char x = center[0];
    int y;
    if(center.length() == 3){
        y = std::stoi(center.substr(1, 2));
    } else{
        y = std::stoi(center.substr(1, 1));
    }
    if(x > 'y') x -=3;
    if(x > 'k') x -=2;
    for (int i = (x > 'a') ? (x - 1) : 0; i <= (x - 'a' + 1) && i < d_grid.getMapSize(); i++){
        for(int j = (y > 0) ? (y - 1) : 0; j <= (y + 1) && j <= d_grid.getMapSize(); j++){
            tile = (1, i);
            tile += std::to_string(j);
            if(ships.find(tile) != ships.end()){
                if(getShip(tile) != ship){
                    getShip(tile)->heal();
                }
            }
        }
    }
    return true;
}

/*scan
*   Permette di vedere la posizione delle navi nella plancia avversaria
*
*   In un area 5x5 riporta le posizioni delle navi avversarie
*   - [Y] per l'avvistamento
*   - [x] per colpo avvenuto con successo
*   Ritorna se bool, in base all'esito dell'azione  
*/
bool Player::scan(std::shared_ptr<Ship> ship, Player opposite){
    std::string center = ship->getCenter();
    std::string tile;
    char x = center[0];
    int y;
    if(center.length() == 3){
        y = std::stoi(center.substr(1, 2));
    } else{
        y = std::stoi(center.substr(1, 1));
    }
    if(x > 'y') x -=3;
    if(x > 'k') x -=2;
    for(int i = (x > 'b') ? (x - 2) : 0; i <= (x - 'a' + 2) && i< d_grid.getMapSize(); i++){
        for(int j = (y > 2) ? (y - 2) : 1; j <= (y + 2) && j < d_grid.getMapSize(); j++){
            if(i >= 'w') tile = (1, (i + 'a' + 5));
            else if(i >= 'j') tile = (1, (i + 'a' + 2));
            else tile = (1, (i + 'a'));
            tile += std::to_string(j);
            if(a_grid.getTile(tile) == ' '){
                if(opposite.getDefenceGrid().getTile(tile) != ' '){
                    a_grid.setTile(tile, 'Y');
                }
            } else if(a_grid.getTile(tile) == 'x' || a_grid.getTile(tile) == 'X'){
                if(!opposite.getShip(tile)){
                    a_grid.setTile(tile, ' ');
                }else if(opposite.getShip(tile)->getArmor() == opposite.getShip(tile)->getDimension()){
                    a_grid.setTile(tile, 'Y');
                }
            } else{ 
                if(opposite.getDefenceGrid().getTile(tile) == ' '){
                    a_grid.setTile(tile, ' ');
                }
            }
        }
    }
    return true;
}

/*addShip
*   Aggiunge alla legenda del giocatore una nuova nave
*
*   Puntato l'oggetto nave, in una mappa di puntatori
*   Inserito il proprio carattere identificativo nelle posizioni affidate
*
*   Ritorna se bool, in base alla disponibilità di inseriremento nelle mappe
*/
bool Player::addShip(std::string stern, std::string bow, Ship& ship){
    std::shared_ptr<Ship> shipPointer(new Ship(ship));
    std::vector<std::shared_ptr<Ship>> pointers;
    int y;
    if(!validPosition(stern, bow)) return false;
    if(obstacles(stern, bow, shipPointer)) return false;
    if(stern.length()==3){
        y = std::stoi(stern.substr(1, 2)); 
    } else {
        y = std::stoi(stern.substr(1, 1)); 
    }
    if(ship.getOrientation()){
        int y2;
        if(bow.length()==3){
            y2 = std::stoi(bow.substr(1, 2));
        } else {
            y2 = std::stoi(bow.substr(1, 1));
        }
        for (int i = y; i <= y2; i++){
            std::string tile(1, stern[0]);
            tile += std::to_string(i); 
            d_grid.setTile(tile, ship.getId());
            pointers.push_back(shipPointer);
            ships.insert(std::pair<std::string, std::shared_ptr<Ship>>(tile, pointers[(pointers.size() - 1)]));
        }    
    } else {
        char x1 = stern[0], x2 = bow[0];
        for (char i = x1; i <= x2; i++){
            if(x1 >= 'j') x1 += 2;
            if(x1 >= 'w') x1 += 3;
            std::string tile(1, i);
            tile += std::to_string(y);
            d_grid.setTile(tile, ship.getId());
            pointers.push_back(shipPointer);
            ships.insert(std::pair<std::string, std::shared_ptr<Ship>>(tile, pointers[(pointers.size() - 1)]));
        }
    }
    if(ship.getId() == 'C')d_grid.addShip();
    return true;
}

/*removeShip
*   Distrugge una nave tra legenda e plancia
*
*   =>Se una nave ha armatura pari a 0:
*   - Rimozione delle chiavi dalla lista
*   - Rimozione dalla griglia di difesa del giocatore
*   Ritorna bool, se eliminata con successo
*/
bool Player::removeShip(std::shared_ptr<Ship> ship){
    std::map<std::string, std::shared_ptr<Ship>>::iterator it = ships.begin();
    while (it != ships.end()){
        if(it->second == ship){
            d_grid.setTile(it->first, ' ');
            ships.erase(it->first);
        }
        it++;
    }
    d_grid.removeShip();
    return true;
}

/*shot
*   Permette di eseguire un'azione della partita: [richiesta Battleship]
*
*   Riporta sulla griglia di attacco del giocatore l'identificazione di una nave nemica
*   Controlla se nella griglia di difesa avversaria quale elemento è presente nella posizione consegnata
*
*   Ritorna bool, in base al successo della chiamata
*/
bool Player::shot(std::shared_ptr<Ship> bship, std::string tile, Player &opposite){
    if(!bship) return false;
    if(bship->getId() != 'C') return false;
    if(opposite.getDefenceGrid().getTile(tile) != ' '){
        a_grid.setTile(tile, 'x');
        opposite.getDefenceGrid().setTile(tile, std::tolower(opposite.getDefenceGrid().getTile(tile)));
        opposite.getShip(tile)->hit();
        std::shared_ptr<Ship> dummy = opposite.getShip(tile);
        if(dummy->getArmor() == 0){
            std::map<std::string, std::shared_ptr<Ship>>::iterator it = opposite.shipLegend().begin();
            while (it != opposite.shipLegend().end()){
                if(it->second == dummy){
                    a_grid.setTile(it->first, 'X');
                }
                it++;
            }
            opposite.removeShip(dummy);
        }
    } else {
        a_grid.setTile(tile, 'O');
    }
    return true;
}

/*move_heal
*   Permette di eseguire un'azione della partita: [richiesta Support]
*
*   Richiama le funzioni: move, heal
*   Unico modo di accesso all'azione unica, ed ai 2 metodi privati
*
*   Ritorna bool, in base al successo della chiamata
*/
bool Player::move_heal(std::shared_ptr<Ship> sship, std::string tile){
    if(!sship) return false;
    if(sship->getId() != 'S') return false;
    std::string stern, bow;
    int coord;
    if(tile.length() == 3){
        coord = std::stoi(tile.substr(1, 2));
    } else {
        coord = std::stoi(tile.substr(1, 1));
    }
    if(sship->getOrientation()){
        stern = (1, tile[0]);
        stern += std::to_string(coord - 1);
        bow = (1, tile[0]);
        bow += std::to_string(coord + 1);
    } else {
        if(tile[0] > 'k') stern = (1, tile[0] - 3);
        else if(tile[0] > 'y') stern = (1, tile[0] - 6);
        else stern = (1, tile[0] - 1);
        stern += std::to_string(coord);
        bow = (1, tile[0] + 1);
        bow += std::to_string(coord);
    }
    if(!validPosition(stern, bow)) return false;
    if(obstacles(stern, bow, sship)) return false;

    if(!move(stern, bow, sship)) return false;
    if(!heal(sship)) return false;

    return true;
}

/*move_scan
*   Permette di eseguire un'azione della partita: [richiesta Submarine]
*
*   Richiama le funzioni: move, scan
*   Unico modo di accesso all'azione unica, ed ai 2 metodi privati
*
*   Ritorna bool, in base al successo della chiamata
*/
bool Player::move_scan(std::shared_ptr<Ship> eship, std::string tile, Player &opposite){
    if(!eship) return false;
    if(eship->getId() != 'E') return false;
    if(d_grid.getTile(eship->getCenter()) != eship->getId()) return false;

    if(!validPosition(tile, tile)) return false;
    if(obstacles(tile, tile, eship)) return false;
    if(!move(tile, tile, eship)) return false;
    if(!scan(eship, opposite)) return false;

    return true;
}

std::string Player::getUsername(){
    return name;
}

DefenceC Player::getDefenceGrid(){
    return d_grid;
}

AttackC Player::getAttackGrid(){
    return a_grid;
}

std::map<std::string, std::shared_ptr<Ship>> Player::shipLegend(){
    return ships;
}

std::shared_ptr<Ship> Player::getShip(std::string tile){
    if(ships.find(tile) != ships.end()) return ships[tile];
    return 0;
}

std::string Player::getShipCenter(std::string ship_tile){
    return ships[ship_tile]->getCenter();
}

std::string Player::setUsername(std::string username){
    this->name = username;
    return name;
}

std::ostream &operator<<(std::ostream &os, Player &player){
    std::string out = "La tua plancia:";
    out +=  player.getDefenceGrid().show_coordinate();
    out += "\nLa plancia nemica:";
    out += player.getAttackGrid().show_coordinate();
    os<<out;
    return os;
}