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

	std::vector<std::shared_ptr<Object>> m_objects;
	Camera* camera; // made public please

	int LoadFileSM(const char* fileName);
	void Cleanup();
private:
	SceneManager() {}; // private constructor
};

