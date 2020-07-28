#include "Application.h"
#include "raylib.h"

#include "Graph2D.h"
#include "Graph2DRenderer.h"

Application::Application(int windowWidth, int windowHeight) :
	m_windowWidth(windowWidth), m_windowHeight(windowHeight)
{

}

Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, "Graphs and Pathfinding");
	Load();
	while (!WindowShouldClose())
	{
		Update(GetFrameTime());
		Draw();
	}
	Unlaod();
	CloseWindow();
}

void Application::Load()
{
	m_graph = new Graph2D();
	

	int numRows = 6;
	int numCols = 13;
	float spacing = 50;
	float xOffset = 100;
	float yOffset = 100;

	// Create all the nodes
	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			float rx = rand() % 16 - 8;
			float ry = rand() % 16 - 8;

			m_graph->AddNode({
				x * spacing + xOffset + rx,
				y * spacing + yOffset + ry
			});
		}
	}

	// Connect nearby nodes
	for (auto node : m_graph->GetNodes())
	{
		std::vector<Graph2D::Node*> neibouringNodes;
		m_graph->GetNearbyNodes(node->data, 70, neibouringNodes);

		for (auto connectedNode : neibouringNodes)
		{
			// dont connect to ourself
			if (connectedNode == node)
				continue;

			float dist = Vector2Distance(node->data, connectedNode->data);
			m_graph->AddEdge(node, connectedNode, dist);
			m_graph->AddEdge(connectedNode, node, dist);
		}

	}

	m_graphRenderer = new Graph2DRenderer();
	m_graphRenderer->SetGraph(m_graph);
}

void Application::Unlaod()
{
	delete m_graph;
	delete m_graphRenderer;
}

void Application::Update(float deltaTime)
{
	m_graphRenderer->Update(deltaTime);
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	m_graphRenderer->Draw();

	EndDrawing();
}