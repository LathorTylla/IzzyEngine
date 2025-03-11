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
		//	if (g_swapchain.m_swapchain) {
		//		g_window.m_width = LOWORD(lParam);
		//		g_window.m_height = HIWORD(lParam);

		//		// Libera los recursos existentes
		//		g_renderTargetView.destroy();
		//		g_depthStencilView.destroy();
		//		g_depthStencil.destroy();
		//		g_backBuffer.destroy();

		//		// Redimensionar el swap chain
		//		HRESULT hr = g_swapchain.m_swapchain->ResizeBuffers(0,
		//																												g_window.m_width,
		//																												g_window.m_height,
		//																												DXGI_FORMAT_R8G8B8A8_UNORM,
		//																												0);
		//		if (FAILED(hr)) {
		//			MessageBox(hWnd, "Failed to resize swap chain buffers.", "Error", MB_OK);
		//			PostQuitMessage(0);
		//		}

		//		// **3. RECREAR EL BACK BUFFER**
		//		hr = g_swapchain.m_swapchain->GetBuffer(0,
		//																						__uuidof(ID3D11Texture2D),
		//																						reinterpret_cast<void**>(&g_backBuffer.m_texture));
		//		if (FAILED(hr)) {
		//			ERROR("SwapChain", "Resize", "Failed to get new back buffer");
		//			return hr;
		//		}

		//		// **4. RECREAR EL RENDER TARGET VIEW**
		//		hr = g_renderTargetView.init(g_device,
		//																 g_backBuffer,
		//																 DXGI_FORMAT_R8G8B8A8_UNORM);
		//		if (FAILED(hr)) {
		//			ERROR("RenderTargetView", "Resize", "Failed to create new RenderTargetView");
		//			return hr;
		//		}

		//		// **5. RECREAR EL DEPTH STENCIL VIEW**
		//		hr = g_depthStencil.init(g_device,
		//														 g_window.m_width,
		//														 g_window.m_height,
		//														 DXGI_FORMAT_D24_UNORM_S8_UINT,
		//														 D3D11_BIND_DEPTH_STENCIL,
		//														 4,
		//														 0);
		//		if (FAILED(hr)) {
		//			ERROR("DepthStencil", "Resize", "Failed to create new DepthStencil");
		//			return hr;
		//		}

		//		hr = g_depthStencilView.init(g_device,
		//																 g_depthStencil,
		//																 DXGI_FORMAT_D24_UNORM_S8_UINT);
		//		if (FAILED(hr)) {
		//			ERROR("DepthStencilView", "Resize", "Failed to create new DepthStencilView");
		//			return hr;
		//		}
		//		
	 //     hr = g_viewport.init(g_window);
	 //     if (FAILED(hr)) {
	 //       ERROR("Viewport", "Resize", "Failed to create new Viewport");
	 //       return hr;
	 //     }

		//		// Actualizar la proyección
		//		g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, 
		//																						g_window.m_width / (float)g_window.m_height, 
		//																						0.01f, 
		//																						100.0f);
		//		CBChangeOnResize cbChangesOnResize;
		//		cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
		//		g_changeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
		//	}
		//	break;

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

		