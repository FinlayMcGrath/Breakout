#include "aabb.h"

Aabb::Aabb() : m_minVertex(FLT_MAX, FLT_MAX, FLT_MAX),	m_maxVertex(-FLT_MAX, -FLT_MAX, -FLT_MAX)
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	m_minVertex.x += 0.0f;
	m_minVertex.y += 0.0f;
	m_minVertex.z += 0.0f;
	m_maxVertex.x += 0.0f;
	m_maxVertex.y += 0.0f;
	m_maxVertex.z += 0.0f;
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
	m_position.x += deltaPosition.x;
	m_position.y += deltaPosition.y;
	m_position.z += deltaPosition.z;
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

XMFLOAT3 Aabb::min_vtx()
{
	XMFLOAT3 minvtx;
	minvtx.x = m_minVertex.x + m_position.x;
	minvtx.y = m_minVertex.y + m_position.y;
	minvtx.z = m_minVertex.z + m_position.z;

	return minvtx;
}

XMFLOAT3 Aabb::max_vtx()
{
	XMFLOAT3 maxvtx;
	maxvtx.x = m_maxVertex.x + m_position.x;
	maxvtx.y = m_maxVertex.y + m_position.y;
	maxvtx.z = m_maxVertex.z + m_position.z;
	return maxvtx;
}
