#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{

}

int SceneManager::LoadFileSM()
{
	m_objects->modelFileName = "../Resources/Packs/Models/Woman1.nfg";
	m_objects->textureFileName = "../Resources/Packs/Textures/Woman1.tga";
	m_objects->vertexShaderFileName = "../Resources/Shaders/TriangleShaderVS.vs";
	m_objects->fragmentShaderFileName = "../Resources/Shaders/TriangleShaderFS.fs";

	return 0;
}

int SceneManager::LoadObject()
{
	m_objects->Init(m_objects->model, m_objects->texture, m_objects->shader, m_objects->matrix);

	return 0;
}

void SceneManager::Draw()
{
	m_objects->Draw();
}

void SceneManager::Update()
{
	// left empty for now
}