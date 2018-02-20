#pragma once

#include "GameObject.h"
#include "SphereMesh.h"
#include "QuadMesh.h"

class Ball : public GameObject
{
public:
	Ball();
	~Ball();
	void Hit(int colour);
	void Hit();
	//setup directx
	void Initialise(D3D* directx, XMFLOAT3 position);
	bool Update(float deltaTime);
	//SphereMesh* getMesh() { return m_mesh; };
	QuadMesh* getMesh() { return m_mesh; };
private:
	QuadMesh* m_mesh;
	Colour m_colourCode;
	bool m_turning;
};

