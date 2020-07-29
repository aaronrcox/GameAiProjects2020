
#include "Graph2DRenderer.h"
#include "Graph2D.h"
#include "PathFinder.h"

Graph2DRenderer::Graph2DRenderer() : m_graph(nullptr)
{
	
}

Graph2DRenderer::~Graph2DRenderer()
{
	delete m_pathFinder;
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


	// is the right mouse button pressed
	if (IsMouseButtonPressed(1))
	{
		// get the first node that we click on.
		std::vector<Graph2D::Node*> neibouringNodes;
		m_graph->GetNearbyNodes(GetMousePosition(), 8, neibouringNodes);

		if (neibouringNodes.empty() == false)
		{
			if (m_startNode == nullptr) m_startNode = neibouringNodes[0];
			else if (m_endNode == nullptr) m_endNode = neibouringNodes[0];
			else { m_startNode = neibouringNodes[0]; m_endNode = nullptr; }

			// Begin Search
			m_pathFinder->BeginSearch(m_startNode, [this](Graph2D::Node* node) {
				return node == m_endNode;
			});
		}
	}

	// Search for a path
	if (m_startNode != nullptr && m_endNode != nullptr)
	{
		if(m_pathFinder->IsSearching() && IsKeyPressed(KEY_SPACE))
			m_pathFinder->UpdateSearch();
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


	

	// Draw the nodes that are on the open list and closed list.
	if (m_pathFinder != nullptr)
	{

		auto& openList = m_pathFinder->GetOpen();
		auto& closedList = m_pathFinder->GetClosed();

		for (auto& openNode : openList)
		{
			DrawCircle(openNode->graphNode->data.x, openNode->graphNode->data.y, 4, SKYBLUE);
		}

		for (auto& closedNode : closedList)
		{
			DrawCircle(closedNode->graphNode->data.x, closedNode->graphNode->data.y, 4, DARKBLUE);
		}


		// draw the path
		if (m_pathFinder->IsPathFound())
		{
			auto& path = m_pathFinder->GetPath();
			for (int i = 1; i < path.size(); i++)
			{
				DrawLineEx(
					{ path[i - 1]->data.x, path[i - 1]->data.y }, 
					{ path[i]->data.x, path[i]->data.y },
					3.0f,
					BLACK);
			}
		}
		
	}

	// Draw start and end nodes
	if (m_startNode != nullptr)
	{
		DrawCircle(m_startNode->data.x, m_startNode->data.y, 4, ORANGE);
	}
	if (m_endNode != nullptr)
	{
		DrawCircle(m_endNode->data.x, m_endNode->data.y, 4, ORANGE);
		DrawCircleLines(m_endNode->data.x, m_endNode->data.y, 5, GRAY);
	}
}

Graph2D* Graph2DRenderer::GetGraph()
{
	return m_graph;
}

void Graph2DRenderer::SetGraph(Graph2D* graph)
{
	m_graph = graph;

	delete m_pathFinder;
	m_pathFinder = new PathFinder(m_graph);
}

