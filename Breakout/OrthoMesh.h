#pragma once

#include "basemesh.h"

using namespace DirectX;

class OrthoMesh : public BaseMesh
{

public:
	OrthoMesh(ID3D11Device* device, ID3D11DeviceContext*, int width, int height, int xPosition = 0, int yPosition = 0);
	~OrthoMesh();

protected:
	void InitBuffers(ID3D11Device*);
	int m_width, m_height, m_xPosition, m_yPosition;
};
