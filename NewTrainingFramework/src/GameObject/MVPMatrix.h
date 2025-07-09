#pragma once
#include "../Utilities/Math.h"

// this struct calculates MVPMatrix as World * View * Projection
class MVPMatrix
{
public:
	Matrix matrix;

	Matrix world;
	Matrix view;
	Matrix projection;

	GLfloat mvpLine[16]; // transform mvp matrix into 1d array for feeding

	int Init();
	void MatrixToArray();

};