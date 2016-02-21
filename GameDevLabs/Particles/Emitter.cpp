
#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>
#include "stdafx.h" 
#include <stdlib.h>
#include <math.h>
#include "Emitter.h"

#include "math.h"

#define MAX_SIZE 200

Particle particles_arr[];

Emitter::Emitter() {}
Emitter::Emitter(Vector3 pos) {
	this->position = pos;
}

float Emitter::RandomFloat(float min, float max) {
	return  (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
}

void Emitter::populate_particles() {
	for (int i = 0; i <= MAX_SIZE - particles.size(); i++) {

		float vx = RandomFloat(-1.0, 1.0);
		float vy = RandomFloat(-1.0, 1.0);
		float lifespan = RandomFloat(0.5, 2);

		Particle *new_particle = new Particle(this->position, Vector3(vx, vy, 0), lifespan);
		particles.push_back(*new_particle);
	}
}

void Emitter::update_particles(float deltaTime) {
	if (particles.size() < MAX_SIZE) {
		populate_particles();
	}
	int pivot = 0;
	for (unsigned m = 0; m < particles.size(); m++) {
		particles[m].lifespan -= deltaTime;
		if (particles[m].isAlive() == true) {
			particles[m].position = particles[m].position + particles[m].velocity*deltaTime;
		}
		else particles.erase(particles.begin() + m - pivot);
		pivot++;
	}
}