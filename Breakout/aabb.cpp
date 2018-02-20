#include "aabb.h"

Aabb::Aabb() : m_minVertex(FLT_MAX, FLT_MAX, FLT_MAX),	m_maxVertex(-FLT_MAX, -FLT_MAX, -FLT_MAX)
{

}

Aabb::Aabb(const XMFLOAT3 min_vtx, const XMFLOAT3 max_vtx)
{
	m_minVertex = min_vtx;
	m_maxVertex = max_vtx;

	m_vertices[0].x = m_minVertex.x;
	m_vertices[0].y = m_minVertex.y;
	m_vertices[0].z = m_minVertex.z;

	m_vertices[1].x = m_maxVertex.x;
	m_vertices[1].y = m_minVertex.y;
	m_vertices[1].z = m_minVertex.z;

	m_vertices[2].x = m_minVertex.x;
	m_vertices[2].y = m_maxVertex.y;
	m_vertices[2].z = m_minVertex.y;

	m_vertices[3].x = m_maxVertex.x;
	m_vertices[3].y = m_maxVertex.y;
	m_vertices[3].z = m_minVertex.z;

	m_vertices[4].x = m_minVertex.x;
	m_vertices[4].y = m_minVertex.y;
	m_vertices[4].z = m_maxVertex.z;

	m_vertices[5].x = m_maxVertex.x;
	m_vertices[5].y = m_minVertex.y;
	m_vertices[5].z = m_maxVertex.z;

	m_vertices[6].x = m_minVertex.x;
	m_vertices[6].y = m_maxVertex.y;
	m_vertices[6].z = m_maxVertex.z;

	m_vertices[7].x = m_maxVertex.x;
	m_vertices[7].y = m_maxVertex.y;
	m_vertices[7].z = m_maxVertex.z;
}

void Aabb::Update(XMFLOAT3 deltaPosition)
{
	m_minVertex.x += deltaPosition.x;
	m_minVertex.y += deltaPosition.y;
	m_minVertex.z += deltaPosition.z;
	m_maxVertex.x += deltaPosition.x;
	m_maxVertex.y += deltaPosition.y;
	m_maxVertex.z += deltaPosition.z;
}

//call this during mesh construction
void Aabb::AddPoint(XMFLOAT3 point)
{
	if (point.x < m_minVertex.x)
	{
		m_minVertex.x = point.x;
	}
	if (point.y < m_minVertex.y)
	{
		m_minVertex.y = point.y;
	}
	if (point.z < m_minVertex.z)
	{
		m_minVertex.z = point.z;
	}
	if (point.x > m_maxVertex.x)
	{
		m_maxVertex.x = point.x;
	}
	if (point.y > m_maxVertex.y)
	{
		m_maxVertex.y = point.y;
	}
	if (point.z > m_maxVertex.z)
	{
		m_maxVertex.z = point.z;
	}
}
