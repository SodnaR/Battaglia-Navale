
void insertShips(Player& p){
	string bow, stern;
    pair<string, string> ship = gen_coordinate(5);
    Battleship bship(ship.first, ship.second);
    bool done=false;
    for(int i = 0; i<bship_custom; i++){
        do{
            cout<<"Inserire coordinata prua e poppa cannoniera "<<i+1<<endl;
			cin>>bow>>stern;
        	bship=Battleship(bow, stern);
        	if(p.addShip(bow, stern, bship)){
        		done=true;
        		cout<<"cannoniera "<<i+1<<" aggiunta"<<endl;
        	}else{
            	cout<<"coordinate non valide"<<endl;
            }
        }while(!done);    
    }
    ship = gen_coordinate(3);
    Support sship(ship.first, ship.second);
    for(int i = 0; i < sship_custom; i++){
        do{
          	cout<<"Inserire coordinata prua e poppa nave da supporto "<<i+1<<endl;
			cin>>bow>>stern;
         	sship=Support (bow, stern);
			if(p.addShip(bow, stern, sship)){
        		done=true;
        		cout<<"nave da supporto "<<i+1<<" aggiunta"<<endl;
        	}else{
            	cout<<"coordinate non valide"<<endl;
            	done=false;
            }
        }while(!done);
    }
	ship = gen_coordinate(1);
   	Submarine eship(ship.first, ship.second);
    for(int i = 0; i< eship_custom; i++){
        do{
        	cout<<"inserire coordinata sottomarino "<<i+1<<endl;
        	cin>>bow;
        	stern=bow;
            eship=Submarine (bow, stern);
            if(p.addShip(bow, stern, eship)){
        		done=true;
        		cout<<"sottomarino "<<i+1<<" aggiunto"<<endl;
        	}else{
            	cout<<"coordinate non valide"<<endl;
            }
        }while(!done);
    }
}


void playerTurn(Player& p1, Player& p2){
   	string origin, target;
   	char move;
   	bool done=false;
	do{    
		cout<<"inserire coordinate per azione di turno (XYOrigin XYTarget)"<<endl;
		cin>>origin>>target;
		if(p1.getDefenceGrid().getTile(origin)==' '){
			cout<<"coordinate di origine non valide, nessuna nave presente, inserire nuove coordinate"<<endl;
			cin>>origin;
		}
	}while(p1.getDefenceGrid().getTile(origin)==' ');
	move=p1.getDefenceGrid().getTile(origin);
	cout<<"move: "<<move<<endl;
	switch(move){
		case 'C':
			cout<<"i'm here"<<endl;
			done=p1.shot(p1.getShip(origin), target, p2);
			break;
		case 'S':
			do{
				done=p1.move_heal(p1.getShip(origin), target);
				if(!done){
					cout<<"coordinate non valide"<<endl;
					cout<<"inserire nuova coordinata destinazione valida occupata"<<endl;
					cin>>target;
				}
			}while(!done);
			break;
		case 'E':
			do{
				done=p1.move_scan(p1.getShip(origin), target, p2);
				if(!done){
					cout<<"coordinate non valide"<<endl;
					cout<<"inserire nuova coordinata destinazione valida non occupata"<<endl;
					cin>>target;
				}
			}while(!done);
		break;		    		
	}
}

void playerVsplayer(Player& p1, Player& p2){
	int coin=rand()%2;
	cout<<p1.getUsername()<<" inserire le proprie navi"<<endl;
    insertShips(p1);
    cout<<p2.getUsername()<<" inserire le proprie navi"<<endl;
    insertShips(p2);
    cout<<"griglie di "<< p1.getUsername()<<endl;
    cout<<p1<<endl;
    cout<<"griglie di "<< p2.getUsername()<<endl;
    cout<<p2<<endl;
    if(coin==0){
    	for(int i = 1; i <= turn_custom; i++){
    		cout<<"TURNO "<<i<<endl;
    		cout<<p1.getUsername()<<" è il tuo turno"<<endl;
    		playerTurn(p1,p2);
    		cout<<"griglie di "<<p1.getUsername()<<endl<<endl;
			cout<<p1<<endl<<endl;
			cout<<p2.getUsername()<<" è il tuo turno"<<endl;
    		playerTurn(p2,p1);
    		cout<<"griglie di "<<p2.getUsername()<<endl<<endl;
			cout<<p2<<endl<<endl;
    	}
    }else{
    	for(int i = 1; i <= turn_custom; i++){
    	cout<<"TURNO "<<i<<endl;
    	cout<<p2.getUsername()<<" è il tuo turno"<<endl;
		playerTurn(p2,p1);
		cout<<"griglie di "<<p2.getUsername()<<endl<<endl;
		cout<<p2<<endl<<endl;
		cout<<p1.getUsername()<<" è il tuo turno"<<endl;
		playerTurn(p1,p2);
		cout<<"griglie di "<<p1.getUsername()<<endl<<endl;
		cout<<p1<<endl<<endl;
    	}
    }
}
