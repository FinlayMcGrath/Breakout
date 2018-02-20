#pragma once

#include "SpriteBatch.h"
#include "QuadMesh.h"
#include "aabb.h"
#include "D3D.h"
#include "Texture.h"
#include "SimpleMath.h"

using namespace std;
using namespace SimpleMath;

class Sprite
{
public:
	Sprite();
	~Sprite();
	bool Update(float deltaTime);
	virtual void Initialise(D3D* direct3D, Vector2 position);
	void Render();
	XMMATRIX GetMatrix();
	XMVECTOR GetPosition() { return m_position; };
	SpriteBatch* getSprite() { return m_sprite; };
	Texture* getTexture() { return m_texture; };
private:
	void SetAabbPoints();
	SpriteBatch *m_sprite;
	Vector2 m_position, m_rotation, m_scale;
	Aabb* m_aabb;
	Texture* m_texture;
};

