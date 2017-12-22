// BaseApplication.h
// Contains base application functionality. For inheritance purposes.
#pragma once

// Globals
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 2000.0f;	// 1000.0f
const float SCREEN_NEAR = 0.1f;		////do not change

// Includes
#include "input.h"
#include "d3d.h"
#include "camera.h"
#include "timer.h"

class BaseApplication
{
public:

	BaseApplication(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input*);
	~BaseApplication();

	virtual bool Frame();

protected:
	virtual void HandleInput(float);
	virtual bool Render() = 0;

protected:
	Input* m_input;
	D3D* m_direct3D;
	Camera* m_camera;
	Timer* m_timer;
};