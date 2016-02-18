
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

	GameObject(Vector3 pos, Vector3 vel, float s) {
		position = pos;
		size = s;

		velocity = vel;
	}


};

