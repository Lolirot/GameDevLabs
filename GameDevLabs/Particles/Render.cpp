#include <stdio.h>
#include <stdarg.h>
#include "stdafx.h" 
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "Vector3.h"
#include <D:\GLUT\glut.h>
#include <vector>
#include "Particle.h"
#include <random>
#include "Emitter.h"
#define GL_GLEXT_PROTOTYPES
#ifndef __APPLE__
#endif

Vector3 initPos(0, 0, 0);
Emitter emitter(initPos);
int window_height = 800;
int window_width = 800;

int lastElapsedTime = 0;
float dTime = 0;

void initialise() {
	emitter.populate_particles();
}

void timerTick() {
	int curr = glutGet(GLUT_ELAPSED_TIME);
	dTime = (curr - lastElapsedTime) * 0.001;
	lastElapsedTime = curr;
}


void draw() {
	for (unsigned j = 0; j < emitter.particles.size(); j++) {
		glPushMatrix();
		glTranslated(emitter.particles[j].position.x, emitter.particles[j].position.y, emitter.particles[j].position.z);
		glutSolidSphere(0.01, 15, 15);
		glPopMatrix();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	draw();
	glFlush();
	glutSwapBuffers();
}

void update() {
	timerTick();
	emitter.update_particles(dTime);
	display();
}

int main(int argc, char** argv)
{
glutInit(&argc, argv);

glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

glutInitWindowSize(window_width, window_height);
glutCreateWindow("Particles");

//  Enable Z-buffer depth test
glEnable(GL_DEPTH_TEST);

emitter.populate_particles();
// Callback functions
glutDisplayFunc(display);
//glutReshapeFunc(reshape);
//glutSpecialFunc(specialKeys);
glutIdleFunc(update);
// Enter main event loop
glutMainLoop();
return 0;
}



