#ifndef SHIP_H
#define SHIP_H

class Ship{
	protected:
		int dim;
		int armor;
		bool alive=true;
		std::vector<int> center(2);
		int orien; //orientazione nave 0=orizzontale, 1 verticale
	public:
		int getArmor(){return armor;}
		bool isAlive(){return alive;}
		virtual void move()=0;
		void locateCenter();
		void hit(){armor=armor-1;}
		void sink(){if(armor==0) alive=false;}
		class Invalid{};
};

#endif
