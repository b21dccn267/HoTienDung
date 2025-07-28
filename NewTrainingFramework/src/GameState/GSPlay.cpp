#include "stdafx.h"
#include "GSPlay.h"
#include "../GameObject/core/Texture.h"
#include "Globals.h"
#include "../GameManager/SceneManager.h"
#include "../GameManager/ResourceManager.h"
#include "../GameObject/core/TextRenderer.h"
#include "../GameObject/core/Animation.h"
#include "../GameManager/SoundManager.h"
#include <SDL2/SDL_mixer.h>

void GSPlay::Init()
{
	// sound test
	//SDL_Init(SDL_INIT_AUDIO);
	//Mix_OpenAudio(44100, AUDIO_S16SYS, 1, 100);
	//Mix_AllocateChannels(1);

	//Mix_Chunk* fx = Mix_LoadWAV();

	//m_soundManager = SoundManager();
	//SoundManager::GetInstance()->PlaySfx("../Resources/Sfx/vine-boom.wav");

	m_gsPlayObjects.reserve(4);

	// character
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(5);
	auto shader = ResourceManager::GetInstance()->GetShader(1);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 1);
	anim->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	anim->SetSize(100, 100);
	

	// background
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(0);
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto background = std::make_shared<Object>(model, texture, shader);
	background->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	background->SetSize(1000.0f, 1000.0f);
	

	// close
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(1);
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnClose = std::make_shared<Object>(model, texture, shader);
	btnClose->Set2DPosition(Vector2(300.0f, 100.0f));
	btnClose->SetSize(200.0f, 200.0f);
	

	// help
	model = ResourceManager::GetInstance()->GetModel(0);
	texture = ResourceManager::GetInstance()->GetTexture(2);
	shader = ResourceManager::GetInstance()->GetShader(0);
	auto btnHelp = std::make_shared<Object>(model, texture, shader);
	btnHelp->Set2DPosition(Vector2(600.0f, 100.0f));
	btnHelp->SetSize(200.0f, 200.0f);
	

	// text
	auto model1 = ResourceManager::GetInstance()->GetModel(0);
	auto texture1 = std::make_shared<Texture>(TextRenderer::RenderText("something meaningful"));
	auto shader1 = ResourceManager::GetInstance()->GetShader(0);
	auto text = std::make_shared<Object>(model1, texture1, shader1);
	text->Set2DPosition(Vector2(300.0f, 500.0f));
	text->SetSize(600.0f, 100.0f);
	

	m_gsPlayAnimations.push_back(anim);
	m_gsPlayObjects.emplace_back(background);
	m_gsPlayObjects.emplace_back(btnClose);
	m_gsPlayObjects.emplace_back(btnHelp);
	m_gsPlayObjects.emplace_back(text);

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
		x->Set2DPosition(Vector2(x->m_position.x, x->m_position.y));
	}
}

void GSPlay::HandleKeyEvent(unsigned char key, bool bIsPressed)
{
	printf("gsPlayKeyPresed: %c\n", key);
	SoundManager::PlaySfx("../Resources/Sfx/vine-boom.wav");
	if (bIsPressed) {
		switch (key) {
		case 0x57: 
			//printf("W pressed\n");
			m_gsPlayAnimations[0]->m_position.y -= 10.0f;
			break;
		case 0x41:
			//printf("A pressed\n");
			m_gsPlayAnimations[0]->m_position.x -= 10.0f;
			break;
		case 0x53:
			//printf("S pressed\n");
			m_gsPlayAnimations[0]->m_position.y += 10.0f;
			break;
		case 0x44:
			//printf("D pressed\n");
			m_gsPlayAnimations[0]->m_position.x += 10.0f;
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