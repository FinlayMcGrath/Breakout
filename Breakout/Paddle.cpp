#include "Paddle.h"

Paddle::Paddle()
{
	m_scale.x = 10.0f;
	m_scale.y = 1.0f;
	m_scale.z = 1.0f;
	m_velocity.x = 10.0f;
}

Paddle::~Paddle()
{
	// Release the mesh
	if (m_mesh)
	{
		delete m_mesh;
		m_mesh = 0;
	}
}

void Paddle::Initialise(D3D* direct3D, XMFLOAT3 position)
{
	m_mesh = new QuadMesh(direct3D->GetDevice(), direct3D->GetDeviceContext(), L"../res/brick1.png");
	m_position = position;
	GameObject::m_mesh = m_mesh;
	GameObject::Initialise();
}

bool Paddle::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	std::cout << m_position.x << std::endl;


	return true;
}

void Paddle::Hit()
{

}