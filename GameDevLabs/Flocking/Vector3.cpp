// GameDevLabs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector3.h"
#include "math.h"

#define PI 3.14159265

Vector3::Vector3() {}
Vector3::Vector3(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

const Vector3 Vector3::up = Vector3(0.0, 1.0, 0.0);
const Vector3 Vector3::down = Vector3(0.0, -1.0, 0.0);
const Vector3 Vector3::left = Vector3(-1.0, 0.0, 0.0);
const Vector3 Vector3::right = Vector3(1.0, 0.0, 0.0);

bool Vector3::operator==(Vector3 b) {
	return (x == b.x && y == b.y && z == b.z);
}

Vector3 Vector3::operator+(Vector3 b) {
	return Vector3(x + b.x, y + b.y, z + b.z);
}

Vector3 Vector3::operator-(Vector3 b) {
	return Vector3(x - b.x, y - b.y, z - b.z);
}

Vector3 Vector3::operator*(Vector3 b) {
	return Vector3(x*b.x, y*b.y, z*b.z);
}

Vector3 Vector3::operator/(Vector3 b) {
	return Vector3(x / b.x, y / b.y, z / b.z);
}

Vector3 Vector3::operator+(float scalar) {
	return Vector3(x + scalar, y + scalar, z + scalar);
}

Vector3 Vector3::operator-(float scalar) {
	return Vector3(x - scalar, y - scalar, z - scalar);
}

Vector3 Vector3::operator*(float scalar) {
	return Vector3(x*scalar, y*scalar, z*scalar);
}

Vector3 Vector3::operator/(float scalar) {
	return Vector3(x / scalar, y / scalar, z / scalar);
}

float Vector3::dot(Vector3 b) {
	return (x*b.x + y*b.y + z*b.z);
}

Vector3 Vector3::cross(Vector3 b) {
	return Vector3(y*b.z - z*b.y, z*b.x - x* b.z, x*b.y - y*b.x);
}

float Vector3::length() {
	return float(sqrt(x*x + y*y + z*z));
}

Vector3 Vector3::normalise() {
	Vector3 normalised(0.0, 0.0, 0.0);
	float length = Vector3::length();
	if (length != 0.0) {
		normalised = Vector3(x / length, y / length, z / length);
	}
	return normalised;
}

float Vector3::distance(Vector3 b) {
	return float(sqrt(((x - b.x)*(x - b.x)) + ((y - b.y)*(y - b.y))+((z-b.z)*(z-b.z))));
}

float Vector3::angle(Vector3 b) {
	float dot = this->dot(b);
	float det = this->x*b.y - this->y*b.x;
	float angl = atan2(det, dot)*180/PI;
	return angl;

}
