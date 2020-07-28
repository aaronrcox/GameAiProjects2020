#include "Application.h"
#include "raylib.h"

#include "GameObject.h"
#include "Player.h"
#include "KeyboardBehaviour.h"

#include "Graph2D.h"
#include "Graph2DEditor.h"

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
	m_graph = new Graph2D();

	auto nodeA = m_graph->AddNode({ 100, 100 });
	auto nodeB = m_graph->AddNode({ 200, 100 });
	auto nodeC = m_graph->AddNode({ 200, 200 });

	m_graph->AddEdge(nodeA, nodeB, 100);
	m_graph->AddEdge(nodeB, nodeA, 100);

	m_graph->AddEdge(nodeB, nodeC, 100);
	m_graph->AddEdge(nodeC, nodeB, 100);



	m_graphEditor = new Graph2DEditor();
	m_graphEditor->SetGraph(m_graph);

}
void Application::Unload()
{

	delete m_graphEditor;
	m_graphEditor = nullptr;

	delete m_graph;
	m_graph = nullptr;
}

void Application::Update(float deltaTime)
{
	m_graphEditor->Update(deltaTime);
}
void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	m_graphEditor->Draw();

	EndDrawing();
}