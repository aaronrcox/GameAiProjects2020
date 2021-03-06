#include "FollowPathBehaviour.h"
#include "Path.h"
#include "GameObject.h"

FollowPathBehaviour::FollowPathBehaviour()
{

}

FollowPathBehaviour::~FollowPathBehaviour()
{

}

void FollowPathBehaviour::Update(GameObject* obj, float deltaTime)
{
	Vector2 p1 = (*m_path)[m_currentPathIndex];
	float dist = Vector2Distance(obj->GetPosition(), p1);

	if (dist < 20)
	{
		m_currentPathIndex = (m_currentPathIndex + 1) % m_path->Count();
		p1 = (*m_path)[m_currentPathIndex];
	}
	
	
	Vector2 dir = Vector2Normalize( Vector2Subtract(p1, obj->GetPosition()) );

	obj->ApplyForce(Vector2Scale(dir, 100));

}
void FollowPathBehaviour::Draw(GameObject* obj) {
	m_path->Draw();
}

Path* FollowPathBehaviour::GetPath()
{
	return m_path;
}
void FollowPathBehaviour::SetPath(Path* path) {
	m_path = path;
}