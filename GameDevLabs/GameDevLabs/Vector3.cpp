// GameDevLabs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector3.h"
#include "math.h"


bool Vector3::operator==(Vector3 b) {
	return (x == b.x && y == b.y && z == b.z);
}

Vector3 Vector3::operator+(Vector3 b) {
	return Vector3(x + b.x, y + b.y, z + b.z);
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
	float length = Vector3::length();
	Vector3 normalised = Vector3(x / length, y / length, z / length);
	return normalised;
}
