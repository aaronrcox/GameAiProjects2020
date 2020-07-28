#include "Graph2D.h"

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