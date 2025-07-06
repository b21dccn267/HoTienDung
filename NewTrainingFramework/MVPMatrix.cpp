#include "stdafx.h"
#include "MVPMatrix.h"
#include "../Utilities/Math.h"

// this function calculates all matrices
// all values of any matrix like translate scale rotate and the like are flex
int MVPMatrix::Init()
{
	GLfloat fScale = 0.5f;
	GLfloat rotateAngle = 45.0f;
	GLfloat translationX = 0;
	GLfloat translationY = 0;
	GLfloat translationZ = 0;

	Matrix temp;
	Matrix translationInverse;
	Matrix rotationInverse;

	Vector3 xAxis, yAxis, zAxis; // 
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 position = Vector3(0.0f, 0.0f, 0.0f); // the camera
	Vector3 target = Vector3(3.0f, 3.0f, 3.0f);   // where camera looks at

	GLfloat fov = 45.0f;
	GLfloat aspectRatio = 4.0f / 3.0f;
	GLfloat nearPlane = 0.01f;
	GLfloat farPlane = 100.0f;

	// to calculate world, start with identity, then scale, rotate, translate
	world.SetIdentity();
	world.SetScale(fScale);
	world.SetRotationX(rotateAngle);
	world.SetTranslation(translationX, translationY, translationZ);

	// to calculate view, find x,y,z and their xyzaxis, or inverse translation * i rotation * i scale
	view.SetZero();
	view.SetIdentity();
	translationInverse.SetIdentity();
	translationInverse.SetTranslation(-position.x, -position.y, -position.z);

	rotationInverse.SetIdentity();
	zAxis = (position - target).Normalize();
	xAxis = (up.Cross(zAxis)).Normalize();
	yAxis = zAxis.Cross(xAxis).Normalize();
	rotationInverse.m[0][0] = xAxis.x; rotationInverse.m[0][1] = yAxis.x; rotationInverse.m[0][2] = zAxis.x;
	rotationInverse.m[1][0] = xAxis.y; rotationInverse.m[1][1] = yAxis.y; rotationInverse.m[1][2] = zAxis.y;
	rotationInverse.m[2][0] = xAxis.z; rotationInverse.m[2][1] = yAxis.z; rotationInverse.m[2][2] = zAxis.z;

	view = translationInverse * rotationInverse;

	// to calculate proj, use SetPerspective
	projection.SetZero();
	projection.SetPerspective(fov, aspectRatio, nearPlane, farPlane); //calc fov, 45 = slide value

	matrix = (world * view) * projection;

	return 0;
}