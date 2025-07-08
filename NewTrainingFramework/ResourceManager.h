#pragma once
#include "Model.h"

// this class manages all game resources
class ResourceManager
{
public:
	Model m_models;

	int LoadModel();
	int GetModel();
	void ClearModel();

	int LoadTexture();
	int GetTexture();
	void ClearTexture();

	int LoadShader();
	int GetShader();
	void ClearShader();
};

