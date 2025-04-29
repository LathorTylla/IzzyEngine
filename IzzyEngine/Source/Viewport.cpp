#include "Viewport.h"
#include "Window.h"
#include "DeviceContext.h"

HRESULT 
Viewport::init(const Window& window){
  if (!window.m_hWnd) {
    ERROR("Viewport", "init", "Invalid Window handle (m_hWnd is nullptr)");
    return E_POINTER;
  }
  if (window.m_width == 0 || window.m_height == 0) {
    ERROR("Viewport", "init", "Invalid Window dimensions (width or height is zero)");
    return E_INVALIDARG;
  }
  m_viewport.Width = static_cast<float>(window.m_width);  // Set the width of the viewport
  m_viewport.Height = static_cast<float>(window.m_height);  // Set the height of the viewport
  m_viewport.MinDepth = 0.0f; // Set the minimum depth of the viewport
  m_viewport.MaxDepth = 1.0f; // Set the maximum depth of the viewport
  m_viewport.TopLeftX = 0;  // Set the top left X coordinate of the viewport
  m_viewport.TopLeftY = 0;  // Set the top left Y coordinate of the viewport
  return S_OK;
}

HRESULT
Viewport::init(unsigned int width,
               unsigned int height) {
  if (width == 0 || height == 0) {
    ERROR("Viewport", "init", "Invalid dimensions (width or height is zero)");
    return E_INVALIDARG;
  }
  m_viewport.Width = static_cast<float>(width); // Set the width of the viewport
  m_viewport.Height = static_cast<float>(height); // Set the height of the viewport
  m_viewport.MinDepth = 0.0f; // Set the minimum depth of the viewport
  m_viewport.MaxDepth = 1.0f; // Set the maximum depth of the viewport
  m_viewport.TopLeftX = 0;  // Set the top left X coordinate of the viewport
  m_viewport.TopLeftY = 0;  // Set the top left Y coordinate of the viewport
  return S_OK;
}

void 
Viewport::update(){
 
}

void 
Viewport::render(DeviceContext& deviceContext){
  if (!deviceContext.m_deviceContext) {
    ERROR("Viewport", "render", "Invalid Device Context (m_deviceContext is nullptr)");
    return;
  }
  deviceContext.RSSetViewports(1, &m_viewport); // Set the viewport
  
}

void 
Viewport::destroy(){ 
}
