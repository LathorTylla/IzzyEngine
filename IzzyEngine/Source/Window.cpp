#pragma once
#include "Window.h"

HRESULT
Window::init(HINSTANCE hInstance, 
						 int nCmdShow, 
						 WNDPROC wndproc) {

  m_hInst = hInstance;	// Store instance handle

	//Register class
	WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);	//size of the structure
  wcex.style = CS_HREDRAW | CS_VREDRAW;	//style of the window
	wcex.lpfnWndProc = wndproc;	
	wcex.cbClsExtra = 0;	
	wcex.cbWndExtra = 0;	
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;	
	wcex.lpszClassName = "TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);


	if (!RegisterClassEx(&wcex)) {
		MessageBox(nullptr, "RegisterClassEX Failed!", "Error", MB_OK);
		ERROR("Window", "init", "CHECK FOR RegisterClassEx");
		return E_FAIL;
	}

	// Create window
	RECT rc = { 0, 0, 1200, 1080 };
	m_rect = rc;

	AdjustWindowRect(&rc, 
									 WS_OVERLAPPEDWINDOW, 
									 FALSE);

	m_hWnd = CreateWindow("TutorialWindowClass",
												m_windowName.c_str(),
												WS_OVERLAPPEDWINDOW,
												CW_USEDEFAULT, 
												CW_USEDEFAULT, 
												m_rect.right - m_rect.left,
												m_rect.bottom - m_rect.top,
												NULL, 
												NULL, 
												m_hInst,
												NULL);
	if (!m_hWnd) {
		MessageBox(nullptr, "CreateWindow failed!", "Error", MB_OK);
		ERROR("Window", "init", "CHECK FOR CreateWindow()");
		return E_FAIL;
	}
	
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	//Setup Viewport Dimensions
	GetClientRect(m_hWnd, &m_rect);
	m_width = m_rect.right - m_rect.left;	
	m_height = m_rect.bottom - m_rect.top;

	return S_OK;
}


	void 
	Window::update() {

	}

	void
	Window::render() {

	}

	void
	Window::destroy() {

	}

