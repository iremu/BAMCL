#pragma once
#include <iostream>
#include <string>
#include "MapObject.h"

//This class produces members of object observations
// The parent class MapObjects provide the id, type and x,y information
//thorugh its protected members. The additional detection angle and measurement
//confidence attributes are added in this class.

using namespace std;

class ObservedObject: public MapObject
{
private:

	//Angle of the detection
	double angle;

	//confidence of detection
	double confidence;

public:
	//Constructor
	ObservedObject();
	ObservedObject(int id, float x,float y,double angle, string type,double confidence);
	
	//Deconstructor
	~ObservedObject();

	//set methods 
	void setCoordinates(float x_, float y_, double angle_);
	void setConfidence(double confidence_level);
	
	//get methods
	double getAngle();
	double getConfidence();

};

