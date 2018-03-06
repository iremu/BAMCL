#include "ObservedObject.h"

//Definition of object class functions
//The rest of the get and set functions are used from the parent class "MapObject"

//Constructor
ObservedObject::ObservedObject()
{
	id = -1; 
}
ObservedObject::ObservedObject(int id_,float x_,float y_,double angle_, string type_,double confidence_)
{
	//Object information
	id = id_;
	//Type of the object window, door etc.
	type = type_;

	//Coordinates of the object
	x = x_;
	y = y_;
	angle = angle_;

	//confidence level of detection
	confidence=confidence_;
}

//Empty deconstructor
ObservedObject::~ObservedObject()
{

}

//Set methods
void ObservedObject::setCoordinates(float x_, float y_, double angle_)
{
	x = x;
	y = y;
	angle = angle_;
}

void ObservedObject::setConfidence(double confidence_level)
{
	confidence = confidence_level;
}

//Return heading angle of the object
double ObservedObject::getAngle()
{
	return angle;
}

//Return confidence of the detection
double ObservedObject::getConfidence()
{
	return confidence;
}
