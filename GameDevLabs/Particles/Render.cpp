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
#define GL_GLEXT_PROTOTYPES
#ifndef __APPLE__
#endif

#define MAX_SIZE 200

//std::vector<Particle> particles(MAX_SIZE);
//Particle particles[MAX_SIZE];
std::vector<Particle> particles;
Vector3 initPos(0, 0, 0);

int window_height = 800;
int window_width = 800;

int lastElapsedTime = 0;
float dTime = 0;

void draw() {

}

float RandomFloat(float min, float max) {
	return  (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
}

void timerTick() {
	int curr = glutGet(GLUT_ELAPSED_TIME);
	dTime = (curr - lastElapsedTime) * 0.001;
	//cout << "delta: " << deltaTime << "\n";
	lastElapsedTime = curr;
}

void populate() {
	for (int i = 0; i <= MAX_SIZE - particles.size(); i++) {
		
		/*std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(0.5, 1.0); // guaranteed unbiased

		auto vx = uni(rng);
		auto vy = uni(rng);
		std::cout << "vx = " << vx << std::endl;
		std::cout << "vy = " << vy << std::endl;
		std::cout << "-------------------------------------" << std::endl;
		*/
		float vx = RandomFloat(-1.0, 1.0);
		float vy = RandomFloat(-1.0, 1.0);
		float lifespan = RandomFloat(0.5, 2);
		//particles[i] = Particle(initPos, Vector3(vx,vy, 0), 0.5);
		Particle *new_particle = new Particle(initPos, Vector3(vx, vy, 0), lifespan);
		particles.push_back(*new_particle);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	for (unsigned j = 0; j < particles.size(); j++) {
		glPushMatrix();
		glTranslated(particles[j].position.x, particles[j].position.y, particles[j].position.z);
		glBegin(GL_TRIANGLES);
		glClearColor(0.1f, 0.03f, 0.6f, 1.0f);
		glVertex3f(0.01f, 0.0f, 0.0f);
		glVertex3f(0.03f, 0.01f, 0.0f);
		glVertex3f(0.01f, 0.03f, 0.0f);
		//std::cout << "triangle drawn";
		glEnd();
		//glRotatef(90, particles[j].position.x, particles[j].position.y, 0.0);
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
}

void reposition() {
	int pivot = 0;
	for (unsigned m = 0; m < particles.size(); m++) {
		particles[m].lifespan -= dTime;
		if (particles[m].isAlive() == true) {
			particles[m].position = particles[m].position + particles[m].velocity*dTime;
		}
		else particles.erase(particles.begin() + m - pivot);

		pivot++;
	}
}

void run() {
	timerTick();
	reposition();
	display();

	if (particles.size()<MAX_SIZE) {
		populate();
	}
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



