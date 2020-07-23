
#include "SplashState.h"
#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"

#include <iostream>

SplashState::SplashState(Application *app) : m_app(app)
{

}
SplashState::~SplashState()
{

}

void SplashState::Load()
{
	std::cout << "LOAD SPLASH" << std::endl;
}
void SplashState::Unload()
{
	std::cout << "UNLOAD SPLASH" << std::endl;
}

void SplashState::Update(float dt)
{
	m_timer += dt;
	if (m_timer > 3.0f)
	{
		m_app->GetGameStateManager()->SetState("Splash", nullptr); // unload
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");
	}

}
void SplashState::Draw()
{
	DrawText("SPLASH", 10, 10, 20, LIGHTGRAY);
}