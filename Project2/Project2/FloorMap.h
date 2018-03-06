#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "MapObject.h"

using namespace std;

class FloorMap
{

public:
	const vector<MapObject> mapLandmarkList; // List of landmarks in the map
	FloorMap();
	~FloorMap();
	
};

