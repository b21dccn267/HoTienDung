#pragma once
#include "../Utilities/utilities.h"

class Camera
{
public:
	GLfloat fov;
	GLfloat aspectRatio;
	GLfloat nearPlane;
	GLfloat farPlane;

	Vector3 pos;
	Vector3 target;
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	Matrix view;
	Matrix perspective;
	Matrix worldCamera;
	Matrix lookAtCamera;



	int Init();
	void Calculate();
};

