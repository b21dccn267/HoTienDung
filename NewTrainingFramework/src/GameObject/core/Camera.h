#pragma once
#include "../Utilities/utilities.h"

// this class calculates:
// WorldCamera, which is used for putting camera to world space aka for moving camera
// View and Projection matrices, to calculate WVP matrix
class Camera
{
public:
	Vector3 xAxis, yAxis, zAxis;
	
	GLfloat fov = 45.0f;
	GLfloat aspectRatio = 4.0f / 3.0f;
	GLfloat nearPlane = 0.01f;
	GLfloat farPlane = 100.0f;

	GLfloat moveSpeed = 0.3f;
	GLfloat rotateSpeed;

	Vector3 m_cameraPos = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_cameraTarget = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 m_cameraUp = Vector3(0.0f, 1.0f, 0.0f);

	Matrix m_viewMatrix;
	Matrix m_perspectiveMatrix;
	Matrix m_worldCamera;

	Camera();
	void CalculateWorldCameraMatrix();
	void CalculateWiewMatrix();
	void CalculatePerspectiveMatrix();
};

