#include "Device.h"

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
	HRESULT hr = m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);

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

	return E_NOTIMPL;
}

HRESULT
Device::CreateDepthStencilView(ID3D11Resource* pResource,
															 const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
															 ID3D11DepthStencilView** ppDepthStencilView) {
	return E_NOTIMPL;
}

HRESULT
Device::CreateVertexShader(const void* pShaderBytecode,
													 SIZE_T BytecodeLength,
												 	ID3D11ClassLinkage* pClassLinkage,
													ID3D11VertexShader** ppVertexShader) {
	return E_NOTIMPL;

}

HRESULT
Device::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
													UINT NumElements,
													const void* pShaderBytecodeWithInputSignature,
													SIZE_T BytecodeLength,
													ID3D11InputLayout** ppInputLayout){
	return E_NOTIMPL;
}
HRESULT
Device::CreatePixelShader(const void* pShaderBytecode,
													SIZE_T BytecodeLength,
													ID3D11ClassLinkage* pClassLinkage,
													ID3D11PixelShader** ppPixelShader) {
	return E_NOTIMPL;
}

HRESULT
Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
										const D3D11_SUBRESOURCE_DATA* pInitialData,
										ID3D11Buffer** ppBuffer) {
	return E_NOTIMPL;
}

HRESULT
Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
													 ID3D11SamplerState** ppSamplerState) {
	return E_NOTIMPL;
}
