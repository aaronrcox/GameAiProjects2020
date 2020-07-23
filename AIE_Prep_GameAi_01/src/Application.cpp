#include "Application.h"
#include "raylib.h"

#include "GameObject.h"

Application::Application(int windowWidth, int windowHeight) :
	m_windowWidth(windowWidth), m_windowHeight(windowHeight)
{

}

Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, "Game AI");
	SetTargetFPS(60);

	Load();
	while (!WindowShouldClose())
	{
		Update(GetFrameTime());
		Draw();
	}
	Unload();
	CloseWindow();
}

void Application::Load()
{
	m_player = new GameObject();
	m_player->SetFriction(1.0f);
	m_player->SetPosition({ m_windowWidth * 0.5f, m_windowHeight * 0.5f });
}
void Application::Unload()
{
	delete m_player; m_player = nullptr;
}

void Application::Update(float dt)
{
	if (IsKeyDown(KEY_A)) m_player->ApplyForce({ -100, 0 });
	if (IsKeyDown(KEY_D)) m_player->ApplyForce({  100, 0 });
	if (IsKeyDown(KEY_W)) m_player->ApplyForce({  0,  -100 });
	if (IsKeyDown(KEY_S)) m_player->ApplyForce({  0,   100 }); 

	m_player->Update(dt);
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	m_player->Draw();

	EndDrawing();
}