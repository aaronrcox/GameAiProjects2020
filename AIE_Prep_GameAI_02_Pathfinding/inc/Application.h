#pragma once

class Graph2D;
class Graph2DRenderer;

class Application
{
public:

	Application(int windowWidth, int windowHeight);
	~Application();

	void Run();

	void Load();
	void Unlaod();

	void Update(float deltaTime);
	void Draw();

protected:

	Graph2D* m_graph = nullptr;
	Graph2DRenderer* m_graphRenderer = nullptr;

	int m_windowWidth;
	int m_windowHeight;

private:
};
