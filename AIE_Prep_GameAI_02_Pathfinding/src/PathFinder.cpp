#include "PathFinder.h"

PathFinder::PathFinder(Graph2D* graph)
{
	m_graph = graph;
}

PathFinder::~PathFinder()
{

}

void PathFinder::BeginSearch(Graph2D::Node* startNode, std::function<bool(Graph2D::Node*)> isGoalNodeFunc)
{
	Node* node = new Node();
	node->graphNode = startNode;
	node->parent = nullptr;

	m_open.clear();
	m_closed.clear();
	m_path.clear();

	m_open.push_back(node);

	m_isGoalNodeFunc = isGoalNodeFunc;
	m_searchComplete = false;
}

void PathFinder::UpdateSearch()
{
	if (m_open.empty())
	{
		m_searchComplete = true;
		return;
	}

	auto node = m_open.back();
	m_open.pop_back();
	m_closed.push_back(node);

	if (m_isGoalNodeFunc(node->graphNode))
	{
		CalculatePath(node, m_path);
		m_searchComplete = true;
		return;
	}

	for (auto& connection : node->graphNode->connections)
	{
		auto childGraphNode = connection.to;

		float cost = Vector2Distance(node->graphNode->data, childGraphNode->data);
		float gScore = node->gScore + cost;

		// is the child node already in either the open or closed list?
		auto pfNode = FindNodeInOpenOrClosed(childGraphNode);
		if (pfNode)
		{
			// update the found node if the current path is better
			if (gScore < pfNode->gScore)
			{
				pfNode->gScore = gScore;
				pfNode->parent = node;
			}
		}
		else
		{
			pfNode = new Node();
			pfNode->graphNode = childGraphNode;
			pfNode->parent = node;
			pfNode->gScore = gScore;

			m_open.push_back(pfNode);
		}
	}

	m_open.sort([this](Node* a, Node* b) {
		return a->gScore > b->gScore;
	});
}

bool PathFinder::IsSearching()
{
	return m_searchComplete == false;
}

bool PathFinder::IsPathFound()
{
	return m_searchComplete;
}

const std::vector<Graph2D::Node*>& PathFinder::GetPath() const
{
	return m_path;
}

PathFinder::Node* PathFinder::FindNodeInOpenOrClosed(Graph2D::Node* graphNode)
{
	// search for the graph node in the open list
	auto oIter = std::find_if(m_open.begin(), m_open.end(), [=](Node* n) {
		return n->graphNode == graphNode;
	});

	if (oIter != m_open.end())
		return *oIter;

	// search for the graph node in the closed list
	auto cIter = std::find_if(m_closed.begin(), m_closed.end(), [=](Node* n) {
		return n->graphNode == graphNode;
	});

	if (cIter != m_closed.end())
		return *cIter;

	return nullptr;
}

void PathFinder::CalculatePath(Node* goal, std::vector<Graph2D::Node*>& out_path)
{
	out_path.clear();
	Node* current = goal;

	while (current != nullptr)
	{
		out_path.push_back(current->graphNode);
		current = current->parent;
	}
}

const std::list<PathFinder::Node*> PathFinder::GetOpen() const
{
	return m_open;
}
const std::list<PathFinder::Node*> PathFinder::GetClosed() const
{
	return m_closed;
}