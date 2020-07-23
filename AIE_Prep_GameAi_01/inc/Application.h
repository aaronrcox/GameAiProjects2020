#pragma once

class GameObject;

class Application
{
public:
	Application(int windowWidth, int windowHeight);
	~Application();

	void Run();

	void Load();
	void Unload();

	void Update(float dt);
	void Draw();

protected:
	int m_windowWidth;
	int m_windowHeight;

	GameObject* m_player;
private:
};