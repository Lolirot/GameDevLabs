#pragma once
#include "Boid.h"
#define MAX_SIZE  20
#define BOID_SIZE 3

class Flock {

public:
	Vector3 initPos;
	std::vector<Boid> flock;
	float boids_speed;
	float neighbourhood_range;

	Flock::Flock();
	Flock::Flock(Vector3);
	float Flock::random_float(float, float);
	void Flock::populate();
	std::vector<Boid> Flock::neighbourhood();
	void Flock::update(float);
	

};