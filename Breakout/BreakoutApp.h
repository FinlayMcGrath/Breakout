// Application.h
#pragma once

// Includes
#include <vector>
#include <memory>
#include "baseapplication.h"
#include "TextureShader.h"
#include "ColourShader.h"
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"
#include "File.h"
#include "Sprite.h"

using namespace std;

class BreakoutApp : public BaseApplication
{
public:

	BreakoutApp(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input*);
	~BreakoutApp();

	bool Frame();

private:
	bool Update();
	bool Render();
	void RenderScene();
	void RenderHUD();
	void HandleInput();
	void CheckCollisions();
	void Cleanup();
	bool BreakoutApp::AabbCollide(GameObject object1, GameObject object2);
	bool BreakoutApp::SphereCollide(GameObject object1, GameObject object2);

	//shaders
	TextureShader* m_textureShader;
	ColourShader* m_colourShader;

	//gameobjects
	vector<Brick*> m_bricks;
	unique_ptr<Brick> m_brick;
	Paddle m_paddle;
	Ball m_ball;

	//sprites
	Sprite m_sprite;

	//orthos


	//lights


	//render textures


	//misc
	float m_deltaTime;
	File m_file;
};