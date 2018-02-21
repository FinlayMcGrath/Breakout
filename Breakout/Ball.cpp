#include "Ball.h"

Ball::Ball()
{
	m_velocity = XMFLOAT3(30.0f, -30.0f, 0.0f);
	m_colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}

Ball::~Ball()
{
	// Release the mesh
	if (m_mesh)
	{
		delete m_mesh;
		m_mesh = 0;
	}
}

void Ball::Initialise(D3D * direct3D, XMFLOAT3 position)
{
	//m_mesh = new SphereMesh(direct3D->GetDevice(), direct3D->GetDeviceContext(), L"../res/brick1.png");
	m_mesh = new QuadMesh(direct3D->GetDevice(), direct3D->GetDeviceContext(), L"../res/brick1.png");
	m_position = position;

	GameObject::m_mesh = m_mesh;
	GameObject::Initialise();

}

bool Ball::Update(float deltaTime)
{
	m_oldPosition = m_position;
	GameObject::Update(deltaTime);

	//check screen bounds
	if (m_position.x > HALF_SCREEN_SIZEX)
	{
		Hit();
		m_velocity.x *= -1;
		m_velocity.y *= -1;
	}
	if (m_position.x < -HALF_SCREEN_SIZEX)
	{
		Hit();
		m_velocity.x *= -1;
		m_velocity.y *= -1;
	}
	if (m_position.y > HALF_SCREEN_SIZEY)
	{
		Hit();
	}
	if (m_position.y < -HALF_SCREEN_SIZEY)
	{
		Hit();
	}

	return true;
}

void Ball::Hit(int colour)
{
	vector<BaseMesh::VertexType> vert = m_mesh->GetVertexValues();
	m_velocity.y *= -1;
	SetColour(colour);

	XMFLOAT3 deltaPosition;
	deltaPosition.x = m_oldPosition.x - m_position.x;
	deltaPosition.y = m_oldPosition.y - m_position.y;
	deltaPosition.z = m_oldPosition.z - m_position.z;
	m_aabb->Update(deltaPosition);

	m_position = m_oldPosition;
}

void Ball::Hit()
{
	XMFLOAT3 deltaPosition;

	deltaPosition.x = m_oldPosition.x - m_position.x;
	deltaPosition.y = m_oldPosition.y - m_position.y;
	deltaPosition.z = m_oldPosition.z - m_position.z;
	m_aabb->Update(deltaPosition);

	m_position = m_oldPosition;
	m_velocity.y *= -1;
}