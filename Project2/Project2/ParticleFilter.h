#include <iostream>
#include <vector>
#include "Particle.h"
#include "ObservedObject.h"
#include "FloorMap.h"

using namespace std;
#pragma once

//Class to define elements and functions of particle filter for monte carlo localization

class ParticleFilter:public Particle, public FloorMap
{
	// Number of particles to draw
	int num_particles;
	
	// Flag, if filter is initialized
	bool is_initialized;

	// Vector of weights of all particles
	vector<double> weights;


public:
	
	// Set of current particles
	vector<Particle> particles;

	// Constructor
	// @param M Number of particles
	ParticleFilter() : num_particles(0), is_initialized(false) {}

	// Destructor
	~ParticleFilter() {}
	   
    /* initialized Returns whether particle filter is initialized yet or not.*/
	const bool initialized() const {
		return is_initialized;
	}


	//!!!!!PROBLEM HOW TO ESTIMATE THOSE FROM A FLOOR PLAN????????????
	/*
	* init Initializes particle filter by initializing particles to Gaussian
	*   distribution around first position and all the weights to 1.
	* @param x Initial x position [m] 
	* @param y Initial y position [m]
	* @param theta Initial orientation [rad]
	* @param std[] Array of dimension 3 [standard deviation of x [m], standard deviation of y [m]
	*   standard deviation of yaw [rad]]
	*/
	void init(float x, float y, double theta, double std[]);

	/**
	* prediction Predicts the state for the next time step
	* @param delta_t Time between time step t and t+1 in measurements [s]
	* @param std_pos[] Array of dimension 3 [standard deviation of x [m], standard deviation of y [m]
	*   standard deviation of yaw [rad]]
	* @param velocity Velocity of person from t to t+1 [m/s]
	* @param yaw_rate Yaw rate of person from t to t+1 [rad/s]
	*/
	void prediction(double delta_t, double std_pos[], double velocity, double yaw_rate);

	/**
	* dataAssociation Finds which observations correspond to which landmarks (likely by using
	*   a nearest-neighbors data association).
	* @param predicted Vector of predicted landmark observations
	* @param observations Vector of landmark observations
	*/
	void dataAssociation(std::vector<ObservedObject> predicted, std::vector<ObservedObject>& objectObservations);

	/**
	* updateWeights Updates the weights for each particle based on the likelihood of the
	*   observed measurements.
	* @param sensor_range Range [m] of sensor
	* @param std_landmark[] Array of dimension 2 [standard deviation of range [m],
	*   standard deviation of bearing [rad]]
	* @param observations Vector of landmark observations
	* @param map Map class containing map landmarks
	*/
	void updateWeights(double std_landmark[], std::vector<ObservedObject> objectObservations);

	/**
	* resample Resamples from the updated set of particles to form
	*   the new set of particles.
	*/
	void resample();

	/*
	* write Writes particle positions to a file.
	* @param filename File to write particle positions to.
	*/
	void write(std::string filename);

};

