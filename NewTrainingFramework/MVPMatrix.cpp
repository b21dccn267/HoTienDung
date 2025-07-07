#include "stdafx.h"
#include "MVPMatrix.h"
#include "../Utilities/Math.h"

// this function calculates all matrices
// all values of any matrix like translate scale rotate and the like are flex
int MVPMatrix::Init()
{
	GLfloat fScale = 1.0f;
	GLfloat rotateAngle = 0.0f; 
	GLfloat translationX = 0.0f;
	GLfloat translationY = 0.0f;
	GLfloat translationZ = 0.0f;

	Matrix temp;
	Matrix translationInverse;
	Matrix rotationInverse;

	Vector3 xAxis, yAxis, zAxis; // 
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 position = Vector3(0.0f, 0.0f, -1.0f);	// the camera
	Vector3 target = Vector3(0.0f, 0.0f, 0.0f);		// where camera looks at

	GLfloat fov = 45.0f;
	GLfloat aspectRatio = 4.0f / 3.0f;
	GLfloat nearPlane = 0.01f;
	GLfloat farPlane = 100.0f;


	// calculate world
	world.SetIdentity();

	Matrix scale, rotation, translation;
	scale.SetScale(fScale);
	rotation.SetRotationX(rotateAngle);
	translation.SetTranslation(translationX, translationY, translationZ);

	world = scale * rotation * translation;


	// calculate view
	view.SetIdentity();

	zAxis = (position - target).Normalize();
	xAxis = (up.Cross(zAxis)).Normalize();
	yAxis = zAxis.Cross(xAxis).Normalize();

	view.m[0][0] = xAxis.x; view.m[0][1] = yAxis.x; view.m[0][2] = zAxis.x; view.m[0][3] = 0.0f;
	view.m[1][0] = xAxis.y; view.m[1][1] = yAxis.y; view.m[1][2] = zAxis.y; view.m[1][3] = 0.0f;
	view.m[2][0] = xAxis.z; view.m[2][1] = yAxis.z; view.m[2][2] = zAxis.z; view.m[2][3] = 0.0f;
	view.m[3][0] = -position.Dot(xAxis); view.m[3][1] = -position.Dot(yAxis); view.m[3][2] = -position.Dot(zAxis); view.m[3][3] = 1.0f;


	// calculate projection
	projection.SetPerspective(fov, aspectRatio, nearPlane, farPlane);
	//projection = projection.Transpose();

	matrix = world * view * projection;

	return 0;
}