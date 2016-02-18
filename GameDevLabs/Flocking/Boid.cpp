#include "stdafx.h"
#include "Vector3.h"
#include <iostream>
#include "Boid.h"

Boid::Boid() {}

Boid::Boid(Vector3 pos, Vector3 vel) {
	position = pos;
	velocity = vel;
	separation_distance = 2.5f;
	max_speed = 1.0f;
	mass = 10;
}

Vector3 Boid::separate(std::vector<Boid> boids_list) {
	Vector3 steer_s(0, 0, 0);
	/*int n = 0;
	for (unsigned j = 0; j < boids_list.size(); j++) {
			float distance = position.distance(boids_list[j].position);
			if ((distance > 0) && (distance < separation_distance)) {
				Vector3 vector_diff = position - boids_list[j].position;
				vector_diff.normalise();
				vector_diff = vector_diff / distance;
				steer_s = steer_s + vector_diff;
				n++;
				std::cout << "n-added" << std::endl;
			}
		}
		if (n > 0) {
			steer_s = steer_s / (float)n;
			steer_s.normalise();
			steer_s = steer_s*max_speed;
			steer_s = steer_s - velocity;
		}

		return steer_s;
		//std::cout << "steer ----" << steer.x << "," << steer.y << std::endl;
		//std::cout << "n = " << n << std::endl;
		//this->velocity = this->velocity + steer_s;
		//this->position = this->position + this->velocity*deltaTime;*/
	int n = 0;
	for (unsigned i = 0; i < boids_list.size(); i++) {
		float distance = position.distance(boids_list[i].position);
		
		if ((distance > 0)&&(distance<separation_distance)) {
			steer_s.x = steer_s.x - (boids_list[i].position.x - this->position.x);
			steer_s.y = steer_s.y - (boids_list[i].position.y - this->position.y);
			n++;
		}
	}
	steer_s = steer_s * 0.8;
		return steer_s;
	}

Vector3 Boid::cohesion(std::vector<Boid> boids_list) {
	Vector3 steer_c(0, 0, 0);
	//int n = 0;
	for (unsigned i = 0; i < boids_list.size(); i++) {
		float distance = position.distance(boids_list[i].position);
		if (distance > 0) {
			steer_c =steer_c + boids_list[i].position;
			//n++;
		}
		//if(n>0){}
		steer_c = steer_c - this->position;
		
	}
	return steer_c;
}

Vector3 Boid::alignment(std::vector<Boid> boids_list) {
	Vector3 steer_a(0, 0, 0);
	for (unsigned i = 0; i < boids_list.size(); i++) {
		float distance = position.distance(boids_list[i].position);
		if (distance > 0) {
			steer_a = steer_a + boids_list[i].velocity;
		}
	}
	steer_a = steer_a / (boids_list.size() - 1);
	steer_a = steer_a - this->velocity;
	steer_a = steer_a * 0.08f;
	return steer_a;
}

void Boid::updatePosition(std::vector<Boid> boids_list, float deltaTime)
{
	Vector3 c, s, a;
	for (unsigned i = 0; i < boids_list.size(); i++) {
		s = separate(boids_list);
		c = cohesion(boids_list);
		a = alignment(boids_list);
		std::cout << "UPDATING POS" << std::endl;
		std::cout << "cohesion vector" << c.x<<","<<c.y <<std::endl;
		std::cout << "separation vector" << s.x << "," << s.y << std::endl;
		std::cout << "alignment vector" << a.x << "," << a.y << std::endl;

		this->velocity = (this->velocity + c + s + a);
		this->position = this->position + this->velocity*deltaTime;
	}
}
