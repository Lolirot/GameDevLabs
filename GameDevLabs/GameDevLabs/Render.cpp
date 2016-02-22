
// Includes
#include "stdafx.h" 
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GameObject.h"
#include <D:\GLUT\glut.h>
#include <algorithm>
#define GL_GLEXT_PROTOTYPES
#ifndef __APPLE__
#endif

#define GRAVITY 9.8

int w_height = 800;
int w_width = 800; 
float limit_vertical = 0.7;
float limit_horizontal = 0.7;

Vector3 sphere_position(0.1, 0.7, 0.5);
Vector3 sphere_velocity(0.1, 3, 0);

GameObject sphere(sphere_position, sphere_velocity, 0);
int lastElapsed = 0;
float deltaTime = 0;

void timerTick() {
	int curr = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (curr - lastElapsed) * 0.001;
	lastElapsed = curr;
}

void reshape(int width, int height) {
	w_width = width;
	w_height = height;
}


void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glBegin(GL_LINE_LOOP); // Draw Platforms
	glVertex3d(0.8, -0.8, 0.5);
	glVertex3d(0.8, 0.8, 0.5);
	glVertex3d(-0.8, 0.8, 0.5);
	glVertex3d(-0.8, -0.8, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3d(-2.0, 0.1, 0.5); // Draw Bars
	glVertex3d(-2.0, 0.3, 0.5);
	glVertex3d(-1.2, 0.3, 0.5);
	glVertex3d(-1.2, 0.1, 0.5);

	glEnd();

	glPushMatrix();
	glTranslated(sphere.position.x, sphere.position.y, sphere.position.z);
	glRotatef(90, sphere.position.x, 0.0, 0.0);
	glutWireSphere(0.1, 15, 15);
	
	glPopMatrix();

	glFlush();
	glutSwapBuffers();	
}

void idle() {
	timerTick();
	sphere.fall(GRAVITY, deltaTime);
	display();

}

void specialKeys(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
		sphere.falling = 0;
	}

	if (key == GLUT_KEY_DOWN) {
	sphere.falling = 1;
}
	//  Request display update
	glutPostRedisplay();

}

int main(int argc, char** argv)
{
	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	//glutInitWindowPosition(10, 10);
	glutInitWindowSize(w_width, w_height);
	glutCreateWindow("Awesome Cube");
	

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	// Callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialKeys);
	glutIdleFunc(idle);
	// Enter main event loop
	glutMainLoop();
	return 0;
}
