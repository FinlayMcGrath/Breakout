#pragma once

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class Aabb
{
public:
	Aabb();
	Aabb(const XMFLOAT3 minVertex, const XMFLOAT3 maxVertex);
	void Update(XMFLOAT3 deltaPosition);
	void AddPoint(XMFLOAT3 point);
	void set_min_vtx(XMFLOAT3 minVertex) { m_minVertex = minVertex; };
	XMFLOAT3 min_vtx();
	void set_max_vtx(XMFLOAT3 maxVertex) { m_maxVertex = maxVertex; };
	XMFLOAT3 max_vtx();
	XMFLOAT3 m_position;
private:
	/// Minimum bounds.
	XMFLOAT3 m_minVertex, m_maxVertex, m_vertices[8];
};