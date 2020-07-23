#include "Application.h"
#include "raylib.h"

#include "GameObject.h"

Application::Application(int windowWidth, int windowHeight, const char* windowTitle) :
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_windowTitle(windowTitle)
{

}
Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, m_windowTitle);
	SetTargetFPS(60);

	Load();

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		Update(deltaTime);
		Draw();
	}

	Unload();

	CloseWindow();
}

void Application::Load()
{
	m_player = new GameObject();
	m_player->SetPosition({ m_windowWidth / 2.0f, m_windowHeight / 2.0f });
	m_player->SetFriction(1.0f);
}
void Application::Unload()
{
	delete m_player;
	m_player = nullptr;
}

void Application::Update(float deltaTime)
{

	
	if (IsKeyDown(KEY_W)) m_player->ApplyForce({ 0, -100 });
	if (IsKeyDown(KEY_S)) m_player->ApplyForce({ 0, 100 });
	if (IsKeyDown(KEY_A)) m_player->ApplyForce({ -100, 0 });
	if (IsKeyDown(KEY_D)) m_player->ApplyForce({ 100, 0 });
	

	m_player->Update(deltaTime);
}
void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	m_player->Draw();

	EndDrawing();
}