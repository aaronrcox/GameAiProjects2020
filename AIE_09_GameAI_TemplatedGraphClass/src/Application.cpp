#include "Application.h"
#include "raylib.h"

#include "GameObject.h"
#include "Player.h"
#include "KeyboardBehaviour.h"

#include "Graph.h"

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
	Graph<Vector2, float> myGraph;

	auto nodeA = myGraph.AddNode({ 100, 100 });
	auto nodeB = myGraph.AddNode({ 200, 100 });
	auto nodeC = myGraph.AddNode({ 200, 200 });

	myGraph.AddEdge(nodeA, nodeB, 100);
	myGraph.AddEdge(nodeB, nodeA, 100);

	myGraph.AddEdge(nodeB, nodeC, 100);
	myGraph.AddEdge(nodeC, nodeB, 100);

}
void Application::Unload()
{
}

void Application::Update(float deltaTime)
{
	
}
void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	

	EndDrawing();
}