#include "Prerequisites.h"
#include "BaseApp.h"

BaseApp app; // Instancia de la clase BaseApp


extern IMGUI_IMPL_API 
LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, 
																			 UINT msg, 
																			 WPARAM wParam, 
																			 LPARAM lParam);

// Called every time the application receives a message
LRESULT CALLBACK
WndProc(HWND hWnd,
				unsigned int message,
				WPARAM wParam,
				LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
    app.resizeWindow(hWnd, lParam);
    break;

	case WM_DESTROY:
			PostQuitMessage(0);
			break;

   //Agregar los siguientes casos para manejar los inputs de teclado
	case WM_KEYDOWN:
    app.keys[wParam] = true;
    break;

  case WM_KEYUP:
    app.keys[wParam] = false;
    break;

	case WM_RBUTTONDOWN:
		app.mouseLeftDown = true;
		break;

	case WM_RBUTTONUP:
		app.mouseLeftDown = false;
		break;

	case WM_MOUSEMOVE:
		if (app.mouseLeftDown) {
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			app.rotateCamera(x, y);
		}
		break;

		default:
			return DefWindowProc(hWnd, 
													 message,
													 wParam, 
													 lParam);
		}

		return 0;
	}
// Entry point for the application
int WINAPI
wWinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPWSTR lpCmdLine,
					 int nCmdShow) {
		return app.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
	}

		