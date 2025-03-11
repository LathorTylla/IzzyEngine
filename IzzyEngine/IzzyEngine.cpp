#include "Prerequisites.h"
#include "BaseApp.h"

BaseApp app;

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK
WndProc(HWND hWnd,
				unsigned int message,
				WPARAM wParam,
				LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	//case WM_SIZE:

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, 
													 message,
													 wParam, 
													 lParam);
		}

		return 0;
	}
	int WINAPI
	wWinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPWSTR lpCmdLine,
					 int nCmdShow) {
		return app.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
	}

		