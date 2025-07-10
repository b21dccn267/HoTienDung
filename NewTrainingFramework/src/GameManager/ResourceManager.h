#pragma once
#include "Model.h"
#include "Object.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "MVPMatrix.h"
#include <vector>

// this class manages all game resources
class ResourceManager
{
public:
	ResourceManager(const ResourceManager& instance) = delete; // no constructor for instance
	static ResourceManager* instance; // provided singleton version
	static ResourceManager* getInstance() { // assign instance to variable
		if (!instance)
		{
			instance = new ResourceManager();
		}
		return instance;
	}

	std::vector<Model*> m_models;
	std::vector<Texture*> m_textures;
	std::vector<Shaders*> m_shaders;

	//std::vector<char*> m_models;
	//std::vector<char**> m_textures;
	//std::vector<char*> m_shaders;

	void LoadFileRM(const char* fileName);
	Model* GetModel(int Id);
	Texture* GetTexture(int Id);
	Shaders* GetShader(int Id);

private:
	ResourceManager() {};
};

