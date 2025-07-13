#pragma once
#include "../Utilities/utilities.h"

// this class represents View in MVP Matrix
// for convenience Camera will output View * Projection
// Camera will be multiplied with WorldMatrix, then with vertexData
// Key event handling will involve:
//		- Check for key presses
//		- Bind key to function calls
//		- Function changes camera class member values
//		- MVP is calculated each frame, so changes are reflected in realtime
class Camera
{
public:
	GLfloat fov;
	GLfloat aspectRatio;
	GLfloat nearPlane;
	GLfloat farPlane;

	GLfloat moveSpeed;
	GLfloat rotateSpeed;

	Vector3 pos;
	Vector3 target;
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	Matrix view;
	Matrix perspective;
	Matrix worldCamera;
	Matrix lookAtCamera;


	int Init();
	void CalculateWorldCameraMatrix();
	void CalculateWiewMatrix();
	void GetPerspectiveMatrix();
};

