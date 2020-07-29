#pragma once

#include "Graph2D.h"

#include <list>

class PathFinder
{
public:

	struct Node
	{
		Graph2D::Node* graphNode = nullptr;
		Node* parent = nullptr;
		float gScore = 0;
	};

public:

	PathFinder(Graph2D* graph);
	~PathFinder();

	void BeginSearch(Graph2D::Node* startNode, std::function<bool(Graph2D::Node*)> isGoalNodeFunc);
	void UpdateSearch();

	bool IsSearching();
	bool IsPathFound();

	const std::vector<Graph2D::Node*>& GetPath() const;

	const std::list<Node*> GetOpen() const;
	const std::list<Node*> GetClosed() const;
protected:

	Node* FindNodeInOpenOrClosed(Graph2D::Node* graphNode);

	void CalculatePath(Node* goal, std::vector<Graph2D::Node *>& out_path);

protected:

	Graph2D* m_graph = nullptr;
	
	// Set to false when we Begin searching for a path... 
	// Set to true after our FindPath method completes...
	bool m_searchComplete = false;

	// callback function used to check if we have found a "Goal" node
	std::function<bool(Graph2D::Node*)> m_isGoalNodeFunc;

	// collection of nodes representing the path
	std::vector<Graph2D::Node *> m_path;


	// open and closed list
	std::list<Node*> m_open;
	std::list<Node*> m_closed;

private:
};

