#include "Application.h"
#include "raylib.h"

Application::Application()
{

}

Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, "maze");
	Load();
	while (!WindowShouldClose())
	{
		Update(GetFrameTime());
		Draw();
	}
	Unload();
	CloseWindow();
}

void Application::Load()
{
	m_tileSize = 40;
	float hs = m_tileSize * 0.5f;

	m_numRows = m_windowHeight / m_tileSize;
	m_numCols = m_windowWidth / m_tileSize;
	int totalTiles = m_numRows * m_numCols;

	ResetMaze();

}

void Application::Unload()
{

}

void Application::Update(float dt)
{
	if (IsKeyPressed(KEY_SPACE))
	{
		ResetMaze();
		m_startGeneration = true;
	}

	m_updateTimer += dt;
	if (m_updateTimer > 0.1f && m_startGeneration)
	{
		m_updateTimer = 0.0f;
		UpdateMazeGen();
	}
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	float hs = m_tileSize * 0.5f;

	auto stackColor = GRAY;
	auto visitedColor = LIGHTGRAY;
	auto lineColor = DARKGRAY;

	// draw the tiles that have been visited
	for (int y = 0; y < m_numRows; y++)
	{
		for (int x = 0; x < m_numCols; x++)
		{
			int index = y * m_numCols + x;
			if (m_tiles[index].visited)
			{
				float xPos = x * m_tileSize + hs;
				float yPos = y * m_tileSize + hs;
				DrawRectangle(xPos - hs, yPos - hs, m_tileSize, m_tileSize, visitedColor);
			}
		}
	}

	// draw the tiles on the stack
	for (auto& tile : m_stack)
	{
		float xPos = tile->xIndex * m_tileSize + hs;
		float yPos = tile->yIndex * m_tileSize + hs;
		DrawCircle(xPos, yPos, 2, stackColor);
	}

	// draw the last node on the stack
	if (m_stack.empty() == false)
	{
		auto tile = m_stack.back();
		float xPos = tile->xIndex * m_tileSize + hs;
		float yPos = tile->yIndex * m_tileSize + hs;
		DrawRectangle(xPos - hs, yPos - hs, m_tileSize, m_tileSize, stackColor);
	}

	// Draw the maze tiles.
	// only draw right & bottom walls to avoid rendering walls twice.
	for (int y = 0; y < m_numRows; y++)
	{
		for (int x = 0; x < m_numCols; x++)
		{
			int index = y * m_numCols + x;
			float xPos = x * m_tileSize + hs;
			float yPos = y * m_tileSize + hs;
			
			// top
			if (m_tiles[index].wall[MazeTile::NORTH] && y == 0)
				DrawLine(xPos - hs, yPos - hs, xPos + hs, yPos - hs, lineColor);

			// Bottom
			if (m_tiles[index].wall[MazeTile::SOUTH])
				DrawLine(xPos - hs, yPos + hs, xPos + hs, yPos + hs, lineColor);

			// Right
			if (m_tiles[index].wall[MazeTile::EAST])
				DrawLine(xPos + hs, yPos - hs, xPos + hs, yPos + hs, lineColor);

			// Left
			if (m_tiles[index].wall[MazeTile::EAST] && x == 0)
			 	DrawLine(xPos - hs, yPos - hs, xPos - hs, yPos + hs, lineColor);

		}
	}

	EndDrawing();
}

void Application::UpdateMazeGen()
{
	if (m_stack.empty())
		return;

	// get the last tile from the stack, and flag it as visited.
	auto tile = m_stack.back();
	tile->visited = true;

	// Get index for nort, south, east, west neibours
	auto nNode = GetTile(tile->xIndex, tile->yIndex-1);
	auto sNode = GetTile(tile->xIndex, tile->yIndex+1);
	auto eNode = GetTile(tile->xIndex+1, tile->yIndex);
	auto wNode = GetTile(tile->xIndex-1, tile->yIndex);
	
	// neibours that have not been visited
	std::vector<MazeTile*> neibours; 
	if (nNode && !nNode->visited) neibours.push_back(nNode);
	if (sNode && !sNode->visited) neibours.push_back(sNode);
	if (eNode && !eNode->visited) neibours.push_back(eNode);
	if (wNode && !wNode->visited) neibours.push_back(wNode);

	// Get a random non visited neibour
	auto neibour = neibours.empty() ? nullptr : neibours[rand() % neibours.size()];

	if (neibour == nullptr)
	{
		// remove current tile from the stack when all neibours have been visited
		m_stack.pop_back();
	}
	else
	{
		// break down the walls between us.
		int xd = neibour->xIndex - tile->xIndex; // WEST: -1	EAST: +1
		int yd = neibour->yIndex - tile->yIndex; // NORTH: -1	SOUTH: +1

		// because each tile has its own wall
		// bereak down the opsate wall for the neibouring tile.
		if (xd > 0) { tile->wall[MazeTile::EAST] = false;  neibour->wall[MazeTile::WEST] = false; }
		if (xd < 0) { tile->wall[MazeTile::WEST] = false;  neibour->wall[MazeTile::EAST] = false; }
		if (yd < 0) { tile->wall[MazeTile::NORTH] = false;  neibour->wall[MazeTile::SOUTH] = false; }
		if (yd > 0) { tile->wall[MazeTile::SOUTH] = false;  neibour->wall[MazeTile::WEST] = false; }

		m_stack.push_back(neibour);
	}	
}

MazeTile* Application::GetTile(int xIndex, int yIndex)
{
	// check index is in bountd
	if (xIndex < 0 || xIndex >= m_numCols || yIndex < 0 || yIndex >= m_numRows)
		return nullptr;

	int index = yIndex * m_numCols + xIndex;
	return &m_tiles[index];
}

void Application::ResetMaze()
{
	m_tiles.clear();
	m_stack.clear();

	for (int y = 0; y < m_numRows; y++)
	{
		for (int x = 0; x < m_numCols; x++)
		{
			m_tiles.push_back(MazeTile(x, y));
		}
	}

	m_stack.push_back(&m_tiles[0]);
}