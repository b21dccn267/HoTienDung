#pragma once
#include "Model.h"
#include "Object.h"

// this class manages all objects of scene
// this class along with ResourceManager are singleton class:
// private constructor + getInstance class to access obj
class SceneManager
{
public:
	SceneManager(const SceneManager& instance) = delete; // no constructor for instance
	static SceneManager* instance;
	static SceneManager* getInstance() { // assign instance to variable
		static SceneManager* instance = new SceneManager();
		return instance;
	}

	Object* m_objects ;
	//Model m_cameras;

	int LoadFileSM(const char* fileName);
	int LoadObject();
	//int LoadCamera();
	
	void Draw();	// calls objects' Draw()
	void Update();	// this one is left empty for now
	void Cleanup();
private:
	SceneManager(); // private constructor
};

