// System.h
#pragma once

#define WIN32_LEAN_AND_MEAN

// INCLUDES 
#include <windows.h>
#include "BreakoutApp.h"
#include "Input.h"

class System
{
public:
	System();
	~System();

	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	
	BreakoutApp* m_Application;
	Input m_input;

//Prototypes
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};

//Globals
static System* ApplicationHandle = 0;
