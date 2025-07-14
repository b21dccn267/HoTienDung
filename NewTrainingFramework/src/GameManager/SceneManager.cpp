#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <string>
#include <sstream>
#include <fstream>

SceneManager* SceneManager::instance = nullptr;

int SceneManager::LoadFileSM(const char* fileName)
{
	int ModelID = -1, TextureID = -1, ShaderID = -1, MatrixID = -1;
	Vector3 pos, rotation, scale;

	int i_objCount = -1;
	std::ifstream file(fileName);
	if (!file) { 
		return -1; 
	}

	std::string line;
	std::getline(file, line);

	std::istringstream filter;
	filter.str(line);
	std::string trash;
	filter >> trash >> i_objCount;

	m_objects.reserve(i_objCount);

	for (int i = 0; i < i_objCount; i++) {
		std::getline(file, line); // empty line
		std::getline(file, line); // skip id

		std::getline(file, line);
		filter.clear();
		filter.str(line);
		filter >> trash >> ModelID;

		std::getline(file, line);
		filter.clear();
		filter.str(line);
		filter >> trash >> TextureID;

		std::getline(file, line);
		filter.clear();
		filter.str(line);
		filter >> trash >> ShaderID;

		std::getline(file, line);
		filter.clear();
		filter.str(line);
		filter >> trash >> pos.x >> pos.y >> pos.z;

		std::getline(file, line);
		filter.clear();
		filter.str(line);
		filter >> trash >> rotation.x >> rotation.y >> rotation.z;

		std::getline(file, line);
		filter.clear();
		filter.str(line);
		filter >> trash >> scale.x >> scale.y >> scale.z;

		
		m_objects.emplace_back(new Object(
			ResourceManager::getInstance()->GetModel(ModelID),
			ResourceManager::getInstance()->GetTexture(TextureID),
			ResourceManager::getInstance()->GetShader(ShaderID),
			pos, rotation, scale
		));
	}

	//instance->camera = new Camera;
	camera = new Camera();
	camera->pos = pos;
	camera->target = Vector3(0.0f, 0.0f, 0.0f);

	return 0;
}

int SceneManager::LoadObject()
{
	//m_objects->Init(m_objects->model, m_objects->texture, m_objects->shader, m_objects->matrix);
	return 0;
}

void SceneManager::Draw()
{
	camera->CalculateWiewMatrix();
	camera->GetPerspectiveMatrix();

	m_objects[0]->Draw(SceneManager::getInstance()->camera);
}

void SceneManager::Update()
{
	//m_objects[0]->Update();
	// put camera here
}

void SceneManager::HandleKeyEvent(unsigned char key)
{
	switch (key) {
	case 0x31: // 1
		SceneManager::getInstance()->camera;
	}
}

void SceneManager::Cleanup()
{
	delete instance;
}