#include "WndUpgrade.h"
#include "../../Utilities/utilities.h"
#include "GameObject/actors/hero/Hero.h"
#include <GameManager/ResourceManager.h>
#include <memory>
#include <globals.h>
#include "GameState/GameButton.h"


WndUpgrade::WndUpgrade()
{
	m_isActive = true;

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(40);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	m_upgradeFrame = std::make_shared<Object>(model, texture, shader);
	m_upgradeFrame->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	m_upgradeFrame->SetSize(700, 400);
	texture = ResourceManager::GetInstance()->GetTexture(41);

	m_upgradeButton1 = std::make_shared<GameButton>(model, texture, shader);
	m_upgradeButton1->SetSize(370, 75);
	m_upgradeButton1->Set2DPosition(Vector2(Globals::screenWidth / 2, 250));

	m_upgradeButton2 = std::make_shared<GameButton>(model, texture, shader);
	m_upgradeButton2->SetSize(370, 75);
	m_upgradeButton2->Set2DPosition(Vector2(Globals::screenWidth / 2, 330));

	m_upgradeButton3 = std::make_shared<GameButton>(model, texture, shader);
	m_upgradeButton3->SetSize(370, 75);
	m_upgradeButton3->Set2DPosition(Vector2(Globals::screenWidth / 2, 410));

	m_upgradeButton1->SetOnClick([]() {
		printf("button1 pressed\n");
		});
	m_upgradeButton2->SetOnClick([]() {
		printf("button2 pressed\n");
		});
	m_upgradeButton3->SetOnClick([]() {
		printf("button3 pressed\n");
		});
}
void WndUpgrade::Draw()
{
	m_upgradeFrame->Draw();
	m_upgradeButton1->Draw();
	m_upgradeButton2->Draw();
	m_upgradeButton3->Draw();
}

void WndUpgrade::Update(GLint x, GLint y, bool isPressed)
{
	m_upgradeButton1->HandleTouchEvents(x, y, isPressed);
	m_upgradeButton2->HandleTouchEvents(x, y, isPressed);
	m_upgradeButton3->HandleTouchEvents(x, y, isPressed);
}