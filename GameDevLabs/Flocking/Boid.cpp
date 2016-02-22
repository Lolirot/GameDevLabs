#include "stdafx.h"
#include "Vector3.h"
#include <iostream>
#include "Boid.h"

Boid::Boid() {}

Boid::Boid(Vector3 pos, Vector3 vel, float speed) {
	position = pos;
	velocity = vel;
	this->speed = speed;
	angle = 0.0f;
}

Vector3 Boid::separate(std::vector<Boid> neighbours) {
	Vector3 steer_s(0.0, 0.0, 0.0);
	float desired_sep = 0.2f;
	for (unsigned i = 0; i < neighbours.size(); i++) {
		float distance = position.distance(neighbours[i].position);
		if (distance < desired_sep) {
			float diff_x = neighbours[i].position.x - this->position.x;
			float diff_y = neighbours[i].position.y - this->position.y;
			
			Vector3 diff_v(diff_x, diff_y, 0.0);
			if (diff_v.x != 0 && diff_v.y != 0) {
				diff_v = diff_v / distance;
			}
			diff_v = diff_v.normalise();
			steer_s = steer_s - diff_v;
		}
	}

	steer_s = steer_s / ((float)(neighbours.size()));
	
	steer_s = steer_s.normalise();
	return steer_s;
}

Vector3 Boid::cohesion(std::vector<Boid> neighbourhood) {
	Vector3 steer_c(0.0, 0.0, 0.0);

	for (unsigned i = 0; i < neighbourhood.size(); i++) {
		steer_c = steer_c + neighbourhood[i].position;
	}
	steer_c = steer_c / ((float)(neighbourhood.size()));
	steer_c = steer_c - position;
	return steer_c;
}

Vector3 Boid::alignment(std::vector<Boid> neighbourhood) {
	Vector3 steer_a(0.0, 0.0, 0.0);

	for (unsigned i = 0; i < neighbourhood.size(); i++) {
			steer_a = steer_a + neighbourhood[i].velocity;
		}
	steer_a = steer_a / ((float)(neighbourhood.size()));
	steer_a = steer_a.normalise();

		return steer_a;
	}

void Boid::updatePosition(std::vector<Boid> neighbourhood, float deltaTime){
	
	if (neighbourhood.size() == 0) {
		position = position + velocity*deltaTime;
	}
	else {
		Vector3 separation, cohesion, alignment;

		separation = Boid::separate(neighbourhood);
		cohesion = Boid::cohesion(neighbourhood);
		alignment = Boid::alignment(neighbourhood);		
		
		this->velocity = this->velocity + separation*separation_coeff + cohesion*cohesion_coeff + alignment*alignment_coeff;

		this->velocity = this->velocity.normalise();
		this->velocity = this->velocity * speed;
		lastPos = this->position;
		this->position = this->position + (this->velocity * deltaTime);
		float newAngle = ((this->position-lastPos).normalise()).angle(Vector3::up);
		if(angle != newAngle) {
			this->angle = newAngle - this->angle;
		}
		if (position.x < -1.0f) { position.x = 1.0f; }
		else if (position.x > 1.0f) position.x = -1.0f;
		if (position.y < -1.0f) position.y = 1.0f;
		else if (position.y > 1.0f) position.y = -1.0f;
	}
	
}