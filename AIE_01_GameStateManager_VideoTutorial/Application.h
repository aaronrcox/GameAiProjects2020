#pragma once


// predeclare classes
// ---------------------------------------
class GameStateManager;

class Application
{
public:

	Application(int windowWidth, int windowHeight);
	~Application();

	void Run();

	void Update(float deltaTime);
	void Draw();

	GameStateManager* GetGameStateManager() {
		return m_gameStateManager;
	}

protected:
private:

	int m_windowWidth;
	int m_windowHeight;

	GameStateManager* m_gameStateManager = nullptr;
};



// TODO:
// - Create a "Play State"
// - Create a "Pause State"
// - Create a "High Score State"



// when we press 'space' on the 'Menu' state - change state to "Play"
// when we press 'p' on the play state - push_state("pause")
// when we press 'p' on the pause state - pop the pause state from the stack
// CHALLENGE: see if you can update the GAME STATE MANAGER so that only the 'top' state is update
// - all states should draw
