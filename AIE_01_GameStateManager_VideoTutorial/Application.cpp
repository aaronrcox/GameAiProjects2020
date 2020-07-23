
#include "Application.h"

#include "raylib.h"

#include "GameStateManager.h"
#include "IGameState.h"
#include "SplashState.h"
#include "MenuState.h"

Application::Application(int windowWidth, int windowHeight) :
	m_windowWidth(windowWidth), m_windowHeight(windowHeight)
{

}
Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, "AIE Game State Manager Tutorial");

	
	m_gameStateManager = new GameStateManager();
	m_gameStateManager->SetState("Splash", new SplashState(this)); // Load();
	m_gameStateManager->SetState("Menu", new MenuState(this)); // Load();
	
	m_gameStateManager->PushState("Splash");




	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		Update(dt);
		Draw();
	}

	delete m_gameStateManager;

	CloseWindow();
}

void Application::Update(float deltaTime)
{
	m_gameStateManager->Update(deltaTime);
}

void Application::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);
	
	m_gameStateManager->Draw();

	EndDrawing();
}

