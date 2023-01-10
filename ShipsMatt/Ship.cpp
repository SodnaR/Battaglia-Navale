#include "Ship.h"
void Ship::locateCenter(std::vector<int> bow, std::vector<int> stern){
	if(bow[0]==stern[0]){
		center[0]=bow[0];
		center[1]=bow[1]+(dim/2);
		rotation=0;
	}else if(bow[1]==stern[1]){
		center[0]=bow[0]+(dim/2);
		center[1]=bow[1];
		rotation=1;
	}
}
