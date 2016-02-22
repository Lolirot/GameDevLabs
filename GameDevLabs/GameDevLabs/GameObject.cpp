
#include "stdafx.h"
#include "GameObject.h"
#include <algorithm>

	GameObject::GameObject() {}

	GameObject::GameObject(Vector3 pos, Vector3 vel, float s) {
		position = pos;
		size = s;
		falling = 0;
		velocity = vel;
	}

	void GameObject::fall(float gravity,float deltaTime) {
		GameObject::applyForce(gravity, deltaTime);
		//applyfriction(deltaTime);
		checkBoundsCollision(0.7, 0.7);
		if (falling == 1) {
			position = position + velocity*deltaTime;
			if (velocity.y > 20) {
				velocity.y = 20;
			}

			if (position.y < -0.7 && abs(velocity.y) <0.1) {
				velocity.x = 0;
				velocity.y = 0;
				falling = false;
			}
		}
	}
	void GameObject::applyForce(float GRAVITY, float deltaTime) {
		velocity.y -= GRAVITY*deltaTime;
		velocity = velocity.normalise();
	}

	void GameObject::checkBoundsCollision(float limit_horizontal, float limit_vertical) {
		if (position.x >= limit_horizontal) velocity.x = -abs(velocity.x);
		if (position.x <= -limit_horizontal) velocity.x = abs(velocity.x);
		if (position.y >= limit_vertical) velocity.y = -abs(velocity.y);
		if (position.y <= -limit_vertical) velocity.y = abs(velocity.y);
	}
