#pragma once
#include "Model.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include <vector>
#include <memory>

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

	//std::vector<Model*> m_models;
	//std::vector<Texture*> m_textures;
	//std::vector<Shaders*> m_shaders;
	std::vector<std::shared_ptr<Model>>		m_models;
	std::vector<std::shared_ptr<Texture>>	m_textures;
	std::vector<std::shared_ptr<Shaders>>	m_shaders;

	void LoadFileRM(const char* fileName);
	//Model* GetModel(int Id);
	//Texture* GetTexture(int Id);
	//Shaders* GetShader(int Id);

	std::shared_ptr<Model>   GetModel(int Id);
	std::shared_ptr<Texture> GetTexture(int Id);
	std::shared_ptr<Shaders> GetShader(int Id);

private:
	ResourceManager() {};
};

