#pragma once
#include "../GameObject/core/Model.h"
#include "../GameObject/core/Texture.h"
#include "../GameObject/core/Shaders.h"
#include "../../../Utilities/utilities.h"
#include "../GameObject/core/Vertex.h"
#include <vector>
#include <memory>

// this class loads all game assets
class ResourceManager
{
public:
	ResourceManager(const ResourceManager& instance) = delete;
	static ResourceManager* instance;
	static ResourceManager* GetInstance() {
		if (!instance)
		{
			instance = new ResourceManager();
		}
		return instance;
	}
	static void DestroyInstance() {
		delete instance;
		instance = nullptr;
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

