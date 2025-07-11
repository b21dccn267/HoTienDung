#include "stdafx.h"
#include "MVPMatrix.h"
#include "../Utilities/Math.h"

// pos rotation and scale are taken as input
int MVPMatrix::Init(Vector3 pos, Vector3 rotation, Vector3 scale)
{
	xScale = scale.x;
	yScale = scale.y;
	zScale = scale.z;

	rotateAngleX = rotation.x;
	rotateAngleY = rotation.y;
	rotateAngleZ = rotation.z;
	
	translationX = 0.0f;
	translationY = 0.0f;
	translationZ = 0.0f;

	xAxis, yAxis, zAxis;
	up = Vector3(0.0f, 1.0f, 0.0f);
	position = pos;				
	target = Vector3(0.0f, 0.0f, 0.0f);		

	fov = 45.0f;
	aspectRatio = 4.0f / 3.0f;
	nearPlane = 0.01f;
	farPlane = 100.0f;

	return 0;
}

int MVPMatrix::Calculate()
{
	// calculate world
	world.SetIdentity();

	Matrix scale, rotation, translation;
	//scale.SetScale(fScale);
	// use 3 value scale version
	scale.SetScale(xScale, yScale, zScale);
	//rotation.SetRotationX(rotateAngle);
	// add x y z rotations
	Matrix rotateX, rotateY, rotateZ;
	rotateX.SetRotationX(rotateAngleX);
	rotateY.SetRotationY(rotateAngleY);
	rotateZ.SetRotationZ(rotateAngleZ);
	rotation = rotateX * rotateY * rotateZ;
	translation.SetTranslation(translationX, translationY, translationZ);

	world = scale * rotation * translation;


	// calculate view
	view.SetIdentity();

	Vector3 xAxis, yAxis, zAxis;
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

void MVPMatrix::MatrixToArray()
{
	mvpLine[0] = matrix.m[0][0];
	mvpLine[1] = matrix.m[0][1];
	mvpLine[2] = matrix.m[0][2];
	mvpLine[3] = matrix.m[0][3];

	mvpLine[4] = matrix.m[1][0];
	mvpLine[5] = matrix.m[1][1];
	mvpLine[6] = matrix.m[1][2];
	mvpLine[7] = matrix.m[1][3];

	mvpLine[8] = matrix.m[2][0];
	mvpLine[9] = matrix.m[2][1];
	mvpLine[10] = matrix.m[2][2];
	mvpLine[11] = matrix.m[2][3];

	mvpLine[12] = matrix.m[3][0];
	mvpLine[13] = matrix.m[3][1];
	mvpLine[14] = matrix.m[3][2];
	mvpLine[15] = matrix.m[3][3];
}