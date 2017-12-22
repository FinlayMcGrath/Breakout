#pragma once

#include "GameObject.h"
#include "QuadMesh.h"

class Brick : public GameObject
{
public:
	Brick();
	~Brick();
	Brick(float x, float y, int maxHits);
	//setup directx
	void Initialise(D3D* directx);
	bool Update(float deltaTime);
	void Hit();
	QuadMesh* getMesh() { return m_mesh; };
	bool GetDeleteFlag() { return m_deleteFlag; };
	int GetMaxHits() { return m_maxHits; };
private:
	QuadMesh* m_mesh;
	int m_maxHits;
	bool m_deleteFlag;
};

