


#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H
#endif
#include "Vector3.h"


class Particle {

public:
	Vector3 position;
	Vector3 velocity;
	float lifespan;

	Particle() {}
	Particle(Vector3, Vector3, float);
	bool isAlive();
};


