#include "GameObject.h"

GameObject::GameObject()
{
	m_scale.x = 1.0f;
	m_scale.y = 1.0f;
	m_scale.z = 1.0f;
}

GameObject::~GameObject()
{

}

void GameObject::Initialise()
{
	m_aabb = new Aabb();
	SetAabbPoints();
}

bool GameObject::Update(float deltaTime)
{
	//TODO: create vector class with overloads so I can use arithmetic on vectors here
	XMFLOAT3 deltaPosition;
	deltaPosition.x = m_velocity.x * m_scale.x * deltaTime;
	deltaPosition.y = m_velocity.y * m_scale.y * deltaTime;
	deltaPosition.z = m_velocity.z * m_scale.z * deltaTime;

	m_position.x += deltaPosition.x;
	m_position.y += deltaPosition.y;
	m_position.z += deltaPosition.z;

	m_mesh->SetMatrix(GetMatrix());

	m_aabb->Update(deltaPosition);

	if (m_aabb->m_position.x != m_position.x)
	{
		deltaPosition.x += 1;
	}
	return true;
}

XMMATRIX GameObject::GetMatrix()
{
	XMMATRIX matrix;

	//calculate matrix transforms based off position and scale
	matrix = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	matrix = XMMatrixMultiply(matrix, XMMatrixTranslation(m_position.x, m_position.y, m_position.z));
	
	return matrix;
}

void GameObject::SetAabbPoints()
{
	for (int i = 0; i < m_mesh->GetVertexCount(); i++)
	{
		XMFLOAT3 transform;
		transform.x = m_mesh->GetVertices()[i].position.x * m_scale.x;
		transform.y = m_mesh->GetVertices()[i].position.y * m_scale.y;
		transform.z = m_mesh->GetVertices()[i].position.z * m_scale.z;
		m_aabb->AddPoint(transform);
	}
	//delete m_mesh->GetVertices();
	m_aabb->Update(m_position);
}

void GameObject::SetColour(int colour)
{
	switch (colour)
	{
	case yellow:
		m_colour.x = 1.0f;
		m_colour.y = 0.0f;
		m_colour.z = 1.0f;
		m_colour.w = 1.0f;
		break;
	case orange:
		m_colour.x = 1.0f;
		m_colour.y = 0.5f;
		m_colour.z = 0.0f;
		m_colour.w = 1.0f;
		break;
	case red:
		m_colour.x = 1.0f;
		m_colour.y = 0.0f;
		m_colour.z = 0.0f;
		m_colour.w = 1.0f;
		break;
	case blue:
		m_colour.x = 0.0f;
		m_colour.y = 0.0f;
		m_colour.z = 1.0f;
		m_colour.w = 1.0f;
		break;
	case black:
		m_colour.x = 0.0f;
		m_colour.y = 0.0f;
		m_colour.z = 0.0f;
		m_colour.w = 1.0f;
		break;
	default:
		m_colour.x = 1.0f;
		m_colour.y = 1.0f;
		m_colour.z = 1.0f;
		m_colour.w = 1.0f;
		break;
	}
}