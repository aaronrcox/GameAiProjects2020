#pragma once

class Graph2D;

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

private:
};
