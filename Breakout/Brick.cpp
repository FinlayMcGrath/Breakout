#include "Brick.h"

Brick::Brick()
{
	m_maxHits = 2;
	m_deleteFlag = false;
}

Brick::Brick(float x, float y, int maxHits)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = 70.0f;
	m_maxHits = maxHits;
	m_deleteFlag = false;
}

Brick::~Brick()
{
	// Release the mesh
	if (m_mesh)
	{
		delete m_mesh;
		m_mesh = 0;
	}
}

void Brick::Initialise(D3D* direct3D)
{
	SetColour(m_maxHits);
	m_mesh = new QuadMesh(direct3D->GetDevice(), direct3D->GetDeviceContext(), L"../res/brick1.png");
	GameObject::m_mesh = m_mesh;
	GameObject::Initialise();
}

bool Brick::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if (m_maxHits < 1)
	{
		m_deleteFlag = true;
	}

	return true;
}

void Brick::Hit()
{
	m_maxHits--;
	SetColour(m_maxHits);
}