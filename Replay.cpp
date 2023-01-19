#include "headers/Engine.h"
using namespace std;
int main(){
	char replay_mode;
	bool mode=true;
	string file_name;
	Player p1, p2;
	cout<<"inserire modalità di replay: \n v [nome_file_log] stampa a schermo \n f[nome_file_log] creazione file"<<endl<<endl;
	cin>>replay_mode>>file_name;
	do{
		if(replay_mode=='v'){
			Vreplay(p1,p2,file_name);
		}else if(replay_mode=='f'){
			Freplay(p1,p2,file_name);
			cout<<"file di log creato, nome: [game_log.txt]"<<endl;
		}else{
			cout<<"modalità di replay non pervenuta, inserire modalità valida"<<endl;
			cin>>replay_mode;
			mode=false;
		}
	}while(!mode);
	return 0;
}
