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
#include "Flock.h"
#include <SOIL.h>

#define GL_GLEXT_PROTOTYPES
#ifndef __APPLE__
#endif

int window_height = 800;
int window_width = 800;

int lastElapsedTime = 0;
float dTime = 0;



Flock flock(Vector3(0.0, 0.0, 0.0));

void initComponents() {
	flock.populate();
}


void initGraphics() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	//glutInitWindowPosition(10, 10);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Awesome Cube");


	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);
}

/*void initTexture() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glFrontFace(GL_CW);

	GLuint linktex = SOIL_load_OGL_texture(
		"ship.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (0 == linktex)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}*/

void drawSprite( GLuint texture) {
	//Draw clockwise
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_POLYGON);
	glTexCoord2i(1, 1); glVertex3f(0.07, 0.07, 0.0);
	glTexCoord2i(1, 0); glVertex3f(0.07, -0.07, 0.0);
	glTexCoord2i(0, 0); glVertex3f(-0.07, -0.07, 0.0);
	glTexCoord2i(0, 1); glVertex3f(-0.07, 0.07, 0.0);
	glEnd();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glFrontFace(GL_CW);

	GLuint linktex = SOIL_load_OGL_texture(
		"ship.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (0 == linktex)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
	glLoadIdentity();
	for (unsigned i = 0; i < flock.flock.size(); i++) {
		glPushMatrix();
		glTranslated(flock.flock[i].position.x, flock.flock[i].position.y, flock.flock[i].position.z);
		//std::cout << (flock.flock[i].velocity.x) << std::endl;
		//std::cout << (flock.flock[i].velocity.y) << std::endl;
		Vector3 rotation = Vector3(0.0f, 0.0f, 1.0f)*dTime;
		glRotatef(flock.flock[i].angle,rotation.x, rotation.y, rotation.z); //rotate object by 30 degree with respect to y-axis
		//std::cout << flock.flock[i].angle << std::endl;
		//glBegin(GL_POLYGON);
		
		drawSprite(linktex);
		/*glClearColor(0.1f, 0.03f, 0.6f, 1.0f);
		glVertex3f(0.05, 0.05, 0.0);
		glVertex3f(0.05, -0.05, 0.0);
		glVertex3f(-0.05, -0.05, 0.0);
		glVertex3f(-0.05, 0.05, 0.0);*/

		//glEnd();
		//std::cout << "triangle drawn" << std::endl;
		//glRotatef(90, particles[j].position.x, particles[j].position.y, 0.0);
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
}

//timer function
void timerTick() {
	int curr = glutGet(GLUT_ELAPSED_TIME);
	dTime = (curr - lastElapsedTime) * 0.001;
	lastElapsedTime = curr;
}



/*void display() {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
for (unsigned j = 0; j < flock.size(); j++) {
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

/*void run() {
timerTick();
boids[i].updatePosition(boids, dTime);
display();
}*/

void update() {
	timerTick();
	flock.update(dTime);
	render();
}

int main(int argc, char** argv)
{
	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);
	//initTexture();
	initGraphics();
	initComponents();

	// Callback functions
	glutDisplayFunc(render);
	glutIdleFunc(update);
	// Enter main event loop
	glutMainLoop();
	return 0;
}

