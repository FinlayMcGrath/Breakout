#pragma once

#include <iostream>
#include "BaseMesh.h"
#include "D3D.h"
#include "aabb.h"
#include "SphereMesh.h"

const int HALF_SCREEN_SIZEX = 40;
const int HALF_SCREEN_SIZEY = 30;

enum Colour { yellow = 1, orange, white, red, blue, black,};

class GameObject 
{
public:
	GameObject();
	~GameObject();
	bool Update(float deltaTime);
	virtual void Initialise();
	void SetColour(int colour);
	void SetVelocity(XMFLOAT3 velocity) { m_velocity = velocity; };
	const Aabb& GetAabb() { return *m_aabb; };
	const SphereMesh& GetBoundingSphere() { return *m_boundingSphere; };
	XMFLOAT3 GetPosition() { return m_position; };
	XMMATRIX GetMatrix();
	XMFLOAT4 GetColour() { return m_colour; };
protected:
	void SetAabbPoints();
	BaseMesh* m_mesh;
	XMFLOAT3 m_position, m_rotation, m_scale, m_velocity;
	Aabb* m_aabb;
	SphereMesh* m_boundingSphere;
	XMFLOAT4 m_colour;
};