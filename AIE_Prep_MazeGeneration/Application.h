#pragma once

#include <vector>
#include <list>
#include <map>

struct MazeTile
{
	enum EDir {
		NORTH, EAST, SOUTH, WEST
	};

	MazeTile() {}
	MazeTile(int x, int y) : xIndex(x), yIndex(y) {}

	// Each tile has 4 walls, NORTH, EAST, SOUTH and WEST.
	bool wall[4] = { true, true, true, true };

	bool visited = false;

	float xIndex;
	float yIndex;
};

class Application
{
public:

	Application();
	~Application();

	void Run();
	void Load();
	void Unload();
	void Update(float dt);
	void Draw();

	void ResetMaze();
	void UpdateMazeGen();
	MazeTile* GetTile(int xIndex, int yIndex);

protected:
private:
	int m_windowWidth = 800;
	int m_windowHeight = 450;

	float m_tileSize;
	int m_numRows;
	int m_numCols;

	std::vector<MazeTile> m_tiles;
	std::list<MazeTile*> m_stack;

	float m_updateTimer = 0;
	bool m_startGeneration = false;
};
