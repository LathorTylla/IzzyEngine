#pragma once
#include "Prerequisites.h"

class 
Device{
public:
	Device() = default;
	~Device() = default;

	void
	init();

	void 
	update();

	void 
	render();

	void 
	destroy();

	HRESULT
	STDMETHODCALLTYPE CreateRenderTargetView(ID3D11Resource* pResource,
																						 const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
																						 ID3D11RenderTargetView** ppRTView);

	HRESULT
	STDMETHODCALLTYPE CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
																			const D3D11_SUBRESOURCE_DATA* pInitialData,
																			ID3D11Texture2D** ppTexture2D);

	HRESULT
	STDMETHODCALLTYPE CreateDepthStencilView(ID3D11Resource* pResource,
																						 const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
																						 ID3D11DepthStencilView** ppDepthStencilView);

	HRESULT
	STDMETHODCALLTYPE CreateVertexShader(const void* pShaderBytecode,
																				 unsigned int BytecodeLength,
																				 ID3D11ClassLinkage* pClassLinkage,
																				 ID3D11VertexShader** ppVertexShader);

	HRESULT
	STDMETHODCALLTYPE CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
																			  unsigned int NumElements,
																				const void* pShaderBytecodeWithInputSignature,
																				unsigned int BytecodeLength,
																				ID3D11InputLayout** ppInputLayout);
	HRESULT
	STDMETHODCALLTYPE CreatePixelShader(const void* pShaderBytecode,
																				unsigned int BytecodeLength,
																				ID3D11ClassLinkage* pClassLinkage,
																				ID3D11PixelShader** ppPixelShader);

	HRESULT
	STDMETHODCALLTYPE CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
																   const D3D11_SUBRESOURCE_DATA* pInitialData,
																   ID3D11Buffer** ppBuffer);

	HRESULT 
	STDMETHODCALLTYPE CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
																				ID3D11SamplerState** ppSamplerState);
public:
	ID3D11Device* m_device = nullptr;
};