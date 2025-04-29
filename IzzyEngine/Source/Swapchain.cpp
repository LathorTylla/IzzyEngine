#include "Swapchain.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "Window.h"

HRESULT
SwapChain::init(Device& device,
								DeviceContext& deviceContext,
								Texture& backBuffer,
								Window window) {

  if (!window.m_hWnd) {
    ERROR("SwapChain", "init", "Invalid Window handle (m_hWnd is nullptr)");
    return E_POINTER;
  }

	HRESULT hr = S_OK;

	unsigned int createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_DRIVER_TYPE
		driverTypes[] = {
				D3D_DRIVER_TYPE_HARDWARE,
				D3D_DRIVER_TYPE_WARP,
				D3D_DRIVER_TYPE_REFERENCE,
	};
	unsigned int numDriverTypes = ARRAYSIZE(driverTypes);
	D3D_FEATURE_LEVEL
		featureLevels[] = {
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
	};
  unsigned int numFeatureLevels = ARRAYSIZE(featureLevels);
  // Intentar crear el dispositivo con cada driver
  for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
    m_driverType = driverTypes[driverTypeIndex];
    hr = D3D11CreateDevice( nullptr,
                            m_driverType,
                            nullptr,
                            createDeviceFlags,
                            featureLevels,
                            numFeatureLevels,
                            D3D11_SDK_VERSION,
                            &device.m_device,
                            &m_featureLevel,
                            &deviceContext.m_deviceContext);
    if (SUCCEEDED(hr))
      break;
  }
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to create D3D11 device");
    return hr;
  }
  // Configurar MSAA
  m_sampleCount = 4;
  hr = device.m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 
                                                      m_sampleCount, 
                                                      &m_qualityLevels);
  if (FAILED(hr) || m_qualityLevels == 0) {
    ERROR("SwapChain", "init", "MSAA not supported or invalid quality level");
    return hr;
  }
  // Configurar la descripción del SwapChain
  DXGI_SWAP_CHAIN_DESC sd;  // Inicializar la descripción
  memset(&sd, 0, sizeof(sd));  // Limpiar la descripción
  sd.BufferCount = 1; // Número de buffers
  sd.BufferDesc.Width = window.m_width; // Ancho de la ventana
  sd.BufferDesc.Height = window.m_height; // Alto de la ventana
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Formato de color
  sd.BufferDesc.RefreshRate.Numerator = 60; // Tasa de refresco
  sd.BufferDesc.RefreshRate.Denominator = 1;  // Tasa de refresco
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Uso del buffer
  sd.OutputWindow = window.m_hWnd; // Ventana de salida
  sd.Windowed = TRUE; // Ventana en modo ventana
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Efecto de intercambio
  sd.SampleDesc.Count = m_sampleCount; // Número de muestras
  sd.SampleDesc.Quality = m_qualityLevels - 1;  // Máxima calidad

  // Obtener la fábrica DXGI
  hr = device.m_device->QueryInterface(__uuidof(IDXGIDevice), 
                                       reinterpret_cast<void**>(&m_dxgiDevice));
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to query IDXGIDevice");
    return hr;
  }
  hr = m_dxgiDevice->GetAdapter(&m_dxgiAdapter);
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to get DXGI Adapter");
    return hr;
  }
  hr = m_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), 
                                reinterpret_cast<void**>(&m_dxgiFactory));
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to get DXGI Factory");
    return hr;
  }
  // Crear SwapChain
  hr = m_dxgiFactory->CreateSwapChain(device.m_device, 
                                      &sd, 
                                      &m_swapchain);
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to create SwapChain");
    return hr;
  }
  // Obtener el buffer trasero
  hr = m_swapchain->GetBuffer(0, 
                              __uuidof(ID3D11Texture2D), 
                              reinterpret_cast<void**>(&backBuffer.m_texture));
  if (FAILED(hr)) {
    ERROR("SwapChain", "init", "Failed to get SwapChain buffer");
    return hr;
  }
  return S_OK;
  }

  void 
  SwapChain::update() {
   
  }

  void 
  SwapChain::render() {
  }

  void 
  SwapChain::destroy() {
    SAFE_RELEASE(m_swapchain);   // Liberar el swap chain
    SAFE_RELEASE(m_dxgiFactory); // Liberar la fábrica DXGI
    SAFE_RELEASE(m_dxgiAdapter); // Liberar el adaptador DXGI
    SAFE_RELEASE(m_dxgiDevice);  // Liberar el dispositivo DXGI
  }
  void 
  SwapChain::present() {
    if (m_swapchain) {
      // Presentar el swap chain
      HRESULT hr = m_swapchain->Present(0, 0);
      if (FAILED(hr)) {
        ERROR("SwapChain", "present", "Failed to present swap chain");
      }
    }
    else {
      ERROR("SwapChain", "present", "SwapChain is nullptr");
    }
}