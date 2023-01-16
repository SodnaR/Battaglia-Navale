#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include "headers/player.h"
using namespace std;

/*Compilatore
*   g++ -o test mainGame.cpp charts/chart.cpp charts/attack_chart.cpp charts/defense_chart.cpp player/player.cpp ships/ship.cpp ships/battleship.cpp ships/support.cpp ships/submarine.cpp
*
*/

pair<string,string> createXY(int dim){
	char start='a';
	char random_alpha;
	int random_y;
	int random_rotation=rand()%2;
	string t1, t2;
	srand(time(0));
	if(random_rotation==1){
		do{
			random_alpha=start+rand()%12;
			random_y=rand()%12+1;
			if(random_alpha=='j'||random_alpha=='k'){
				random_alpha+=3;
			}
			t1=random_alpha+to_string(random_y);
			t2=random_alpha+to_string(random_y+(dim-1));
		}while((random_y+(dim-1)>12));
	}else{
		do{
			random_alpha=start+rand()%12;
			random_y=rand()%12+1;
			if(random_alpha=='j'||random_alpha=='k'){
				random_alpha+=3;
			}
			t1=random_alpha+to_string(random_y);
			t2=(random_alpha+(dim-1));
			t2+=to_string(random_y);
		}while((random_alpha+(dim-1))>'l');
	}
	return make_pair(t1,t2);
}

bool playTurn(int turncount)
Player botVsbot(Player p1,Player p2, int turncount){
	pair<string,string>t=createXY(5);
	bool created=true;
	bool endturn=false;
	int random_action;
	Battleship bs1(t.first, t.second);
	created=p1.addShip(t.first, t.second, bs1);
	cout<<"bs1 created"<<endl;
	do{
		t=createXY(5);
		Battleship bs2(t.first, t.second);
		created=p1.addShip(t.first, t.second, bs2);
		cout<<"bs2 "<<created<<endl;
		if(created){
			cout<<"bs2 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(5);
		Battleship bs3(t.first, t.second);
		created=p1.addShip(t.first, t.second, bs3);
		cout<<"bs3 "<<created<<endl;
		if(created){
			cout<<"bs3 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss1(t.first, t.second);
		created=p1.addShip(t.first, t.second, ss1);
		cout<<"ss1 "<<created<<endl;
		if(created){
			cout<<"ss1 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss2(t.first, t.second);
		created=p1.addShip(t.first, t.second, ss2);
		cout<<"ss2 "<<created<<endl;
		if(created){
			cout<<"ss2 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss3(t.first, t.second);
		created=p1.addShip(t.first, t.second, ss3);
		cout<<"ss3 "<<created<<endl;
		if(created){
			cout<<"ss3 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(1);
		Submarine sb1(t.first, t.second);
		created=p1.addShip(t.first, t.second, sb1);
		cout<<"sb1 "<<created<<endl;
		if(created){
			cout<<"sb1 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(1);
		Submarine sb2(t.first, t.second);
		created=p1.addShip(t.first, t.second, sb2);
		cout<<"sb2 "<<created<<endl;
		if(created){
			cout<<"sb2 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	cout<<p1<<endl;
	Battleship bs4(t.first, t.second);
	created=p2.addShip(t.first, t.second, bs4);
	cout<<"bs1 created"<<endl;
	do{
		t=createXY(5);
		Battleship bs5(t.first, t.second);
		created=p2.addShip(t.first, t.second, bs5);
		cout<<"bs2 "<<created<<endl;
		if(created){
			cout<<"bs2 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(5);
		Battleship bs6(t.first, t.second);
		created=p2.addShip(t.first, t.second, bs6);
		cout<<"bs3 "<<created<<endl;
		if(created){
			cout<<"bs3 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss4(t.first, t.second);
		created=p2.addShip(t.first, t.second, ss4);
		cout<<"ss1 "<<created<<endl;
		if(created){
			cout<<"ss1 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss5(t.first, t.second);
		created=p2.addShip(t.first, t.second, ss5);
		cout<<"ss2 "<<created<<endl;
		if(created){
			cout<<"ss2 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(3);
		Support ss6(t.first, t.second);
		created=p1.addShip(t.first, t.second, ss6);
		cout<<"ss3 "<<created<<endl;
		if(created){
			cout<<"ss3 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(1);
		Submarine sb3(t.first, t.second);
		created=p2.addShip(t.first, t.second, sb3);
		cout<<"sb1 "<<created<<endl;
		if(created){
			cout<<"sb1 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	do{
		t=createXY(1);
		Submarine sb4(t.first, t.second);
		created=p1.addShip(t.first, t.second, sb4);
		cout<<"sb2 "<<created<<endl;
		if(created){
			cout<<"sb2 created"<<endl;
		}
	}while(created==false);
	cout<<t.first<<" "<<t.second<<endl;
	cout<<p2<<endl;
	do{
		
	}while(endturn==false);
	/*Battleship bs1(s1.first, s1.second), bs2(s2.first, s2.second), bs3(s3.first, s3.second), bs4(s4.first, s4.second);
    Support    ss1(s5.first, s5.second), ss2(s6.first, s6.second), ss3(s7.first, s7.second), ss4(s8.first, s8.second);
    Submarine  es1(s9.first, s9.second), es2(s0.first, s0.second);
	*/
	return p1;
}

Player playerVsplayer(Player p1, Player p2){
	int coin=rand()%2;
	if(coin==0){
		cout<<p1.getUsername()<<" inizia"<<endl;
	}else{
		cout<<p2.getUsername()<<" inizia"<<endl;
	}
	return p1;
}


int main(){
    Player winner, p1, p2;
    int players;
    string username;
	int turncount=10;
    std::cout << "Benvenuti: prego inserire il numero di giocatori [Max 2]: ";
    cin >> players;
    std::cout <<flush; //flush forces the printing to the screen before it pauses
    //system("clear");

    switch (players)
    {
    case 0:
        winner = botVsbot(p1, p2,turncount);
        cout<<"player 1 vince"<<endl;
        break;
    case 1:
        std::cout << "Inserire il proprio username: ";
        cin >> username;
        p1.setUsername(username);
        std::cout << p1.getUsername() << std::endl;
       // winner = playerVsbot(p1, p2);
        break;
    case 2:
        std::cout << "Player 1 - Inserire il proprio username: ";
        cin >> username;
        p1.setUsername(username);
        std::cout << endl << "Player 2 - Inserire il proprio username: ";
        cin >> username;
        p2.setUsername(username);
        std::cout << p1.getUsername() << p2.getUsername() << std::endl;
       // winner = playerVsplayer(p1, p2);
        break;
    }
    return 0;
}
