#pragma once
#include "Vector3.h"
#include "stdafx.h"
#include <vector>

class Boid {
public:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	float speed;
	float separation_coeff = 0.5f;
	float cohesion_coeff = 0.3f;
	float alignment_coeff = 0.3f;
	float angle;
	Vector3 lastPos;

	Boid::Boid();
	Boid::Boid(Vector3, Vector3, float);
	Vector3 Boid::separate(std::vector<Boid>);
	Vector3 Boid::cohesion(std::vector<Boid>);
	Vector3 Boid::alignment(std::vector<Boid>);
	void Boid::updatePosition(std::vector<Boid>, float);


};