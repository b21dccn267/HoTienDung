#pragma once
#include "../Utilities/utilities.h"

// this class calculates view and projection (part of mvp)
// WorldCamera is not used yet, but still
// Key event handling will involve:
//		- Check for key presses
//		- Bind key to function calls
//		- Function changes camera class member values
//		- MVP is calculated each frame, so changes are reflected in realtime
class Camera
{
public:
	Vector3 xAxis, yAxis, zAxis;
	Camera();
	GLfloat fov = 45.0f;
	GLfloat aspectRatio = 4.0f / 3.0f;
	GLfloat nearPlane = 0.01f;
	GLfloat farPlane = 100.0f;

	GLfloat moveSpeed = 0.3f;
	GLfloat rotateSpeed;

	Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 target = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	Matrix view;
	Matrix perspectiveMatrix;
	Matrix worldCamera;
	Matrix lookAtCamera; //view*projection, and what should be multiplied to object world/model matrix


	void CalculateWorldCameraMatrix();
	void CalculateWiewMatrix();
	void GetPerspectiveMatrix();
	Matrix LookAt();
};

