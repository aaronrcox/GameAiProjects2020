#include "SeekBehaviour.h"
#include "GameObject.h"
#include "raylib.h"

SeekBehaviour::SeekBehaviour() : Behaviour()
{

}

SeekBehaviour::~SeekBehaviour()
{

}

void SeekBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToTarget = Vector2Distance(m_target, obj->GetPosition());
	if (distToTarget < m_range)
	{
		if(m_onArriveFn)
			m_onArriveFn();
	}

	// get the heading position
	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());
	float headingLen = Vector2Length(heading);

	Vector2 dirToTarget = Vector2Normalize( Vector2Subtract(m_target, obj->GetPosition()) );
	Vector2 vecToTarget = Vector2Scale(dirToTarget, headingLen);

	Vector2 targetForcePos = Vector2Add(vecToTarget, obj->GetPosition());

	Vector2 forceDir = Vector2Subtract(targetForcePos, heading);

	obj->ApplyForce(forceDir);
}

void SeekBehaviour::Draw(GameObject* obj)
{
	
	DrawCircle(m_target.x, m_target.y, m_range, LIGHTGRAY);
	DrawCircle(m_target.x, m_target.y, 4, GRAY);
}

const Vector2& SeekBehaviour::GetTarget() const
{
	return m_target;
}
void SeekBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& SeekBehaviour::GetRange() const
{
	return m_range;
}
void SeekBehaviour::SetRange(const float& range)
{
	m_range = range;
}

void SeekBehaviour::OnTargetArrive(OnArriveFn callback)
{
	m_onArriveFn = callback;
}