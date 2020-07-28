#pragma once

#include "raymath.h"
#include "Graph.h"

class Graph2D : public Graph<Vector2, float>
{
public:

	Graph2D();
	virtual ~Graph2D();

	void GetNearbyNodes(Vector2 pos, float radius, std::vector<Node*>& out_nodes);

protected:
private:
};