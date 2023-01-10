#ifndef SHIP_H
#define SHIP_H

class Ship{
	protected:
		int dim;
		int armor;
		bool alive=true;
		std::vector<int> center(2);
		int rotation; //orientazione nave 0=orizzontale, 1 verticale
	public:
		int getArmor(){return armor;}
		int getRotation(){ return rotation;}
		bool isAlive(){return alive;}
		virtual void move()=0;
		void locateCenter();
		void hit(){armor=armor-1;}
		void sink(){if(armor==0) alive=false;}
		void setArmor(int a);
		class Invalid{};
};

#endif
