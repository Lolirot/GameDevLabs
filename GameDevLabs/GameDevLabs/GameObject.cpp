
#include "stdafx.h"
#include "Vector3.h"
#include "LinkedList.cpp"

class GameObject {

//public:
//	LinkedList* vertices;

//	GameObject::GameObject(LinkedList* vert) : vertices(vert) {}

public:
	Vector3 position;
	Vector3 velocity;
	int size;
	int falling = 0;
	GameObject() {}

	GameObject(float a, float b, float c, float s, float vx, float vy, float vz) {
		position.x = a;
		position.y = b;
		position.z = c;
		size = s;

		velocity.x = vx;
		velocity.y = vy;
		velocity.z = vz;
	}


};

