#include "Player.h"
#include "KeyboardBehaviour.h";
#include "SeekBehaviour.h"

Player::Player()
{
	m_kbBehaviour = new KeyboardBehaviour();
	m_seekBehaviour = new SeekBehaviour();





	m_seekBehaviour->SetTargetRadius(25.0f);
	m_seekBehaviour->OnArrive([this](){
		SetBehaviour(m_kbBehaviour);
	});

	SetBehaviour(m_kbBehaviour);
}

Player::~Player()
{
	SetBehaviour(nullptr);

	delete m_seekBehaviour;
	delete m_kbBehaviour;
}

void Player::Update(float deltaTime)
{
	if (IsMouseButtonPressed(0))
	{
		m_seekBehaviour->SetTarget( GetMousePosition() );
		SetBehaviour(m_seekBehaviour);
	}

	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	GameObject::Draw();
}