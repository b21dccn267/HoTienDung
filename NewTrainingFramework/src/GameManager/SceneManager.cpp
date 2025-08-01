
#include "SceneManager.h"
#include "ResourceManager.h"
#include "../GameObject/core/Camera.h"
#include <string>
#include <sstream>
#include <fstream>
#include <memory>

SceneManager* SceneManager::instance = nullptr;

void SceneManager::InitCamera()
{
	camera = std::make_shared<Camera>();
	camera->m_cameraPos = Vector3(0.0f, 0.0f, 0.0f);
	camera->m_cameraTarget = Vector3(0.0f, 0.0f, -1.0f);
}
