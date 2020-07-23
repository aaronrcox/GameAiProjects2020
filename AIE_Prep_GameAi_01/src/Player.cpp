#include "Player.h"
#include "KeyboardBehaviour.h"

Player::Player() : GameObject()
{
	m_keyboardController = new KeyboardBehaviour();

	SetBehaviour(m_keyboardController);
	SetFriction(1.0f);
}

Player::~Player()
{
	delete m_keyboardController;
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	GameObject::Draw();
}