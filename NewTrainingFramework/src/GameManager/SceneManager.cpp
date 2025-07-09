#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"
SceneManager::SceneManager()
{

}

int SceneManager::LoadFileSM(const char* fileName)
{
	/*m_objects->modelFileName = "../Resources/Packs/Models/Woman1.nfg";
	m_objects->textureFileName = "../Resources/Packs/Textures/Woman1.tga";
	m_objects->vertexShaderFileName = "../Resources/Shaders/TriangleShaderVS.vs";
	m_objects->fragmentShaderFileName = "../Resources/Shaders/TriangleShaderFS.fs";*/

	// what do:
	// read txt
	// get id from txt
	// load assets with said id from resman
	// assign to own

	int ModelID, TextureID, ShaderID, MatrixID;
	// culprit of erroe: either bad simpleton establishment or smth else
	/*Model* model = ResourceManager::getInstance()->GetModel(ModelID);
	Texture* texture = ResourceManager::getInstance()->GetTexture(TextureID);
	Shaders* shader = ResourceManager::getInstance()->GetShader(ShaderID);*/
	//MVPMatrix* matrix = ResourceManager::getInstance()->GetModel(MatrixID); // fix this
	MVPMatrix* matrix = new MVPMatrix;
	//m_objects = new Object(model, texture, shader, matrix);
	return 0;
}

int SceneManager::LoadObject()
{
	//m_objects->Init(m_objects->model, m_objects->texture, m_objects->shader, m_objects->matrix);
	return 0;
}

void SceneManager::Draw()
{
	m_objects->Draw();
}

void SceneManager::Update()
{
	m_objects->Update();
}

void SceneManager::Cleanup()
{

}