#pragma once
#include "GameManager/SoundManager.h"
#include "GameObject/actors/Creature.h"
#include "GameObject/actors/CreatureSpawner.h"
#include "GameObject/actors/hero/Hero.h"
#include "GameObject/actors/Projectile.h"
#include "GameObject/core/Animation.h"
#include "GameObject/core/Object.h"
#include "GameObject/ui/HealthBar.h"
#include "GameObject/ui/WndUpgrade.h"
#include "GameObject/utils/Timer.h"
#include "GameStateBase.h"
#include <memory>
#include <vector>

class CrHero;

class GSPlay : public GameStateBase
{
public:
    std::vector<std::shared_ptr<Object>> m_gsPlayObjects;
    std::vector<std::shared_ptr<GameButton>> m_gsPlayButtons;
    //std::shared_ptr<Creature> m_creature; 
    bool m_isPaused;
    bool m_isInGladiatorMode; // special event
    // store last hero hp state here after glad mode on
    int m_hero1Health;
    int m_hero2Health;

    // game actors 
    std::shared_ptr<Hero> m_hero;
    //std::shared_ptr<Creature> m_hero2;
    std::shared_ptr<CrHero> m_hero2;
    std::shared_ptr<CreatureSpawner> m_creatureSpawner;

    // game hud objects
    std::shared_ptr<HealthBar> m_healthBar1;
    std::shared_ptr<HealthBar> m_healthBar2;
    std::shared_ptr<Timer> m_timer;
    std::shared_ptr <WndUpgrade> m_upgradeMenu;

    GSPlay() : GameStateBase(StateType::STATE_PLAY), m_isPaused(false) {}
    void Init() override;
    void Pause() override;
    void Exit() override;
    void Resume() override;
    void Draw() override;
    void Update(float deltaTime) override;
    void HandleKeyEvent(unsigned char key, bool bIsPressed) override;
    void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
    void Cleanup() override;

    ~GSPlay() override;

private:
    static void OnPauseButtonClick();
};