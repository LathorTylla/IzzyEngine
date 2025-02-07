#pragma once
#include "Prerequisites.h"

//Forward Declarations

class Device;
class DeviceContext;
class Window;
class Texture;

class 
Swapchain{
public:
	Swapchain() = default;
	~Swapchain() = default;

	HRESULT
		init(Device& device,
				 DeviceContext& deviceContext,
				 Texture& backBuffer,
				 Window window);

	void 
	update();

	void 
	render();

	void 
	destroy();

	void 
	present();

public:
	IDXGISwapChain* m_swapChain = nullptr;
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
private:
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

	unsigned int m_sampleCount;
	unsigned int m_qualityLevels;

	IDXGIDevice* m_dxgiDevice = nullptr;
	IDXGIAdapter* m_dxgiAdapter = nullptr;
	IDXGIFactory* m_dxgiFactory = nullptr;



private:

};