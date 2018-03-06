#include "Particle.h"

//Empty constructor
Particle::Particle()
{
	//could be random values i guess
	id = -1;
	x = -1;
	y = -1;
	heading_angle = -1;
	weight = 0.02;
}
//Constructor with initial values
Particle::Particle(int id_, int x_, int y_, double  theta, double weight_)
{
	id = id_;
	x = x_;
	y = y_;
	heading_angle = theta;
	weight = weight_;
}


Particle::~Particle()
{
}

//Set parameters of the particle
void Particle::setParticleState(int x_, int y_, double angle, double weight_)
{
	setX(x_);
	setY(y_);
	setAngle(angle);
	setWeight(weight_);
}

void Particle::setX(int x_)
{
	x = x_;
}
void Particle::setY(int y_)
{
	y = y_;
}
void Particle::setAngle(int theta)
{
	heading_angle = theta;
}
void Particle::setWeight(int w)
{
	weight = w;
}

void Particle::setID(int num)
{
	id = num;
}

//Return x value of the particle
int Particle::getX()
{
	return x;
}

//Return y value of the particle
int Particle::getY()
{
	return y;
}
int

//Return heading angle of the particle
double Particle::getAngle()
{
	return heading_angle;
}

//Return heading angle of the particle
double  Particle::getWeight()
{
	return weight;
}
int Particle::getID()
{
	return id;

}