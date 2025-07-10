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
	int i_modelCount = -1;
	int i_textureCount = -1;
	int i_shaderCount = -1;

	fgets(line, sizeof line, f);
	sscanf_s(line, "#Model %d", &i_modelCount);
	m_models.reserve(i_modelCount);

	
	while(fgets(line, sizeof line, f)) {
		fgets(line, sizeof line, f); // skip id part xd
		if (sscanf_s(line, "#2DTexture %d", &i_textureCount) == 1) {
			m_textures.reserve(i_textureCount);
			break;
		}
		char* modelFileName = NULL;
		char temp[50];
		/*sscanf_s(line, "FILE \"%s\" ", modelFileName, (unsigned)sizeof(modelFileName));*/
		sscanf_s(line, "FILE \"%s\" ", temp, (unsigned)sizeof(temp));
		modelFileName = _strdup(temp);
		Model* tempModel = new Model();
		tempModel->Init(modelFileName);
		tempModel->SetModelParameters();
		tempModel->BindBuffer();
		m_models.emplace_back(tempModel);
	}

	
	//sscanf_s(line, "#Texture %d", &i_textureCount);
	

	while (fgets(line, sizeof line, f) && !strcmp(line, "#Shader")) {
		fgets(line, sizeof line, f); // skip id part xd

		char* textureFileName;
		char* tiling;
		sscanf_s(line, "FILE \"%s\" ", textureFileName);
		Texture* tempTexture;
		tempTexture->Init(textureFileName);
		m_textures.emplace_back(tempTexture);
	}




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

