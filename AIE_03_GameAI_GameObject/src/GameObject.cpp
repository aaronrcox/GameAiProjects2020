
#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{
	// m_velocity += m_acceleration * deltaTime;
	// m_position += m_velocity * deltaTime;
	// AddForce( -m_velocity * m_friction); // apply friction

	ApplyForce( Vector2Scale(Vector2Negate(m_velocity), m_friction) );

	m_velocity = Vector2Add(m_velocity, Vector2Scale(m_acceleration, deltaTime));
	m_position = Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime));
	m_acceleration = { 0, 0 };
}

void GameObject::Draw()
{
	Vector2 heading = Vector2Add(m_position, m_velocity);

	DrawCircle(m_position.x, m_position.y, 8, GRAY);
	DrawLine(m_position.x, m_position.y, heading.x, heading.y, BLACK);

}

void GameObject::ApplyForce(const Vector2& force)
{
	// m_acceleration += force;
	m_acceleration = Vector2Add(m_acceleration, force);
}

// Getters
const Vector2& GameObject::GetPosition() const
{
	return m_position;
}
const Vector2& GameObject::GetVelocity() const
{
	return m_velocity;
}
const float& GameObject::GetFriction() const
{
	return m_friction;
}

// Setters
void GameObject::SetPosition(const Vector2& pos)
{
	m_position = pos;
}
void GameObject::SetVelocity(const Vector2& vel)
{
	m_velocity = vel;
}
void GameObject::SetFriction(const float& friction)
{
	m_friction = friction;
}