#include "MapObject.h"

MapObject::MapObject()
{

}

MapObject::~MapObject()
{
}
void MapObject::setCoordinates(float x_, float y_)
{
	x = x;
	y = y;
	
}
void MapObject::setType(string object_type)
{
	type = object_type;
}
void MapObject::setID(int num)
{
	id = num;
}

void MapObject::getCoordinates(float& x_, float & y_)
{
	x_ = x;
	y_ = y;
}

float MapObject::getX()
{
	return x;
}

float MapObject::getY()
{
	return y;
}
string MapObject::getType()
{
	return type;
}

int MapObject::getID(void)
{
	return id;
}