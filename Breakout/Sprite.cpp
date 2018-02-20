#include "Sprite.h"

Sprite::Sprite()
{
	m_scale.x = 1.0f;
	m_scale.y = 1.0f;
}

Sprite::~Sprite()
{
	// Release the texture object.
	if (m_texture)
	{
		delete m_texture;
		m_texture = 0;
	}

	// Release the texture object.
	if (m_sprite)
	{
		delete m_sprite;
		m_sprite = 0;
	}

	// Release the texture object.
	if (m_aabb)
	{
		delete m_aabb;
		m_aabb = 0;
	}
}

void Sprite::Initialise(D3D* direct3D, Vector2 position)
{
	m_texture = new Texture(direct3D->GetDevice(), L"../res/brick1.png");
	m_sprite = new SpriteBatch(direct3D->GetDeviceContext());
	m_position = position;
	m_aabb = new Aabb();
	SetAabbPoints();
}

void Sprite::Render()
{
	m_sprite->Begin();

	m_sprite->Draw(m_texture->GetTexture(), m_position, nullptr);

	m_sprite->End();

}

bool Sprite::Update(float deltaTime)
{
	//m_mesh->SetMatrix(GetMatrix());

	return false;
}

XMMATRIX Sprite::GetMatrix()
{
	XMMATRIX matrix;

	//calculate matrix transforms based off position and scale
	matrix = XMMatrixTranslation(m_position.x, m_position.y, 0.0f);

	return matrix;
}

void Sprite::SetAabbPoints()
{
	/*for (int i = 0; i < m_mesh->GetVertexCount(); i++)
	{
		XMFLOAT3 transform;
		transform.x = m_mesh->GetVertices()[i].position.x * m_scale.x;
		transform.y = m_mesh->GetVertices()[i].position.y * m_scale.y;
		transform.z = m_mesh->GetVertices()[i].position.z * m_scale.z;
		m_aabb->AddPoint(transform);
	}
	delete m_mesh->GetVertices();
	m_aabb->Update(m_position);*/
}