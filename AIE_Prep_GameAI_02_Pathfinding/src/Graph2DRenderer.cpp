
#include "Graph2DRenderer.h"
#include "Graph2D.h"

Graph2DRenderer::Graph2DRenderer() : m_graph(nullptr)
{

}
Graph2DRenderer::~Graph2DRenderer()
{

}

void Graph2DRenderer::Update(float deltaTime)
{
	if (IsMouseButtonPressed(0))
	{
		auto mousePos = GetMousePosition();
		std::vector<Graph2D::Node*> neibouringNodes;
		m_graph->GetNearbyNodes(mousePos, 50, neibouringNodes);

		for (auto closeNodes : neibouringNodes)
		{
			auto node = m_graph->AddNode(mousePos);
			float dist = Vector2Distance(node->data, closeNodes->data);

			m_graph->AddEdge(node, closeNodes, dist);
			m_graph->AddEdge(closeNodes, node, dist);
		}
	}
}
void Graph2DRenderer::Draw()
{
	auto& nodes = m_graph->GetNodes();
	
	for (auto node : nodes)
	{
		for (auto connection : node->connections)
		{
			DrawLine(node->data.x, node->data.y, connection.to->data.x, connection.to->data.y, GRAY);
		}
	}

	// Draw each node
	for (auto node : nodes)
	{
		DrawCircle(node->data.x, node->data.y, 8, LIGHTGRAY);
		DrawCircleLines(node->data.x, node->data.y, 8, GRAY);
	}

	// draw shaddow lines / edges for the node we are going to create
	// =================================================================
	auto mousePos = GetMousePosition();
	std::vector<Graph2D::Node*> neibouringNodes;
	m_graph->GetNearbyNodes(mousePos, 50, neibouringNodes);
	
	for (auto closeNodes : neibouringNodes)
	{
		DrawLine(mousePos.x, mousePos.y, closeNodes->data.x, closeNodes->data.y, LIGHTGRAY);
	}
	DrawCircle(mousePos.x, mousePos.y, 6, LIGHTGRAY);
	// =================================================================
}

Graph2D* Graph2DRenderer::GetGraph()
{
	return m_graph;
}
void Graph2DRenderer::SetGraph(Graph2D* graph)
{
	m_graph = graph;
}