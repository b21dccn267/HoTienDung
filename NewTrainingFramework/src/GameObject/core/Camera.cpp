#include "../Utilities/utilities.h"
#include "Camera.h"
#include "Globals.h"


Camera::Camera()
{
	CalculateWiewMatrix();
	CalculatePerspectiveMatrix();
}

// equals rotation * translation, this is the model matrix of camera (no scale)
// quite useless rn
// below code is wrong
void Camera::CalculateWorldCameraMatrix()
{
	Matrix rotation;
	Matrix rotateX, rotateY, rotateZ;
	rotateX.SetRotationX(0.0f);
	rotateY.SetRotationY(0.0f);
	rotateZ.SetRotationZ(0.0f);
	rotation = rotateX * rotateY * rotateZ;

	Matrix translation;
	translation.SetTranslation(0.0f, 0.0f, 0.0f);

	this->m_worldCamera = rotation * translation;
}

// normal view
void Camera::CalculateWiewMatrix()
{
	
	zAxis = (m_cameraPos - m_cameraTarget).Normalize();
	xAxis = (m_cameraUp.Cross(zAxis)).Normalize();
	yAxis = zAxis.Cross(xAxis).Normalize();

	m_viewMatrix.m[0][0] = xAxis.x; m_viewMatrix.m[0][1] = yAxis.x; m_viewMatrix.m[0][2] = zAxis.x; m_viewMatrix.m[0][3] = 0.0f;
	m_viewMatrix.m[1][0] = xAxis.y; m_viewMatrix.m[1][1] = yAxis.y; m_viewMatrix.m[1][2] = zAxis.y; m_viewMatrix.m[1][3] = 0.0f;
	m_viewMatrix.m[2][0] = xAxis.z; m_viewMatrix.m[2][1] = yAxis.z; m_viewMatrix.m[2][2] = zAxis.z; m_viewMatrix.m[2][3] = 0.0f;
	m_viewMatrix.m[3][0] = -m_cameraPos.Dot(xAxis); m_viewMatrix.m[3][1] = -m_cameraPos.Dot(yAxis); m_viewMatrix.m[3][2] = -m_cameraPos.Dot(zAxis); m_viewMatrix.m[3][3] = 1.0f;
}

// now uses ortho
void Camera::CalculatePerspectiveMatrix()
{
	m_perspectiveMatrix.SetOrtho(0.0f, Globals::screenWidth, Globals::screenHeight, 0.0f, -1.0f, 1.0f);
}
