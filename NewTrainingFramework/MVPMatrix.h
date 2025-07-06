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

	int Init();
};