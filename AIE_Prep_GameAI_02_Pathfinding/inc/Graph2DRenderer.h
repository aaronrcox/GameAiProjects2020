#pragma once

#include "Graph2D.h"

class PathFinder;

class Graph2DRenderer
{
public:

	Graph2DRenderer();
	~Graph2DRenderer();

	void Update(float deltaTime);
	void Draw();

	Graph2D* GetGraph();
	void SetGraph(Graph2D* graph);

protected:

	Graph2D* m_graph;

	Graph2D::Node* m_startNode = nullptr;
	Graph2D::Node* m_endNode = nullptr;
	PathFinder* m_pathFinder;

private:
};
