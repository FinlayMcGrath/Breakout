// Colour shader.h
// Simple shader example.
#pragma once

#include "BaseShader.h"

using namespace std;
using namespace DirectX;


class ColourShader : public BaseShader
{
	struct ColourBufferType
	{
		XMFLOAT4 colour;
	};
public:

	ColourShader(ID3D11Device* device, HWND hwnd);
	~ColourShader();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, XMFLOAT4 colour);
	void Render(ID3D11DeviceContext* deviceContext, int vertexCount);

private:
	void InitShader(WCHAR*, WCHAR*);
	ID3D11Buffer* m_matrixBuffer, *m_colourBuffer;


};
