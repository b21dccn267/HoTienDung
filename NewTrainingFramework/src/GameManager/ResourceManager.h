#pragma once
#include "Model.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include <vector>
#include <memory>

// this class loads all game assets
class ResourceManager
{
public:
	ResourceManager(const ResourceManager& instance) = delete;
	static ResourceManager* instance;
	static ResourceManager* getInstance() {
		if (!instance)
		{
			instance = new ResourceManager();
		}
		return instance;
	}

	std::vector<std::shared_ptr<Model>>		m_models;
	std::vector<std::shared_ptr<Texture>>	m_textures;
	std::vector<std::shared_ptr<Shaders>>	m_shaders;

	void LoadFileRM(const char* fileName);

	std::shared_ptr<Model>   GetModel(int Id);
	std::shared_ptr<Texture> GetTexture(int Id);
	std::shared_ptr<Shaders> GetShader(int Id);

private:
	ResourceManager() {};
};

