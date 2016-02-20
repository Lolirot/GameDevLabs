#include "stdafx.h"
#include "Vector3.h"
#include <iostream>
#include "Boid.h"

Boid::Boid() {}

Boid::Boid(Vector3 pos, Vector3 vel, float speed) {
	position = pos;
	velocity = vel;
	this->speed = speed;
}

Vector3 Boid::separate(std::vector<Boid> neighbours) {
	Vector3 steer_s(0.0, 0.0, 0.0);
	float desired_sep = 0.1f;
	for (unsigned i = 0; i < neighbours.size(); i++) {
		//steer_s = steer_s - (neighbours[i].position - this->position);
		float distance = position.distance(neighbours[i].position);
		//std::cout << "STEER_SEP X---" << steer_s.x << std::endl;
		if (distance < desired_sep) {
			//Vector3 diff = neighbours[i].position - this->position;
			float diff_x = neighbours[i].position.x - this->position.x;
			float diff_y = neighbours[i].position.y - this->position.y;
			//std::cout << "DIFFERENCE, NORMALISED --->" << diff.x << ", " << diff.y << std::endl;
			//diff = diff.normalise();
			//std::cout << "DIFFERENCE, NORMALISED --->" << diff.x << ", " << diff.y << std::endl;
			
			Vector3 diff_v(diff_x, diff_y, 0.0);
			if (diff_v.x != 0 && diff_v.y != 0) {
				diff_v = diff_v / distance;
			}
			diff_v = diff_v.normalise();
			steer_s = steer_s - diff_v;
		}
	}

	steer_s = steer_s / ((float)(neighbours.size()));
	//std::cout << "STEER_SEP X---" << steer_s.x << std:: endl;
	//std::cout << "STEER_SEP Y----" << steer_s.y << std::endl;
	//steer_s = steer_s.normalise();
	//std::cout << "STEER_SEP X---" << steer_s.x << std::endl;
	//std::cout << "STEER_SEP Y----" << steer_s.y << std::endl;

	//steer_s.x = -(steer_s.x - position.x);
	//steer_s.y = -(steer_s.y - position.y);
	//steer_s = steer_s - position;
	steer_s = steer_s.normalise();
	//std::cout << "steer  -----> " << steer_s.x << ", " << steer_s.y << std::endl;
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

		/*std::cout << "SEPARATION  x-----" << separation.x << std::endl;
		std::cout << "SEPARATION  y-----" << separation.y << std::endl;
		std::cout << "---------------------------------------" << std::endl;
		std::cout << "COHESION  x-----" << cohesion.x << std::endl;
		std::cout << "COHESION  y-----" << cohesion.y << std::endl;
		std::cout << "---------------------------------------" << std::endl;
		std::cout << "ALIGNMENT  x-----" << alignment.x << std::endl;
		std::cout << "ALIGNMENT  y-----" << alignment.y << std::endl;
		std::cout << "---------------------------------------" << std::endl;*/

		
		
		this->velocity = this->velocity + separation*separation_coeff + cohesion*cohesion_coeff + alignment*alignment_coeff;

		this->velocity = this->velocity.normalise();
		this->velocity = this->velocity * speed;
		this->position = this->position + (this->velocity * deltaTime);
		if (position.x < -1.0f) position.x = 1.0f;
		else if (position.x > 1.0f) position.x = -1.0f;
		if (position.y < -1.0f) position.y = 1.0f;
		else if (position.y > 1.0f) position.y = -1.0f;
	}
	
}