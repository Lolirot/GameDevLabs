


#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H
#endif
#include "Vector3.h"


class Particle {

	//public:
	//	LinkedList* vertices;

	//	GameObject::GameObject(LinkedList* vert) : vertices(vert) {}

public:
	Vector3 position;
	Vector3 velocity;
	//Vector3 acceleration;
	float lifespan;

	Particle() {}
	Particle(Vector3, Vector3, float);
	bool isAlive();
	//void Particle::run(Vector3);
};


