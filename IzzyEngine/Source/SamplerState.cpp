#include "SamplerState.h"
 #include "Device.h"
 #include "DeviceContext.h"
 
 HRESULT 
 SamplerState::init(Device& device) {
   if (!device.m_device) {
     ERROR("SamplerState", "init", "Device is nullptr");
     return E_POINTER;
   }
 
   // Check if the sampler state is already created
   D3D11_SAMPLER_DESC sampDesc = {};  // Initialize the sampler description
   sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;// Linear filter
   sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;  // Wrap address mode
   sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;  
   sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;  
   sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;  
   sampDesc.MinLOD = 0; // Minimum LOD
   sampDesc.MaxLOD = D3D11_FLOAT32_MAX; // Maximum LOD
 
   HRESULT hr = device.CreateSamplerState(&sampDesc, &m_sampler); // Create the sampler state
   if (FAILED(hr)) {
     ERROR("SamplerState", "init", "Failed to create SamplerState");
     return hr;
   }
 
   return S_OK;
 }
 
 void 
 SamplerState::update() {
  
 }
 
 void 
 SamplerState::render(DeviceContext& deviceContext, 
                      unsigned int StartSlot, 
                      unsigned int NumSamplers) {
   if (!m_sampler) {
     ERROR("SamplerState", "render", "SamplerState is nullptr");
     return;
   }
 
   deviceContext.PSSetSamplers(StartSlot, NumSamplers, &m_sampler); // Set the sampler state
 }
 
 void 
 SamplerState::destroy() {
   if (m_sampler) {
     SAFE_RELEASE(m_sampler); // Release the sampler state
   }
 }