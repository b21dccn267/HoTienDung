#include "stdafx.h"
#include "ResourceManager.h"
#include <string>
#include <sstream>
#include <fstream>

ResourceManager* ResourceManager::instance = nullptr;

// this function read the txt file
void ResourceManager::LoadFileRM(const char* fileName)
{
	std::ifstream file(fileName);
	if (!file) { 
		return;
	}

	int i_modelCount = -1;
	int i_textureCount = -1;
	int i_shaderCount = -1;

	// make space for m_models vector, so that adding new stuff dont void all mem addr
	std::string line;
	std::getline(file, line);

	std::istringstream filter;
	filter.str(line);
	std::string trash;
	filter >> trash >> i_modelCount;

	m_models.reserve(i_modelCount);

	// read model in txt file
	for (int i = 0; i < i_modelCount; i++) {
		std::getline(file, line); // skip ID line
		std::getline(file, line);

		filter.clear();
		filter.str(line);
		std::string s_path;

		filter >> trash >> s_path;
		s_path = s_path.substr(1, s_path.size() - 2);
		const char* modelFileName = s_path.c_str();

		Model* tempModel = new Model(modelFileName);
		//Model* tempModel = new Model;
		//tempModel->Init(modelFileName);
		//tempModel->SetModelParameters();
		//tempModel->BindBuffer();
		m_models.emplace_back(tempModel);
	}

	// make space for m_textures
	filter.clear();
	std::getline(file, line);
	filter.str(line);
	filter >> trash >> i_textureCount;

	m_textures.reserve(i_textureCount);

	// read texture
	for (int i = 0; i < i_textureCount; i++) {
		std::getline(file, line); // skip ID line
		std::getline(file, line);

		filter.clear();
		filter.str(line);
		std::string s_path;

		filter >> trash >> s_path;
		s_path = s_path.substr(1, s_path.size() - 2);
		const char* textureFileName = s_path.c_str();
		// read TILING
		std::getline(file, line);
		filter.clear();
		filter.str(line);
		std::string param; // either CLAMP or REPEAT

		filter >> trash >> param;
		int i_param = -1;
		if (param == "CLAMP") {
			i_param = 1;
		}
		Texture* tempTexture = new Texture(textureFileName, i_param);
		//Texture* tempTexture = new Texture;
		//tempTexture->Init(textureFileName);
		//tempTexture->SetTextureParameters(i_param);
		m_textures.emplace_back(tempTexture);
	}

	// make space for m_shaders
	filter.clear();
	std::getline(file, line);
	filter.str(line);
	filter >> trash >> i_shaderCount;

	m_shaders.reserve(i_shaderCount);

	// read shaders
	// is different
	for (int i = 0; i < i_shaderCount; i++) {
		std::getline(file, line); // skip ID line

		std::getline(file, line);
		filter.clear();
		filter.str(line);
		std::string s_path;
		filter >> trash >> s_path; // VS
		s_path = s_path.substr(1, s_path.size() - 2);
		char* vertexShaderFileName = &s_path[0];

		std::getline(file, line);
		filter.clear();
		filter.str(line);
		std::string s_path1;
		filter >> trash >> s_path1; // FS
		s_path1 = s_path1.substr(1, s_path1.size() - 2);
		char* fragmentShaderFileName = &s_path1[0];

		Shaders* tempShader = new Shaders;
		tempShader->Init(vertexShaderFileName, fragmentShaderFileName);
		m_shaders.emplace_back(tempShader);
	}
}

Model* ResourceManager::GetModel(int Id)
{
	return m_models[Id];
}

Texture* ResourceManager::GetTexture(int Id)
{
	return m_textures[Id];
}

Shaders* ResourceManager::GetShader(int Id)
{
	return m_shaders[Id];
}

