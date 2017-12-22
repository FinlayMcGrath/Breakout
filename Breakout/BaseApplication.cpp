// BaseApplication.cpp
// Base application functionality for inheritnace.
#include "BaseApplication.h"


BaseApplication::BaseApplication(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	m_input = in;

	// Create the Direct3D object.
	m_direct3D = new D3D(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	// Initialize the Direct3D object.
	if (!m_direct3D)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		exit(EXIT_FAILURE);
	}

	// Create the camera object.
	m_camera = new Camera();
	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_camera->Update();

	// Create the timer object.
	m_timer = new Timer();
}


BaseApplication::~BaseApplication()
{
	// Release the timer object.
	if (m_timer)
	{
		delete m_timer;
		m_timer = 0;
	}

	// Release the camera object.
	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}

	// Release the Direct3D object.
	if (m_direct3D)
	{
		delete m_direct3D;
		m_direct3D = 0;
	}
}

bool BaseApplication::Frame()
{
	// Check if the user pressed escape and wants to exit the application.
	if (m_input->isKeyDown(VK_ESCAPE) == true)
	{
		return false;
	}

	// Update the system stats.
	m_timer->Frame();

	// Do the frame input processing.
	HandleInput(m_timer->GetTime());

	return true;
}


void BaseApplication::HandleInput(float frameTime)
{
	// Set the frame time for calculating the updated position.
	m_camera->SetFrameTime(frameTime);

	// Handle the input.
	if (m_input->isKeyDown('W'))
	{
		// forward
		m_camera->MoveForward();
	}
	if (m_input->isKeyDown('S'))
	{
		// back
		m_camera->MoveBackward();
	}
	if (m_input->isKeyDown('Q'))
	{
		// Down
		m_camera->MoveDownward();
	}
	if (m_input->isKeyDown('E'))
	{
		// Up
		m_camera->MoveUpward();
	}
	if (m_input->isKeyDown(VK_UP))
	{
		// rotate up
		m_camera->TurnUp();
	}
	if (m_input->isKeyDown(VK_DOWN))
	{
		// rotate down
		m_camera->TurnDown();
	}
	if (m_input->isKeyDown(VK_LEFT))
	{
		// rotate left
		m_camera->TurnLeft();
	}
	if (m_input->isKeyDown(VK_RIGHT))
	{
		// rotate right
		m_camera->TurnRight();
	}

	if (m_input->isKeyDown(VK_SPACE))
	{
		m_camera->Reset();
	}
}
