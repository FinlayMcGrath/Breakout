#include "breakoutapp.h"

BreakoutApp::BreakoutApp(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in) : BaseApplication(hinstance, hwnd, screenWidth, screenHeight, in)
{
	m_input = in;
	m_deltaTime = 0.0f;

	//set up shaders
	m_textureShader = new TextureShader(m_direct3D->GetDevice(), hwnd);
	m_colourShader = new ColourShader(m_direct3D->GetDevice(), hwnd);

	//load bricks from text file
	m_bricks = m_file.Load("../bricks.txt");

	//setup directx with gameobjects
	for (auto brick : m_bricks)
	{
		brick->Initialise(m_direct3D);
	}
	m_paddle.Initialise(m_direct3D, XMFLOAT3(0.0f, -25.0f, 70.0f));
	m_ball.Initialise(m_direct3D, XMFLOAT3(0.0f, 0.0f, 70.0f));
	
}

BreakoutApp::~BreakoutApp()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the shaders
	if (m_textureShader)
	{
		delete m_textureShader;
		m_textureShader = 0;
	}

	if (m_colourShader)
	{
		delete m_colourShader;
		m_colourShader = 0;
	}
}

bool BreakoutApp::Frame()
{
	bool result;

	result = BaseApplication::Frame();
	m_deltaTime = m_timer->GetTime();
	if (!result)
	{
		return false;
	}

	HandleInput();

	//update objects
	result = Update();
	if (!result)
	{
		return false;
	}
	
	CheckCollisions();
	
	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool BreakoutApp::Update()
{
	for (auto brick : m_bricks)
	{
		brick->Update(m_deltaTime);
	}

	m_ball.Update(m_deltaTime);
	m_paddle.Update(m_deltaTime);

	return true;
}

bool BreakoutApp::Render()
{
	// Generate the view matrix based on the camera's position.
	m_camera->Update();

	// Render scene to buffer
	RenderScene();
	
	return true;
}

//draw textured scene
void BreakoutApp::RenderScene()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	m_direct3D->SetBackBufferRenderTarget();
	m_direct3D->ResetViewport();

	// Clear the scene. (default blue colour)
	m_direct3D->BeginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_direct3D->GetWorldMatrix(worldMatrix);
	m_camera->GetViewMatrix(viewMatrix);
	m_direct3D->GetProjectionMatrix(projectionMatrix);

	//draw gameobjects
	for (auto brick : m_bricks)
	{
		worldMatrix = brick->getMesh()->GetMatrix();
		brick->getMesh()->SendData(m_direct3D->GetDeviceContext());
		m_colourShader->SetShaderParameters(m_direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix,  brick->GetColour());
		m_colourShader->Render(m_direct3D->GetDeviceContext(), brick->getMesh()->GetIndexCount());
	}

	worldMatrix = m_ball.getMesh()->GetMatrix();
	m_ball.getMesh()->SendData(m_direct3D->GetDeviceContext());
	m_colourShader->SetShaderParameters(m_direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_ball.GetColour());
	m_colourShader->Render(m_direct3D->GetDeviceContext(), m_ball.getMesh()->GetIndexCount());

	worldMatrix = m_paddle.getMesh()->GetMatrix();
	m_paddle.getMesh()->SendData(m_direct3D->GetDeviceContext());
	m_textureShader->SetShaderParameters(m_direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_paddle.getMesh()->GetTexture());
	m_textureShader->Render(m_direct3D->GetDeviceContext(), m_paddle.getMesh()->GetIndexCount());

	// Present the rendered scene to the screen.
	m_direct3D->EndScene();
}

void BreakoutApp::HandleInput()
{
	if (m_input->isKeyDown('A'))
	{
		// Strafe Left
		if (m_paddle.GetPosition().x > -HALF_SCREEN_SIZEX)
		{
			m_paddle.SetVelocity(XMFLOAT3(-15.0f, 0.0f, 0.0f));
		}
		m_input->SetKeyUp('A');
	}	
	else if (m_input->isKeyDown('D'))
	{
		// Strafe Right
		if (m_paddle.GetPosition().x < HALF_SCREEN_SIZEX)
		{
			m_paddle.SetVelocity(XMFLOAT3(15.0f, 0.0f, 0.0f));
		}
		m_input->SetKeyUp('D');
	}
	else
	{
		m_paddle.SetVelocity(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
}

//collision detection and resolution
void BreakoutApp::CheckCollisions()
{
	for (auto brick : m_bricks)
	{
		if (AabbCollide(*brick, m_ball))
		{
			brick->Hit();
			m_ball.Hit(brick->GetMaxHits() + 1);
		}
	}
	
	if (AabbCollide(m_paddle, m_ball))
	{
		m_ball.Hit();
	}	
	Cleanup();
}

bool BreakoutApp::AabbCollide(GameObject object1, GameObject object2)
{
	//get the max and min of the bounding box
	XMFLOAT3 firstmin = object1.GetAabb().min_vtx();
	XMFLOAT3 firstmax = object1.GetAabb().max_vtx();
	XMFLOAT3 secondmin = object2.GetAabb().min_vtx();
	XMFLOAT3 secondmax = object2.GetAabb().max_vtx();

	//calculate dimensions of object1
	float firstwidth = firstmax.x - firstmin.x;
	float firstheight = firstmax.y - firstmin.y;
	float firstlength = firstmax.z - firstmin.z;

	//calculate dimensions of object2
	float secondwidth = secondmax.x - secondmin.x;
	float secondheight = secondmax.y - secondmin.y;
	float secondlength = secondmax.z - secondmin.z;

	//if right side of object 1 is less than left side of object 2
	//not checking for z bounding
	if (object1.GetPosition().x + (firstwidth / 2) < object2.GetPosition().x - (secondwidth / 2))
		return false;
	//if left side of object 1 is greater than right side of object 2
	if (object1.GetPosition().x - (firstwidth / 2) > object2.GetPosition().x + (secondwidth / 2))
		return false;
	//if bottom side of object 1 is less than top side of object 2
	if (object1.GetPosition().y + (firstheight / 2) < object2.GetPosition().y - (secondheight / 2))
		return false;
	//if top side of object 1 is greater than bottom side of object 2
	if (object1.GetPosition().y - (firstheight / 2) > object2.GetPosition().y + (secondheight / 2))
		return false;
	//if front side of object 1 is less than back side of object 2
	//if (object1.GetPosition().z + (firstlength / 2) < object2.GetPosition().z - (secondlength / 2))
	//	return false;
	//if back side of object 1 is less than front side of object 2
	//if (object1.GetPosition().z - (firstlength / 2) > object2.GetPosition().z + (secondlength / 2))
	//	return false;
	return true;
}

//delete any objects flagged for deletion last update
void BreakoutApp::Cleanup()
{
	for (int i = 0; i < m_bricks.size(); i++)
	{
		if (m_bricks[i]->GetDeleteFlag())
		{
			m_bricks.erase(m_bricks.begin() + i);
		}
	}
}