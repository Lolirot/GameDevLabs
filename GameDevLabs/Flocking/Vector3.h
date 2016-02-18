#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
public:
	Vector3();
	Vector3(float, float, float);
	bool operator==(Vector3 b);
	Vector3 operator+(Vector3 b);
	Vector3 operator-(Vector3 b);
	Vector3 operator*(Vector3 b);
	Vector3 operator/(Vector3 b);
	Vector3 operator+(float scalar);
	Vector3 operator-(float scalar);
	Vector3 operator*(float scalar);
	Vector3 operator/(float scalar);
	Vector3 cross(Vector3 b);
	Vector3 normalise();
	float Vector3::distance(Vector3);
	float dot(Vector3 b);
	float length();
	float x;
	float y;
	float z;
};


#endif
