#pragma once
#include "Vector3.h"
#include "stdafx.h"
#include <vector>

class Boid {
public:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;


	float max_steering_force;
	float max_speed;
	float separation_distance;
	float angle;
	float mass;

	Boid::Boid();
	Boid::Boid(Vector3, Vector3);
	Vector3 Boid::separate(std::vector<Boid>);
	Vector3 Boid::cohesion(std::vector<Boid>);
	Vector3 Boid::alignment(std::vector<Boid>);
	void Boid::updatePosition(std::vector<Boid>, float);


};