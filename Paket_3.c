#include "../src/Movement.h"
void findWall(), backAway(), turn(int), dropPackage(), goStraight(), goAcross();
int main(void)
{
	init();
	Wait(SEC_2);
	findWall(); //Find wall

	turn(180);
	goAcross();
	findWall();

	turn(90); //Turn 90 degrees right
	goStraight(); //Travel a predetermined length

	findWall(); //Finds wall
	dropPackage(); //Drops of package
	backAway();
	turn(-90); //Turn 90 degrees left

	goStraight(); //Travel back the same length

	findWall();
	turn(180);
	goAcross();

	findWall();

	return 0;
}
