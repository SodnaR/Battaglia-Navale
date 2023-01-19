/*Ideatori: Sartori Mattia
*           Zanella Samuele
*
*Autore:    Sartori Mattia
*/
#include "engine.h"
using namespace std;


int main(){
	char replay_mode;
	bool mode;
	string file_name;
	cout << "inserire modalità di replay:"<< endl 
         << " v [nome_file_log] stampa a schermo " << endl 
         << " f [nome_file_log] creazione file" << endl << endl;
	cin>>replay_mode>>file_name;
	do{
        mode = true;
		if(replay_mode=='v'){
			vReplay(file_name);
		}else if(replay_mode=='f'){
			fReplay(file_name);
			cout << "file di log creato, nome: [game_log.txt]" << endl;
		}else{
			cout << "modalità di replay non pervenuta, inserire modalità valida" << endl;
			cin>>replay_mode;
			mode=false;
		}
	}while(!mode);
	return 0;
}
