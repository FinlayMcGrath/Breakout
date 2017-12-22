#pragma once
#include "BaseMesh.h"

using namespace DirectX;

class SphereMesh : public BaseMesh
{

public:
	SphereMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* textureFilename, int resolution = 20);
	~SphereMesh();
	float GetRadius() { return m_radius; };
protected:
	void InitBuffers(ID3D11Device* device);
	int m_resolution;
private:
	float m_radius;
};
