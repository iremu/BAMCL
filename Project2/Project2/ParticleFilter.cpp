#include <random>
#include <algorithm>
#include <iostream>
#include <numeric>
#include "corecrt_math_defines.h"

#include "ParticleFilter.h"
#include "ObservedObject.h"
#include "MapObject.h"
#include "FloorMap.h"

#define INIT_PARTICLE_NO=729

/*
This is the class for particle filter.
*/
ParticleFilter::ParticleFilter()
{
}

ParticleFilter::~ParticleFilter()
{
}
using namespace std;

// @ PROBLEM!!!!!!!!!x,y,theta estimation problem
// Set the number of particles. Initialize all particles to first position (based on estimates of
//  x, y, theta and their uncertainties from some estimation?) and all weights to 1. 
// Add random Gaussian noise to each particle.
// NOTE: Consult particle_filter.h for more information about this method (and others in this file).
void ParticleFilter::init(double x, double y, double theta, double std[]) {
	
	num_particles = INIT_PARTICLE_NO; //set to number of files in observation directory

	weights.resize(num_particles);
	particles.resize(num_particles);

	double std_x, std_y, std_theta; // Standard deviations for x, y, and theta
	std_x = std[0];
	std_y = std[1];
	std_theta = std[2];

    // Normal distribution for x, y and theta
	normal_distribution<double> dist_x(x, std_x); // mean is centered around the new measurement
	normal_distribution<double> dist_y(y, std_y);
	normal_distribution<double> dist_theta(theta, std_theta);

	//this is a random number engine class that generates pseudo - random numbers.
	default_random_engine random_val_gen; 

    // create particles and set their values
	for (int i = 0; i<num_particles; ++i) {
		//create a particle
		Particle p;
		//set particle id
		p.setID(i);
		// take a random value from the Gaussian Normal distribution and update the attribute
		//x, y, thetha, weight
		p.setParticleState(dist_x(random_val_gen), dist_y(random_val_gen), dist_theta(random_val_gen), 1);
		//add particle to the list of particles
		particles[i] = p;
		//add weight of the particle to the list of particles
		weights[i] = p.getWeight();
	}
	is_initialized = true;
}

// Add measurements to each particle and add random Gaussian noise.
// NOTE: When adding noise you may find std::normal_distribution and std::default_random_engine useful.

void ParticleFilter::prediction(double delta_t, double std_pos[], double velocity, double yaw_rate) {

	double std_x, std_y, std_theta; // Standard deviations for x, y, and theta
	std_x = std_pos[0];
	std_y = std_pos[1];
	std_theta = std_pos[2];

	default_random_engine gen;

	for (int i = 0; i<num_particles; ++i) {

		Particle *p = &particles[i]; // get address of particle to update									 
	   
		//yaw rate= angular velocity
		
		// new x= x + (velocity/w)*sin(theta)+ (w*delta_t)-sin(theta)
		// new y= y + (velocity/w)*cos(theta)- (w*delta_t)
		double new_x = p->getX() + (velocity / yaw_rate) * (sin(p->getAngle()) + yaw_rate * delta_t) - sin(p->getAngle());
		double new_y = p->getY() + (velocity / yaw_rate) * (cos(p->getAngle()) - cos(p->getAngle() + yaw_rate * delta_t));
		double new_theta = p->getAngle() + (yaw_rate*delta_t);

		// add Gaussian Noise to each measurement
		// Normal distribution for x, y and theta
		normal_distribution<double> dist_x(new_x, std_x);
		normal_distribution<double> dist_y(new_y, std_y);
		normal_distribution<double> dist_theta(new_theta, std_theta);

		// update the particle attributes
		p->setX(dist_x(gen));
		p->setY= (dist_y(gen));
		p->setAngle = (dist_theta(gen));
	}
}



// Find the predicted measurement that is closest to each observed measurement and assign the
//   observed measurement to this particular landmark.
// it is useful to implement this method and use it as a helper during the updateWeights phase.
//@@@PROBLEM !!!!!! I have to turn it to a function which uses differences of angles 
void ParticleFilter::dataAssociation(std::vector<ObservedObject> predictedObjects, std::vector<ObservedObject>& objectObservations) {
	
	// Find the predicted measurement that is closest to each observed measurement and assign the
    //   observed measurement to this particular landmark.
	
	//iterate through predictions
	for (auto pred : predictedObjects) {
		
		double dist_min = std::numeric_limits<double>::max();
		
		//match it with the closest distanced observation
		for (auto observation : objectObservations) {
			double distance = dist(observation.getX(), 
				observation.getY(), pred.getX(), pred.getY()); // distance b/w obs and landmark
			
			if (distance < dist_min) {
				observation.setID = pred.getID; //Set predictions ID to observation
			}
			dist_min = distance;
		}
	}
}

//@This needs to change for angle comparison as well

//  Update the weights of each particle using a multi - variate Gaussian distribution.
//   NOTE: The observations are given in the agent's coordinate system. Your particles are located
//   according to the MAP'S coordinate system.
void ParticleFilter::updateWeights(double std_landmark[],
	std::vector<ObservedObject> objectObservations) {

	double std_x = std_landmark[0]; //Standard deviation of x
	double std_y = std_landmark[1]; //standard deviation of y
	double weights_sum = 0;  

	for (int i = 0; i<num_particles; ++i) {
		Particle *p = &particles[i];
		double wt = 1.0;

		// convert observed object from agent's reference frame to map's coordinate system
		for (int j = 0; j<objectObservations.size(); ++j) {
			ObservedObject current_obs = objectObservations[j];
			ObservedObject transformed_obs;

			//http://planning.cs.uiuc.edu/node99.html if one needs to consult, equation 33.3
			//x*cos(theta)-y*sin(theta)+ xt
			float x = (current_obs.getX()*cos(p->getAngle())) - (current_obs.getY()*sin(p->getAngle())) + p->getX();
			
			//x*sin(theta)+y*cos(theta)+ yt
			float y=  (current_obs.getX()*sin(p->getAngle())) + (current_obs.getY()*cos(p->getAngle())) + p->getY();

			transformed_obs.setCoordinates(x, y, current_obs.getAngle());
			transformed_obs.setID(current_obs.getID());
			transformed_obs.setType(current_obs.getType);
			transformed_obs.setConfidence(current_obs.getConfidence());
	   //--------------------

	   // find the predicted measurement that is closest to each observed measurement and assign
	   // the observed measurement to this particular landmark
		
			FloorMap floorMap;   //define the object to be able to call list of the objects on the map
			MapObject mapObject; //the landmark we are looking for on the map.

			double distance_min = std::numeric_limits<double>::max();

			//iterate through the objects on the map
			for (int k = 0; k< floorMap.mapLandmarkList.size(); ++k) {
				
				MapObject realMapObject = floorMap.mapLandmarkList[k];

				double distance = dist(transformed_obs.getX(), transformed_obs.getY(), 
					realMapObject.getX(), realMapObject.getY());
				
				//find the one landmark on the map with the least distance to the our measurement
			   if (distance < distance_min) {
					distance_min = distance;
					mapObject = realMapObject; 
				}
			}

			//Update weights using Multivariate Gaussian Distribution
			//Formula for two dimensional gaussian function. "mapObject" is the center.
			//transformed_obs and stds are the spreads of the blob.
			double num = exp(-0.5 * (pow((transformed_obs.getX() - mapObject.getX()),2) /
				pow(std_x, 2) + pow((transformed_obs.getY() - mapObject.getY()), 2) / pow(std_y, 2)));
			
			//volume under the curve. We devide the gaussian function to the volume under the curve to
			//normalize it and make it equal to 1 in the end.
			double denom = 2 * M_PI * std_x * std_y;
			
			//wt=1.0 at this point, now it will change
			wt *= num / denom;
		}
		weights_sum += wt;
		p->setWeight(wt);
	}
	// normalize weights to bring them in (0, 1]
	for (int i = 0; i < num_particles; i++) {
		Particle *p = &particles[i];
		p->getWeight() /= weights_sum;
		weights[i] = p->getWeight();
	}
}

void ParticleFilter::resample() {
	// Resample particles with replacement with probability proportional to their weight.
	//   http://en.cppreference.com/w/cpp/numeric/random/discrete_distribution
	/*std::discrete_distribution produces random integers on the interval[0, n),
	where the probability of each individual integer i is defined as w
	i / S, that is the weight of the ith integer divided by the sum of all n weights.
	*/

	default_random_engine gen;
	discrete_distribution<int> distribution(weights.begin(), weights.end());
	vector<Particle> resampled_particles;

	for (int i = 0; i < num_particles; i++) {
		resampled_particles.push_back(particles[distribution(gen)]);
	}

	particles = resampled_particles;

}

//Euclidean Distance Function
inline float dist(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void ParticleFilter::write(std::string filename) {
	// You don't need to modify this file.
	std::ofstream dataFile;
	dataFile.open(filename, std::ios::app);
	for (int i = 0; i < num_particles; ++i) {
		dataFile << particles[i].x << " " << particles[i].y << " " << particles[i].theta << "\n";
	}
	dataFile.close();
}