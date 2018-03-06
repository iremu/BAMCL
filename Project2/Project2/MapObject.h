#include <iostream>
#include <string>
#include <vector>
using namespace std;

//This is the class to define objects located on the map already.
//Those objects already exist on the floor plan. The members are not detections.

class MapObject
{
	//The protected members are also the members of the 
	// child class object.
	protected:
	//object id
	int id;

	//Coordinates of the object
	float x, y;

	//type of the object
	string type;

public:
	MapObject(); 
	
	MapObject(int,float,float,string);

	~MapObject();

	void setCoordinates(float x_, float y_);
	
	void setType(string object_type);
	
	void setID(int num);

	void getCoordinates(float& x_, float& y_);

	string getType();

	int getID(void);

	float getX();

	float getY();
};

