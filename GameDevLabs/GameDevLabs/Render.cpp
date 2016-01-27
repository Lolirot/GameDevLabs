
// Includes
#include <stdio.h>
#include <stdarg.h>
#include "stdafx.h" 
#include <stdlib.h>
#include <math.h>
#include "Vector3.h"
#include "GameObject.cpp"
#include <D:\GLUT\glut.h>
#define GL_GLEXT_PROTOTYPES
#ifndef __APPLE__
#endif

#define GRAVITY 2

void display();
void specialKeys();

int w_height = 800;
int w_width = 800; 

double rotate_y = 0;
double rotate_x = 0;

float limit_vertical = 0.7;
float limit_horizontal = 0.7;

GameObject sphere(0.1, 0.7, 0.5, 0.1, 3, 0, 0);
//GameObject sphere_b(-0.1, -0.7, 0.5, 0.1);
GameObject plain;
int lastElapsed = 0;
float deltaTime = 0;

void timerTick() {
	int curr = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (curr - lastElapsed) * 0.001;
	cout << "delta: " << deltaTime<<"\n";
	lastElapsed = curr;
}

void reshape(int width, int height) {
	w_width = width;
	w_height = height;
}



void fall() {
	if (sphere.falling == 1) {
		
		//cout << "falling\n";
		sphere.velocity.y -= GRAVITY*deltaTime;
		sphere.position = sphere.position + sphere.velocity*deltaTime;
		if (sphere.velocity.y > 20) {
			sphere.velocity.y = 20;
		}
	}
}

void checkBoundsCollision() {
	if (sphere.position.x >= limit_horizontal) sphere.velocity.x = -abs(sphere.velocity.x);
	if (sphere.position.x <= -limit_horizontal) sphere.velocity.x = abs(sphere.velocity.x);
	if (sphere.position.y >= limit_vertical) sphere.velocity.y = -abs(sphere.velocity.y);
	if (sphere.position.y <= -limit_vertical) sphere.velocity.y = abs(sphere.velocity.y);
}

bool checkObjectCollision(GameObject a, GameObject b) {
	//check X
	if (abs(a.position.x - b.position.x) < (a.size) / 2 + (b.size) / 2) {
		//check Y
		if (abs(a.position.y - b.position.y) < (a.size) / 2 + (b.size) / 2) {
			//check Z
			if (abs(a.position.z - b.position.z) < (a.size) / 2 + (b.size) / 2) {
				return true;
			}
			return true;
		}
		return true;
	}
	else return false;
}

void idle() {
	timerTick();
	fall();
	checkBoundsCollision();
	display();

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Rotate when user changes rotate_x and rotate_y
	//glRotatef(rotate_x, 1.0, 0.0, 0.0);
	//glRotatef(rotate_y, 0.0, 1.0, 0.0);

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

void specialKeys(int key, int x, int y) {

	//  Right arrow - increase rotation by 5 degree
	/*if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	*/if (key == GLUT_KEY_UP) {
		sphere.falling = 0;
		cout << "STOPPED\n";
	}

	if (key == GLUT_KEY_DOWN) {
	sphere.falling = 1;
	//cout << "falling";
}
	//rotate_x -= 5;

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

	// Set clear color to black and clear window 
	

	// Enter main event loop
	glutMainLoop();
	return 0;
}
