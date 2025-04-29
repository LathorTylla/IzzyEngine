#include "Device.h"

void
Device::destroy() {
  SAFE_RELEASE(m_device);	//Liberar el dispositivo
}

HRESULT
Device::CreateRenderTargetView(ID3D11Resource* pResource,
															 const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
															 ID3D11RenderTargetView** ppRTView) {
	//Validar parametros de etrada
	if (!pResource) {
		ERROR("Device", "CreateRenderTargetView", "pResource is nullptr");
		return E_INVALIDARG; //Argumento Invalido
	}

	if (!ppRTView) {
		ERROR("Device", "CreateRenderTargetView", "ppRTView is nullptr");
		return E_POINTER;//Puntero Nulo
	}

	//Crear el render target view
	HRESULT hr = m_device->CreateRenderTargetView(pResource, 
																								pDesc, 
																								ppRTView);

	if (SUCCEEDED(hr)) {
		MESSAGE("Device", "CreateRenderTargetView", "Render Target View created Successfully");
	}
	else {
		std::wstring errorMsg = L"Failed to create Render Target View. HRESULT: " + std::to_wstring(hr);
		ERROR(L"Device", L"CreateRenderTargetView", errorMsg);
	}
	return hr;
}

HRESULT
Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
												const D3D11_SUBRESOURCE_DATA* pInitialData,
												ID3D11Texture2D** ppTexture2D) {
	//Validar parametros de entrada
	if (!pDesc) {
		ERROR("Device", "CreateTexture2D", "pDesc is nullptr");

		return E_INVALIDARG;
	}
	if (!ppTexture2D) {
		ERROR("Device", "CreateTexture2D", "ppTexture2D is nullptr");
		return E_POINTER;
	}
  //Crear la textura 2D
	HRESULT hr = m_device->CreateTexture2D(pDesc, 
																				 pInitialData, 
																				 ppTexture2D);

	if (SUCCEEDED(hr)) {
		MESSAGE("Device", "CreateTexture2D", "Texture 2D created Successfully");
	}
	else {
		std::wstring errorMsg = L"Failes to create Texture 2D. HRESULT: " + std::to_wstring(hr);
		ERROR(L"Device", L"CreateTexture2D", errorMsg);
	}
	return hr;
}
	

HRESULT
Device::CreateDepthStencilView(ID3D11Resource* pResource,
															 const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
															 ID3D11DepthStencilView** ppDepthStencilView) {
	//validara parametros de entrada
	if (!pResource) {
		ERROR("Device", "CreateDepthStencilView", "pResource is nullptr");
		return E_INVALIDARG;
	}
	if (!ppDepthStencilView) {
		ERROR("Device", "CreateDepthStencilView", "ppDepthStencilView is nullptr");
		return E_POINTER;
	}

  //Crear el depth stencil view
	HRESULT hr = m_device->CreateDepthStencilView(pResource, 
																								pDesc, 
																								ppDepthStencilView);

		if (SUCCEEDED(hr)) {
			MESSAGE("Device", "CreateDepthStencilView", "DepthStencilView created Successfully");
		}
		else {
			ERROR("Device", "CreateDepthStencilView",
			("Failed to create DepthStencilView. HRESULT: " + std::to_string(hr)).c_str());
		}
		return hr;
}

HRESULT
Device::CreateVertexShader(const void* pShaderBytecode,
													 unsigned int BytecodeLength,
												 	ID3D11ClassLinkage* pClassLinkage,
													ID3D11VertexShader** ppVertexShader) {
	//validara parametros de entrada
	if (!pShaderBytecode) {
		ERROR("Device", "CreateVertexShader", "pShaderBytecode is nullptr");
		return E_INVALIDARG;
	}
	if (!ppVertexShader) {
		ERROR("Device", "CreateVertexShader", "ppVertexShader is nullptr");
		return E_POINTER;
	}

  //Crear el vertex shader
	HRESULT hr = m_device->CreateVertexShader(pShaderBytecode, 
																						BytecodeLength, 
																						pClassLinkage, 
																						ppVertexShader);

	if (SUCCEEDED(hr)) {
		MESSAGE("Device", "CreateDepthStencilView", "VertexShader created Successfully");
	}
	else {
			ERROR("Device", "CreateVertexShader",
			("Failed to create VertexShader. HRESULT: " + std::to_string(hr)).c_str());
	}
	return hr;

}

//Crear el Input Layout
HRESULT
Device::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
													unsigned int NumElements,
													const void* pShaderBytecodeWithInputSignature,
													unsigned int BytecodeLength,
													ID3D11InputLayout** ppInputLayout){
	if (!pInputElementDescs) {
		ERROR("Device", "CreateInputLayout", "pInputElementDescs is nullptr");
		return E_INVALIDARG;
	}
	if (!ppInputLayout) {
		ERROR("Device", "CreateInputLayout", "ppInputLayout is nullptr");
		return E_POINTER;
	}

  //Crear el input layout
	HRESULT hr = m_device->CreateInputLayout(pInputElementDescs, 
																					 NumElements, 
																					 pShaderBytecodeWithInputSignature, 
																					 BytecodeLength, 
																					 ppInputLayout);

	if (SUCCEEDED(hr)) {
		MESSAGE("Device", "CreateInputLayout", "InputLayout created successfully");
	}
	else {
		ERROR("Device", "CreateInputLayout",
			("Failed to create InputLayout. HRESULT: " + std::to_string(hr)).c_str());
	}

	return hr;
}

HRESULT
Device::CreatePixelShader(const void* pShaderBytecode,
													unsigned int BytecodeLength,
													ID3D11ClassLinkage* pClassLinkage,
													ID3D11PixelShader** ppPixelShader) {
	if (!pShaderBytecode) {
		ERROR("Device", "CreatePixelShader", "pShaderBytecode is nullptr");
		return E_INVALIDARG;
	}
	if (!ppPixelShader) {
		ERROR("Device", "CreatePixelShader", "ppPixelShader is nullptr");
		return E_POINTER;
	}

  //Crear el pixel shader
	HRESULT hr = m_device->CreatePixelShader(pShaderBytecode,
																					 BytecodeLength, 
																					 pClassLinkage, 
																					 ppPixelShader);

	if (SUCCEEDED(hr)) {
		MESSAGE("Device", "CreatePixelShader", "PixelShader created successfully");
	}
	else {
		ERROR("Device", "CreatePixelShader",
			("Failed to create PixelShader. HRESULT: " + std::to_string(hr)).c_str());
	}

	return hr;
}

HRESULT
Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
										const D3D11_SUBRESOURCE_DATA* pInitialData,
										ID3D11Buffer** ppBuffer) {
	if (!pDesc) {
		ERROR("Device", "CreateBuffer", "pDesc is nullptr");
		return E_INVALIDARG;
	}
	if (!ppBuffer) {
		ERROR("Device", "CreateBuffer", "ppBuffer is nullptr");
		return E_POINTER;
	}

  //Crear el buffer
	HRESULT hr = m_device->CreateBuffer(pDesc, 
																			pInitialData, 
																			ppBuffer);

	if (SUCCEEDED(hr)) {
		MESSAGE("Device", "CreateBuffer", "Buffer created successfully");
	}
	else {
		ERROR("Device", "CreateBuffer",
			("Failed to create Buffer. HRESULT: " + std::to_string(hr)).c_str());
	}

	return hr;
}

HRESULT
Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
													 ID3D11SamplerState** ppSamplerState) {
	if (!pSamplerDesc) {
		ERROR("Device", "CreateSamplerState", "pSamplerDesc is nullptr");
		return E_INVALIDARG;
	}
	if (!ppSamplerState) {
		ERROR("Device", "CreateSamplerState", "ppSamplerState is nullptr");
		return E_POINTER;
	}

  //Crear el sampler state
	HRESULT hr = m_device->CreateSamplerState(pSamplerDesc, 
																						ppSamplerState);

	if (SUCCEEDED(hr)) {
		MESSAGE("Device", "CreateSamplerState", "SamplerState created successfully");
	}
	else {
		ERROR("Device", "CreateSamplerState",
			("Failed to create SamplerState. HRESULT: " + std::to_string(hr)).c_str());
	}

	return hr;
}