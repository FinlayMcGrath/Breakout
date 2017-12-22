#pragma once

#include "GameObject.h"
#include "QuadMesh.h"
#include <iostream>

class Paddle :	public GameObject
{
public:
	Paddle();
	~Paddle();
	void Hit();
	//setup directx
	void Initialise(D3D* directx, XMFLOAT3 position);
	bool Update(float deltaTime);
	QuadMesh* getMesh() { return m_mesh; };
private:
	QuadMesh* m_mesh;
};

