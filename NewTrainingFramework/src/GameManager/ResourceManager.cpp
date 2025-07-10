#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = nullptr;

// this function read the txt file
void ResourceManager::LoadFileRM(const char* fileName)
{
	// fileName = "../Resources/Config/ResourceManager.txt"
	FILE* f = fopen(fileName, "r");

	if (!f) {
		return;
	}
	// what do:
	// read resman txt
	// call asset.init 
	// store res by id
	// 
	char line[200];
	// load model
	//fgets(line, sizeof line, f);
	//while (fgets(line, sizeof line, f) && line[0] != '#') {
	//	sscanf_s("ID %d", NULL);

	//	fgets(line, sizeof line, f);
	//	//char temp[50];
	//	//sscanf_s("FILE \"%s\" ", temp);

	//	//m_models.emplace_back(temp);
	//}

	//// load texture
	////fgets(line, sizeof line, f);
	//while (fgets(line, sizeof line, f) && line[0] != '#') {
	//	sscanf_s("ID %d", NULL);

	//	fgets(line, sizeof line, f);
	//	//char temp[50];
	//	//sscanf_s("FILE \"%s\" ", temp);
	//	//m_textures.emplace_back(temp);

	//	fgets(line, sizeof line, f);
	//	//sscanf_s("TILING \"%s\" ", temp);
	//	// no saving this for now
	//}

	//// load shaders
	////fgets(line, sizeof line, f);
	//while (fgets(line, sizeof line, f) && line[0] != '#') {
	//	sscanf_s("ID %d", NULL);

	//	fgets(line, sizeof line, f);
	//	//char temp[50];
	//	//sscanf_s("FILE \"%s\" ", temp);
	//	//m_shaders.emplace_back(temp);
	//}

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

