#include "stdafx.h"
#include "Vector3.h"
#include "Particle.h"
#include <iostream>


Particle::Particle(Vector3 pos, Vector3 vel, float life) {
	position = pos;
	velocity = vel;
	lifespan = life;
}

bool Particle::isAlive() {
	if (lifespan <= 0.0) return false;
	else return true;
}

/*void Particle::run(Vector3 acceleration) {
	position = position + velocity + acceleration;
}*/



