#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <stdlib.h>
#include <stdio.h>
#include <ev3.h>
void findWall(), backAway(), turn(int), dropPackage(), goStraight(), goAcross(), init(), end();
void init(){

	InitEV3(); //Declare library function
	setAllSensorMode(GYRO_ANG,NO_SEN,NO_SEN,US_DIST_MM); //set what input corresponds to what sensor
}

void end(){
	FreeEV3(); //Part of library
}
void findWall(){
OnFwdReg(OUT_C,25); //This turns on the motor to go forward with specific speed
OnRevReg(OUT_B,25); //This turns on the motor to go backward with specific speed
	int minDistanceDeg; //Declare a int for distance to wall
	int startDeg = readSensor(IN_1); //Set the start degree of gyro
int minDistance = readSensor(IN_4); //Sets the start min distance as the current sensor distance
	while(startDeg + 360 > readSensor(IN_1)) //While the gyro hasn’t turned 360 degrees checks the sensors
	{
		if (readSensor(IN_4) <= minDistance){  //If the distance to the wall is less than the previous min distance, set a new min distance and the degree for the that distance
			minDistance = readSensor(IN_4);
			minDistanceDeg = readSensor(IN_1);
		}
		Wait(MS_20); //Waits 20ms before checking the sensors again
	}
	Off(OUT_BC); //After it has turn 360 degrees turn of the motors
	turn(minDistanceDeg-readSensor(IN_1)); //Turn to the degree where the distance was shortest

	OnFwdReg(OUT_BC,50); //Turns on both motors to travel forward
	Wait(SEC_5);
	Off(OUT_BC); //Let the motors drive for 5 sec, then turn them off
	backAway();
}

void backAway(){
OnRevReg(OUT_BC, 50); //Starts the motors to travel backwards
Wait(MS_300); // Let the motors drive for 300ms
	while(readSensor(IN_4) < 250 || readSensor(IN_4) == 2550 ) //When sensor distance is  to small, it gives a value of 2550, otherwise travel to a distance more than 250 mm away
	{
		Wait(MS_200);
	}
	Off(OUT_BC); //Turns off the motors
}

void dropPackage() {
	OnRevReg(OUT_A,50); //Turns on the motor that change the angle of the holder
	Wait(SEC_2);
	Off(OUT_A); //After two seconds, turns off the motors

	Wait(SEC_2); //Wait 2 sec to let the package drop off

	OnFwdReg(OUT_A,50); //Turns back the angle of the holder
	Wait(SEC_2);
	Off(OUT_A);
}

void goStraight(){
	int a = readSensor(IN_1); //Sets the start value of  the gyro
	int i;
	for ( i = 0; i < 31 ; i++){
		//Turn to the start degree and drive forward
		if(readSensor(IN_1) != a){
			turn(a-readSensor(IN_1));
		}
		OnFwdReg(OUT_BC, 50); //Start the motors
		Wait(MS_500);
	}
	Off(OUT_BC);
}

void turn(int deg){
	int sensor = readSensor(IN_1); //Get the current gyro degree
	while(abs(readSensor(IN_1)-( sensor + deg))>3) //Turn as long as the desired degree is within 3 degrees marginal, may be lessened
		{
			//LcdPrintf("%d\n", readSensor(IN_1));
			if (readSensor(IN_1) > sensor + deg) //Turns the on axle the shortest way for desired degree
			{
				OnFwdReg(OUT_B,25);
				OnRevReg(OUT_C,25);
			}
			else if (readSensor(IN_1) < sensor + deg)
			{
				OnFwdReg(OUT_C,25);
				OnRevReg(OUT_B,25);
			}
			Wait(MS_100); // Wait 100ms before checking sensor again, may be lessened for higher precision
		}
	Off(OUT_BC); //Turns of the motors
}

void goAcross(){
	int a = readSensor(IN_1);
	while(readSensor(IN_4) > 200)
	{
		if(readSensor(IN_1) != a)
		{
			turn(a-readSensor(IN_1));
		}
		OnFwdReg(OUT_BC, 50);
		Wait(MS_500);
	}
}


#endif /* MOVEMENT_H_ */
