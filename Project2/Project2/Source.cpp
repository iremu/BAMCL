#include <stdio.h>
#include "engine.h"
#include <ctime>
#include <iomanip>
#include <random>

int main(void) {

	Engine *ep = engOpen(NULL);		// Connect to MATLAB engine
	if (ep == 0) {
		printf("Connecton to Matlab Engine failed\n");
	}
	else {
		printf("Connecton to Matlab Engine succeeded!\n");
		//engEvalString(ep, "x=0:pi/30:2*pi;");
		//engEvalString(ep, "y=sin(3*x);");
		//engEvalString(ep, "plot(x,y);");
	}

	//getchar();		// for demo purposes, pause until user hits a key
	
	//=========Start of the main program for particle filter

	// ~~~~Timer Settings~~~~
	// Start timer.
	int start = clock();
	double delta_t = 0.1; // Time elapsed between measurements [sec]
	
	
	
	
	engClose(ep);
	return(0);
}