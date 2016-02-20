#include "stdafx.h"
#include "Flock.h"
#include "Boid.h"
#include <stdio.h>
#include <iostream>

Flock::Flock() {}

Flock::Flock(Vector3 initPos):neighbourhood_range(3) {
	this->initPos = initPos;
}

float Flock::random_float(float min, float max) {
	return  (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
}

void Flock::populate() {
	for (unsigned i = 0; i <= MAX_SIZE; i++) {
		float random_speed = random_float(0.2f, 0.4f);
		Vector3 random_vel = Vector3(random_float(-5.0f, 5.0f), random_float(-5.0f, 5.0f), 0);
		flock.push_back(Boid(initPos, random_vel, random_speed));
	}
}

std::vector<Boid> Flock::neighbourhood() {
	std::vector<Boid> neighbourhood;
	for (unsigned i = 0; i <= MAX_SIZE; i++) {
		for (unsigned j = 0; j < MAX_SIZE; j++) {
			float diff = flock[i].position.distance(flock[j].position);
			if ((i!=j) && ((abs(diff)) < neighbourhood_range))
			{
				neighbourhood.push_back(flock[j]);
			}
		}
	}
	return neighbourhood;
}

//NOTE: Addd wraparound method

void Flock::update(float deltaTime) {
	for (unsigned i = 0; i <= MAX_SIZE; i++) {
		flock[i].updatePosition(Flock::neighbourhood(), deltaTime);
		//flock[i].position = flock[i].position + flock[i].velocity*deltaTime
		
		std::cout << "updating" << flock[i].position.x<<std::endl;
	}
}

