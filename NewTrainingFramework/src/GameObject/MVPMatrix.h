#pragma once
#include "../Utilities/Math.h"

// this struct calculates MVPMatrix as World * View * Projection
// this struct should be read only and not be used
class MVPMatrix
{
public:
	GLfloat xScale;
	GLfloat yScale;
	GLfloat zScale;

	GLfloat rotateAngleX;
	GLfloat rotateAngleY;
	GLfloat rotateAngleZ;
	
	GLfloat translationX;
	GLfloat translationY;
	GLfloat translationZ;

	Vector3 xAxis, yAxis, zAxis;
	Vector3 up;
	Vector3 position;	// the camera
	Vector3 target;		// where camera looks at

	GLfloat fov;
	GLfloat aspectRatio;
	GLfloat nearPlane;
	GLfloat farPlane;


	Matrix matrix;

	Matrix world;
	Matrix view;
	Matrix projection;

	GLfloat mvpLine[16]; // transform mvp matrix into 1d array for feeding

	int Init(Vector3 pos, Vector3 rotation, Vector3 scale);
	int Calculate();
	void MatrixToArray();

};