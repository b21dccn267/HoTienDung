#include "stdafx.h"
#include "GSPlay.h"
#include "Texture.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextRenderer.h"

void GSPlay::Init()
{
	m_gsPlayObjects.reserve(4);

	m_gsPlayObjects.emplace_back(SceneManager::GetInstance()->m_objects[0]);
	m_gsPlayObjects.emplace_back(SceneManager::GetInstance()->m_objects[1]);
	m_gsPlayObjects.emplace_back(SceneManager::GetInstance()->m_objects[2]);
	


	m_gsPlayObjects[0]->Set2DPosition(Vector2(100.0f, 100.0f));
	m_gsPlayObjects[0]->SetSize(200.0f, 200.0f);
	m_gsPlayObjects[1]->Set2DPosition(Vector2(300.0f, 100.0f));
	m_gsPlayObjects[1]->SetSize(200.0f, 200.0f);
	m_gsPlayObjects[2]->Set2DPosition(Vector2(600.0f, 100.0f));
	m_gsPlayObjects[2]->SetSize(200.0f, 200.0f);


	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = std::make_shared<Texture>(TextRenderer::RenderText("something meaningful"));
	auto shader = ResourceManager::GetInstance()->GetShader(0);

	std::shared_ptr<Object> text = std::make_shared<Object>(model, texture, shader);

	m_gsPlayObjects.emplace_back(text);
	m_gsPlayObjects[3]->Set2DPosition(Vector2(100.0f, 400.0f));
	m_gsPlayObjects[3]->SetSize(600.0f, 100.0f);


	printf("play init\n");
}

void GSPlay::Pause()
{
}

void GSPlay::Exit()
{
}

void GSPlay::Resume()
{
}

void GSPlay::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& x : m_gsPlayObjects) {
		x->Draw();
	}
}

void GSPlay::Update(float deltaTime)
{
	for (auto& x : m_gsPlayObjects) {
		x->Update();
	}
}

void GSPlay::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		printf("gsPlayKeyEvent\n");
	}
}

void GSPlay::HandleMouseEvent(GLint x, GLint y, bool bIsPressed)
{
	printf("gsPlayMouseEvent\n");
}

void GSPlay::Cleanup()
{
}

GSPlay::~GSPlay()
{
}
