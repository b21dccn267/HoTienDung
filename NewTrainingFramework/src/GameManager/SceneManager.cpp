#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"

SceneManager* SceneManager::instance = nullptr;

int SceneManager::LoadFileSM(const char* fileName)
{
	// what do:
	// read txt
	// get id from txt
	// load assets with said id from resman
	// assign


	int ModelID = 1, TextureID = 1, ShaderID = 1, MatrixID = 1; //temp fix

	// hardcode to refactor matrix
	Model* model = new Model;
	Texture* texture = new Texture;
	Shaders* shader = new Shaders;
	MVPMatrix* matrix = new MVPMatrix;

	model->Init("../Resources/Packs/Models/Woman1.nfg");
	model->SetModelParameters();
	model->BindBuffer();

	texture->Init("../Resources/Packs/Textures/Woman1.tga");
	texture->SetTextureParameters();

	shader->Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

	matrix->Init(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));
	matrix->Calculate();
	matrix->MatrixToArray();

	FILE* f = fopen(fileName, "r");



	
	//Model* model = ResourceManager::getInstance()->GetModel(ModelID);
	//Texture* texture = ResourceManager::getInstance()->GetTexture(TextureID);
	//Shaders* shader = ResourceManager::getInstance()->GetShader(ShaderID);
	////MVPMatrix* matrix = ResourceManager::getInstance()->GetModel(MatrixID); // fix this
	//MVPMatrix* matrix = new MVPMatrix;
	m_objects = new Object(model, texture, shader, matrix);
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