#pragma once
#include "PreRequisites.h"

/*
 * @brief DeviceContext.
 *
 * Clase encargada de gestionar y ejecutar el renderizado.
 * Se encarga de administrar el flujo de trabajo entre la CPU y la GPU, asegurando que los recursos gráficos
 * sean configurados correctamente antes de la renderización.
 */
class
DeviceContext {
public:
	DeviceContext() = default;
	~DeviceContext() = default;

	/*
	 * @brief Inicializa el DeviceContext.
	 */
	void
	init();

	/*
	 * @brief Actualiza la lógica del DeviceContext.
	 */
	void
	update();

	/*
	 * @brief Ejecuta el proceso de renderizado en el DeviceContext.
	 */
	void
	render();

	/*
	 * @brief Libera los recursos utilizados por el DeviceContext.
	 */
	void
	destroy();

	/*
	 * @brief Configura los Viewports utilizados para la renderización.
	 *
	 * @param NumViewports Número de viewports a establecer.
	 * @param pViewports   Puntero a los datos de los viewports.
	 */
	void
	RSSetViewports(unsigned int NumViewports, 
								 const D3D11_VIEWPORT* pViewports);

	/*
	 * @brief Asigna recursos de textura al Pixel Shader.
	 */
	void
	PSSetShaderResources(unsigned int StartSlot,
											 unsigned int NumViews,
											 ID3D11ShaderResourceView* const* ppShaderResourceViews);

	/*
	 * @brief Establece el InputLayout para definir la estructura de los vértices en la GPU.
	 */
	void
	IASetInputLayout(ID3D11InputLayout* pInputLayout);

	/*
	 * @brief Asigna el Vertex Shader a utilizar en el pipeline de renderizado.
	 */
	void
	VSSetShader(ID3D11VertexShader* pVertexShader,
							ID3D11ClassInstance* const* ppClassInstances,
							unsigned int NumClassInstances);

	/*
	 * @brief Asigna el Pixel Shader a utilizar en el pipeline de renderizado.
	 */
	void
	PSSetShader(ID3D11PixelShader* pPixelShader,
							ID3D11ClassInstance* const* ppClassInstances,
							unsigned int NumClassInstances);

	/*
	 * @brief Actualiza un recurso en la GPU con nuevos datos.
	 */
	void
	UpdateSubresource(ID3D11Resource* pDstResource,
										unsigned int DstSubresource,
										const D3D11_BOX* pDstBox,
										const void* pSrcData,
										unsigned int SrcRowPitch,
										unsigned int SrcDepthPitch);

	/*
	 * @brief Configura los Vertex Buffers utilizados en la etapa de Input Assembler.
	 */
	void
	IASetVertexBuffers(unsigned int StartSlot,
										 unsigned int NumBuffers,
									 	 ID3D11Buffer* const* ppVertexBuffers,
										 const unsigned int* pStrides,
										 const unsigned int* pOffsets);

	/*
	 * @brief Establece el Index Buffer para su uso en la renderización de modelos indexados.
	 */
	void
	IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
									 DXGI_FORMAT Format,
							 		 unsigned int Offset);

	/*
	 * @brief Asigna los Samplers al Pixel Shader para el muestreo de texturas.
	 */
	void
	PSSetSamplers(unsigned int StartSlot,
								unsigned int NumSamplers,
								ID3D11SamplerState* const* ppSamplers);

	/*
	 * @brief Configura el estado de rasterización de la escena.
	 */
	void
	RSSetState(ID3D11RasterizerState* pRasterizerState);

	/*
	 * @brief Configura el BlendState para aplicar transparencias o combinaciones de colores.
	 */
	void
	OMSetBlendState(ID3D11BlendState* pBlendState,
									const float BlendFactor[4],
									unsigned int SampleMask);

	/*
	 * @brief Establece los Render Targets y Depth Stencil utilizados en la renderización.
	 */
	void
	OMSetRenderTargets(unsigned int NumViews,
										 ID3D11RenderTargetView* const* ppRenderTargetViews,
										 ID3D11DepthStencilView* pDepthStencilView);

	/*
	 * @brief Define la topología de los primitivos a renderizar.
	 */
	void
	IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

	/*
	 * @brief Limpia el Render Target con un color especificado.
	 */
	void
	ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
												const float ColorRGBA[4]);

	/*
	 * @brief Limpia el Depth Stencil Buffer para evitar residuos de frames anteriores.
	 */
	void
	ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
												unsigned int ClearFlags,
												float Depth,
												UINT8 Stencil);

	/*
	 * @brief Asigna buffers constantes al Vertex Shader.
	 */
	void
	VSSetConstantBuffers(unsigned int StartSlot,
											 unsigned int NumBuffers,
											 ID3D11Buffer* const* ppConstantBuffers);

	/*
	 * @brief Asigna buffers constantes al Pixel Shader.
	 */
	void
	PSSetConstantBuffers(unsigned int StartSlot,
											 unsigned int NumBuffers,
											 ID3D11Buffer* const* ppConstantBuffers);

	/*
	 * @brief Dibuja los elementos utilizando un índice de buffer previamente configurado.
	 */
	void
	DrawIndexed(unsigned int IndexCount,
							unsigned int StartIndexLocation,
							int BaseVertexLocation);

private:

public:

	/*
	 * @brief Puntero a ID3D11DeviceContext.
	 *
	 * Encargado de gestionar la comunicación entre CPU y GPU en DirectX 11.
	 */
	ID3D11DeviceContext* m_deviceContext = nullptr;
};