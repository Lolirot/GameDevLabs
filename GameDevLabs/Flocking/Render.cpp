#include <stdio.h>
#include <stdarg.h>
#include "stdafx.h" 
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "Vector3.h"
#include <D:\GLUT\glut.h>
#include <vector>
#include "Boid.h"
#include <random>
#define GL_GLEXT_PROTOTYPES
#ifndef __APPLE__
#endif
#define MAX_SIZE 4

std::vector<Boid> boids;
Vector3 initPos(0, 0, 0);

int window_height = 800;
int window_width = 800;

int lastElapsedTime = 0;
float dTime = 0;

//generate random float -- used for random positions and velocity when creating boids
float RandomFloat(float min, float max) {
	return  (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
}


//timer function
void timerTick() {
	int curr = glutGet(GLUT_ELAPSED_TIME);
	dTime = (curr - lastElapsedTime) * 0.001;
	lastElapsedTime = curr;
}

//populates vector with boids
void populate() {
	for (int i = 0; i <MAX_SIZE; i++) {
		float vx = RandomFloat(0.0, 1.0);
		float vy = RandomFloat(0.0, 1.0);
		//float lifespan = RandomFloat(0.5, 2);
		//particles[i] = Particle(initPos, Vector3(vx,vy, 0), 0.5);
		std::cout << "new boid" << std::endl;
		boids.push_back(Boid(initPos, Vector3(vx, vy, 0)));
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	for (unsigned j = 0; j < boids.size(); j++) {
		glPushMatrix();
		if (boids[j].position.x < -0.9) boids[j].position.x = 0.9;
		if (boids[j].position.x > 0.9) boids[j].position.x = -0.9;
		if (boids[j].position.y < -0.9) boids[j].position.y = 0.9;
		if (boids[j].position.y > 0.9)boids[j].position.y = -0.9;
		glTranslated(boids[j].position.x, boids[j].position.y, boids[j].position.z);
		glBegin(GL_TRIANGLES);
		glClearColor(0.1f, 0.03f, 0.6f, 1.0f);
		glVertex3f(0.01f, 0.0f, 0.0f);
		glVertex3f(0.03f, 0.01f, 0.0f);
		glVertex3f(0.01f, 0.03f, 0.0f);
		//std::cout << "triangle drawn" << std::endl;
		glEnd();
		//glRotatef(90, particles[j].position.x, particles[j].position.y, 0.0);
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
}

void run() {
	timerTick();
	for (unsigned i = 0; i < boids.size(); i++) {
		boids[i].updatePosition(boids, dTime);
	}
	display();
}


int main(int argc, char** argv)
{
	//  Initialize GLUT and process user parameters
		glutInit(&argc, argv);
	

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	//glutInitWindowPosition(10, 10);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Awesome Cube");


	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);
	populate();
	// Callback functions
	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	//glutSpecialFunc(specialKeys);
	glutIdleFunc(run);

	// Set clear color to black and clear window


	// Enter main event loop
	glutMainLoop();
	return 0;
}

