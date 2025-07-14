#include "stdafx.h"
#include "Camera.h"
#include "../Utilities/utilities.h"


// equals rotation * translation, this is the model matrix of camera (no scale)
// quite useless rn
void Camera::CalculateWorldCameraMatrix()
{
	//GLfloat rotateAngleX = 0.0f;
	//GLfloat rotateAngleY = 0.0f;
	//GLfloat rotateAngleZ = 0.0f;

	Matrix rotation;
	Matrix rotateX, rotateY, rotateZ;
	rotateX.SetRotationX(0.0f);
	rotateY.SetRotationY(0.0f);
	rotateZ.SetRotationZ(0.0f);
	rotation = rotateX * rotateY * rotateZ;

	Matrix translation;
	translation.SetTranslation(0.0f, 0.0f, 0.0f);

	this->worldCamera = rotation * translation;
}

// normal view
void Camera::CalculateWiewMatrix()
{
	Vector3 xAxis, yAxis, zAxis;
	zAxis = (pos - target).Normalize();
	xAxis = (up.Cross(zAxis)).Normalize();
	yAxis = zAxis.Cross(xAxis).Normalize();

	view.m[0][0] = xAxis.x; view.m[0][1] = yAxis.x; view.m[0][2] = zAxis.x; view.m[0][3] = 0.0f;
	view.m[1][0] = xAxis.y; view.m[1][1] = yAxis.y; view.m[1][2] = zAxis.y; view.m[1][3] = 0.0f;
	view.m[2][0] = xAxis.z; view.m[2][1] = yAxis.z; view.m[2][2] = zAxis.z; view.m[2][3] = 0.0f;
	view.m[3][0] = -pos.Dot(xAxis); view.m[3][1] = -pos.Dot(yAxis); view.m[3][2] = -pos.Dot(zAxis); view.m[3][3] = 1.0f;
}

// normal projection
void Camera::GetPerspectiveMatrix()
{
	perspectiveMatrix.SetPerspective(fov, aspectRatio, nearPlane, farPlane);
}