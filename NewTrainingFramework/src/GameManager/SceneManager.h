#pragma once
#include "Model.h"
#include "Object.h"
#include "Camera.h"
#include <vector>
#include <memory>

// this class bundles assets into objects for game states
// as well as enabling Camera access for gs draw
class SceneManager
{
public:
	SceneManager(const SceneManager& instance) = delete;
	static SceneManager* instance;
	static SceneManager* GetInstance() {
		if (!instance)
		{
			instance = new SceneManager();
		}
		return instance;
	}

	static void DestroyInstance() {
		delete instance;
		instance = nullptr;
	}

	std::vector<std::shared_ptr<Object>> m_objects;
	std::shared_ptr<Camera> camera;

	int LoadFileSM(const char* fileName);

private:
	SceneManager() {};
};

