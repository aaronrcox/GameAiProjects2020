#include "Player.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"

Player::Player() : GameObject()
{
	m_keyboardController = new KeyboardBehaviour();

	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->SetRange(20);

	m_seekBehaviour->OnTargetArrive([this]() {
		SetBehaviour(m_keyboardController);
	});

	SetBehaviour(m_keyboardController);
	SetFriction(1.0f);
}

Player::~Player()
{
	SetBehaviour(nullptr);

	delete m_seekBehaviour;
	delete m_keyboardController;
}

void Player::Update(float deltaTime)
{
	// check left mouse button pressed
	if (IsMouseButtonPressed(0))
	{
		m_seekBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_seekBehaviour);
	}

	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	GameObject::Draw();
}