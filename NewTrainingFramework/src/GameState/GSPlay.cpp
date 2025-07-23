#include "stdafx.h"
#include "GSPlay.h"
#include "Texture.h"
#include "Globals.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextRenderer.h"
#include "Animation.h"

void GSPlay::Init()
{
	m_gsPlayObjects.reserve(4);

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(4);
	auto shader = ResourceManager::GetInstance()->GetShader(1);
	auto anim = std::make_shared<Animation>(model, texture, shader, 0.2f, 0);
	anim->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	anim->SetSize(100, 100);
	m_gsPlayAnimations.push_back(anim);
	//anim->Set2DPosition()

	auto model1 = ResourceManager::GetInstance()->GetModel(0);
	auto texture1 = std::make_shared<Texture>(TextRenderer::RenderText("something meaningful"));
	auto shader1 = ResourceManager::GetInstance()->GetShader(0);

	std::shared_ptr<Object> text = std::make_shared<Object>(model1, texture1, shader1);

	m_gsPlayObjects.emplace_back(SceneManager::GetInstance()->m_objects[0]); // background
	//m_gsPlayObjects.emplace_back(SceneManager::GetInstance()->m_objects[4]); // character

	m_gsPlayObjects.emplace_back(anim); // character
	m_gsPlayObjects.emplace_back(SceneManager::GetInstance()->m_objects[1]); // close
	m_gsPlayObjects.emplace_back(SceneManager::GetInstance()->m_objects[2]); // help
	m_gsPlayObjects.emplace_back(text); // text 

	m_gsPlayObjects[0]->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));

	m_gsPlayObjects[0]->SetSize(1000.0f, 1000.0f);

	// conrollable object

	m_gsPlayObjects[1]->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	m_gsPlayObjects[1]->SetSize(500.0f, 500.0f);
	//
	m_gsPlayObjects[2]->Set2DPosition(Vector2(300.0f, 100.0f));
	m_gsPlayObjects[2]->SetSize(200.0f, 200.0f);
	m_gsPlayObjects[3]->Set2DPosition(Vector2(600.0f, 100.0f));
	m_gsPlayObjects[3]->SetSize(200.0f, 200.0f);
	// text
	m_gsPlayObjects[4]->Set2DPosition(Vector2(300.0f, 400.0f));
	m_gsPlayObjects[4]->SetSize(600.0f, 100.0f);

	//m_gsPlayAnimations.reserve(1);
	//std::shared_ptr<Animation> animPure = std::make_shared<Animation>(model, texture, shader, 1, 0);
	//m_gsPlayAnimations.emplace_back(animPure);
	//m_gsPlayAnimations[0]->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	//m_gsPlayAnimations[0]->SetSize(500.0f, 500.0f);

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
	for (auto& x : m_gsPlayAnimations) {
		x->Draw();
	}
}

void GSPlay::Update(float deltaTime)
{
	for (auto& x : m_gsPlayObjects) {
		x->Update(deltaTime);
	}
	for (auto& x : m_gsPlayAnimations) {
		x->Update(deltaTime);
	}
}

void GSPlay::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	printf("gsPlayKeyPresed: %c\n", key);
	if (bIsPressed) {
		switch (key) {
		case 0x57: 
			//printf("W pressed\n");
			m_gsPlayObjects[1]->m_position.y += 1.0f;
			break;
		case 0x41:
			//printf("A pressed\n");
			m_gsPlayObjects[1]->m_position.x -= 1.0f;
			break;
		case 0x53:
			//printf("S pressed\n");
			m_gsPlayObjects[1]->m_position.y -= 1.0f;
			break;
		case 0x44:
			//printf("D pressed\n");
			m_gsPlayObjects[1]->m_position.x += 1.0f;
			break;
		}
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