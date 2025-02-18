#include "InputLayout.h"
#include "Device.h"
#include "DeviceContext.h"


HRESULT 
InputLayout::init(Device& device, 
                  std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout, 
                  ID3DBlob* VertexShaderData){
  if (Layout.empty()) {
    ERROR("InputLayout", "init", "Invalid Layout (empty)");
    return E_INVALIDARG;
  }
  if (!VertexShaderData) {
    ERROR("InputLayout", "init", "Invalid VertexShaderData (nullptr)");
    return E_INVALIDARG;
  }
  HRESULT hr = S_OK;
    
  hr = device.CreateInputLayout(Layout.data(), 
                                static_cast<unsigned int>(Layout.size()), 
                                VertexShaderData->GetBufferPointer(), 
                                VertexShaderData->GetBufferSize(), 
                                &m_inputLayout);
  if (FAILED(hr)) {
    ERROR("InputLayout", "init", "Failed to create Input Layout");
    return hr;
  }
  return S_OK;
}

void
InputLayout::update() {

}

void
InputLayout::render(DeviceContext& deviceContext) {
  if (!deviceContext.m_deviceContext) {
    ERROR("InputLayout", "render", "Invalid Device Context (m_deviceContext is nullptr)");
    return;
  }
  deviceContext.IASetInputLayout(m_inputLayout);
}

void
InputLayout::destroy() {
  SAFE_RELEASE(m_inputLayout);
}
