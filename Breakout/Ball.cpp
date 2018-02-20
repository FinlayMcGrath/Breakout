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
	m_mesh = new SphereMesh(direct3D->GetDevice(), direct3D->GetDeviceContext(), L"../res/brick1.png");
	m_position = position;

	GameObject::m_mesh = m_mesh;
	GameObject::Initialise();

}

bool Ball::Update(float deltaTime)
{
	m_oldPosition = GetPosition();

	GameObject::Update(deltaTime);

	//check screen bounds
	if (m_position.x > HALF_SCREEN_SIZEX)
	{
		m_velocity.x *= -1;
		m_position.x = HALF_SCREEN_SIZEX;
	}
	if (m_position.x < -HALF_SCREEN_SIZEX)
	{
		m_position.x = -HALF_SCREEN_SIZEX;
		m_velocity.x *= -1;
	}
	if (m_position.y > HALF_SCREEN_SIZEY)
	{
		m_velocity.y *= -1;
		m_position.y = HALF_SCREEN_SIZEY;
	}
	if (m_position.y < -HALF_SCREEN_SIZEY)
	{
		m_position.y = -HALF_SCREEN_SIZEY;
		m_velocity.y *= -1;
	}

	return true;
}

void Ball::Hit(int colour = -1)
{
	m_velocity.y *= -1;
	SetColour(colour);
}

void Ball::Hit()
{
	m_velocity.y *= -1;
	SetPosition(m_oldPosition);
}