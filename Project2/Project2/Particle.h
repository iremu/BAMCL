#pragma once
#include <iostream>
using namespace std;

//Defines the particles of the particle filter

class Particle
{
private:
	//state variables
	int id;
	int x, y; //x and y coordinates 
	double heading_angle; //heading or bearing angle of the particle which is the angle between x coordinate 
	
	//weight of the particle
	double weight;

public:
	//Constructors
	Particle();
	Particle(int,int,int,double,double);
	
	//Deconstructor
	virtual ~Particle();
	
	//Set Values to particle
	void setParticleState(int, int, double, double);
	void setX(int x_);
	void setY(int y_);
	void setAngle(int theta);
	void setWeight(int w);
	void setID(int);

	//Return variables
	int getX();
	int getY();
	double getAngle();
	double getWeight();
	int getID();
};

