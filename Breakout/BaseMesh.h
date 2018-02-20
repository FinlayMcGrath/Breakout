// Mesh.h
#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <string>
#include <vector>
#include "texture.h"

using namespace DirectX;
using namespace std;


class BaseMesh
{
public:

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	BaseMesh();
	~BaseMesh();

	virtual void SendData(ID3D11DeviceContext*);
	int GetIndexCount();
	int GetVertexCount() { return m_vertexCount; };
	ID3D11ShaderResourceView* GetTexture();
	//XMFLOAT3 getPosition(){ return m_position; };
	//void setPosition(XMFLOAT3 position_){ m_position = position_; };
	//XMFLOAT3 getRotation(){ return m_rotation; };
	//void getRotation(XMFLOAT3 rotation_){ m_rotation = rotation_; };
	//XMFLOAT3 getScale(){ return m_scale; };
	//void setScale(XMFLOAT3 scale_){ m_scale = scale_; };
	XMMATRIX GetMatrix() { return m_matrix; };
	void SetMatrix(XMMATRIX matrix) { m_matrix = matrix; };
	VertexType* GetVertices() { return m_vertices; };
	vector<VertexType> GetVertexValues();
protected:
	virtual void InitBuffers(ID3D11Device*) = 0;
	void LoadTexture(ID3D11Device*, ID3D11DeviceContext*, WCHAR*);

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	Texture* m_Texture;
	//XMFLOAT3 m_position, m_rotation, m_scale;
	XMMATRIX m_matrix;
	VertexType* m_vertices;
};
