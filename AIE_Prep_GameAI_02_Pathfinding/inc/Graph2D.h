#pragma once

#include "raymath.h"
#include "Graph.h"

class Graph2D : public Graph<Vector2, float>
{
public:

	struct PathFindNode
	{
		Node* graphNode;
		PathFindNode* parent;
		float gScore;
	};


	enum class FindPathMode
	{
		DIJKSTRA,
		ASTAR,
		DFS,
		BFS
	};

public:

	Graph2D();
	virtual ~Graph2D();

	void GetNearbyNodes(Vector2 pos, float radius, std::vector<Node*>& out_nodes);

	// Dijkstra
	bool FindPath(Node *startNode, std::function<bool(Node *)>isGoalNode, std::list<Node *> out_path);
	

protected:
private:

};