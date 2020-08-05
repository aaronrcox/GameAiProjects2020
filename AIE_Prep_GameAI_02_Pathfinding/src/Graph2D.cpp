#include "Graph2D.h"
#include <map>

Graph2D::Graph2D()
{

}

Graph2D::~Graph2D()
{

}

void Graph2D::GetNearbyNodes(Vector2 pos, float radius, std::vector<Node*>& out_nodes)
{
	for (auto node : m_nodes)
	{
		float dist = Vector2Distance(pos, node->data);
		if (dist < radius)
		{
			out_nodes.push_back(node);
		}
	}
}

/*
bool Graph2D::FindPath(Node* startNode, std::function<bool(Node*)>isGoalNode, std::list<Node*> out_path)
{
	if (m_nodes.empty())
		return false;

	std::map<PathFindNode*, bool> visited;
	std::map<PathFindNode*, bool> inStack;
	std::map<Node*, PathFindNode*> nodes;

	std::list<PathFindNode*> stack;

	PathFindNode* pfNode = new PathFindNode();
	pfNode->graphNode = startNode;
	pfNode->parent = nullptr;
	pfNode->gScore = 0;

	inStack[pfNode] = true;
	nodes[startNode] = pfNode;
	stack.push_back(pfNode);

	while (stack.empty() == false)
	{
		// get node at end of stack, and then remove the node from the stack.
		pfNode = stack.back();
		stack.pop_back();
		inStack[pfNode] = false;

		// add the node to the visited
		visited[pfNode] = true;

		// if the predicate returns true, we can stop the search
		if (isGoalNode(pfNode->graphNode)) {
			out_path.clear();
			while (pfNode != nullptr)
			{
				out_path.push_front(pfNode->graphNode);
				pfNode = pfNode->parent;
			}
			return true;
		}

		// add children to the stack if they have not been visited
		for (Edge& connection : pfNode->graphNode->connections)
		{
			// GScore = edgeCost + parent GScore
			float gScore = connection.data + ((pfNode->parent) ? pfNode->parent->gScore : 0);
			
			// does the node exist in the visited list? or,
			// is it already in the stack?
			auto childPfNodeIter = nodes.find(connection.to);
			if (childPfNodeIter == nodes.end())
			{ 
				PathFindNode* childPfNode = new PathFindNode();
				childPfNode->graphNode = connection.to;
				childPfNode->parent = pfNode;
				childPfNode->gScore = gScore;

				inStack[childPfNode] = true;
				nodes[connection.to] = childPfNode;
				stack.push_back(pfNode);
			}
			else
			{
				PathFindNode* childPfNode = childPfNodeIter->second;
				if (childPfNode->gScore > gScore)
				{
					childPfNode->gScore = gScore;
					childPfNode->parent = pfNode;
				}
			}
		}

		stack.sort([](const PathFindNode* a, const PathFindNode* b) {
			return a->gScore > b->gScore;
		});
	}

	// stack is empty... no path found
	return false;
}

*/