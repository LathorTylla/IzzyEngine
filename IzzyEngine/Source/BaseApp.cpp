#include "BaseApp.h"

HRESULT
BaseApp::init() {
	return E_NOTIMPL;
}

void
BaseApp::update() {
}

void
BaseApp::render() {
}

void
BaseApp::destroy() {
}

int
BaseApp::run(HINSTANCE hInstance,
						 HINSTANCE hPrevInstance,
						 LPWSTR lpCmdLine,
						 int nCmdShow,
						 WNDPROC wndproc) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  //if (FAILED(g_window.init(hInstance, nCmdShow, WndProc)))
    //return 0;

  if (FAILED(init())) {
    destroy();
    return 0;
  }

  // Main message loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else {
      update();
      render();
    }
  }

  destroy();

  return (int)msg.wParam;

  return 0;
}
	