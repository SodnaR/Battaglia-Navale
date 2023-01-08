#ifndef SUBMARINE_H
#define SUBMARINE_H

class Submarine: public Ship{
	public:
		Submarine Submarine(int x, int y);
		void move(int x, int y, Griglia d);
		void scan (Griglia d, Griglia a);
};
#endif
