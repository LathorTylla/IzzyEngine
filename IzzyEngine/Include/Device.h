#pragma once
#include "Prerequisites.h"

/*
 * @brief Device.
 *
 * Clase encargada de la creación y gestión de recursos gráficos en DirectX 11.
 * Proporciona métodos para inicializar, actualizar, renderizar y destruir.
 */
class 
Device{
public:
	Device() = default;
	~Device() = default;

	/*
	 * @brief Inicializa el Device y sus recursos asociados.
	 */
	void
	init();

	/*
	 * @brief Actualiza la lógica interna del Device.
	 */
	void 
	update();

	/*
	 * @brief Ejecuta el proceso de renderizado utilizando los recursos creados en el Device.
	 */
	void 
	render();

	/*
	 * @brief Libera los recursos utilizados por el Device.
	 */
	void 
	destroy();

	/*
	 * @brief Crea un RenderTargetView a partir de un recurso.
	 *
	 * @param pResource   Recurso base sobre el cual se creará el RenderTargetView.
	 * @param pDesc       Descripción del RenderTargetView.
	 * @param ppRTView    Puntero donde se almacenará la referencia al RenderTargetView creado.
	 * @return            Devuelve un HRESULT indicando el éxito o fallo de la operación.
	 */
	HRESULT
	CreateRenderTargetView(ID3D11Resource* pResource,
												 const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
												 ID3D11RenderTargetView** ppRTView);

	/*
	 * @brief Crea una textura 2D en memoria.
	 *
	 * @param pDesc       Descripción de la textura a crear.
	 * @param pInitialData Datos iniciales que se asignarán a la textura.
	 * @param ppTexture2D  Puntero donde se almacenará la referencia a la textura creada.
	 * @return            Devuelve un HRESULT indicando el éxito o fallo de la operación.
	 */
	HRESULT
	CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
									const D3D11_SUBRESOURCE_DATA* pInitialData,
									ID3D11Texture2D** ppTexture2D);

	/*  
   * @brief Crea una DepthStencilView utilizada para gestionar la profundidad en la escena.
   *
   * @param pResource          Recurso base sobre el cual se creará el DepthStencilView.
   * @param pDesc              Descripción de la vista del Depth Stencil.
   * @param ppDepthStencilView Puntero donde se almacenará la referencia al DepthStencilView creado.
   * @return                   Devuelve un HRESULT indicando el éxito o fallo de la operación.
   */
	HRESULT
	CreateDepthStencilView(ID3D11Resource* pResource,
												 const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
												 ID3D11DepthStencilView** ppDepthStencilView);

	/*
	 * @brief Crea un VertexShader a partir de los datos compilados del shader.
	 *
	 * @param pShaderBytecode Código binario del shader.
	 * @param BytecodeLength  Tamaño del código en bytes.
	 * @param pClassLinkage   Puntero opcional para el enlace de clases del shader.
	 * @param ppVertexShader  Puntero donde se almacenará la referencia al VertexShader creado.
	 * @return                Devuelve un HRESULT indicando el éxito o fallo de la operación.
	 */
	HRESULT
	CreateVertexShader(const void* pShaderBytecode,
										 unsigned int BytecodeLength,
										 ID3D11ClassLinkage* pClassLinkage,
										 ID3D11VertexShader** ppVertexShader);

	/*
	 * @brief Crea un InputLayout para definir la estructura de los vértices en la GPU.
	 *
	 * @param pInputElementDescs                 Arreglo que define los elementos del input layout.
	 * @param NumElements                        Número de elementos en el input layout.
	 * @param pShaderBytecodeWithInputSignature  Código del shader con la firma de entrada.
	 * @param BytecodeLength                     Tamaño del código en bytes.
	 * @param ppInputLayout                      Puntero donde se almacenará la referencia al InputLayout creado.
	 * @return                                   Devuelve un HRESULT indicando el éxito o fallo de la operación.
	 */
	HRESULT
	CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
										unsigned int NumElements,
										const void* pShaderBytecodeWithInputSignature,
										unsigned int BytecodeLength,
										ID3D11InputLayout** ppInputLayout);

	/*
	 * @brief Crea un PixelShader a partir de los datos compilados del shader.
	 *
	 * @param pShaderBytecode Código binario del shader.
	 * @param BytecodeLength  Tamaño del código en bytes.
	 * @param pClassLinkage   Puntero opcional para el enlace de clases del shader.
	 * @param ppPixelShader   Puntero donde se almacenará la referencia al PixelShader creado.
	 * @return                Devuelve un HRESULT indicando el éxito o fallo de la operación.
	 */
	HRESULT
	CreatePixelShader(const void* pShaderBytecode,
										unsigned int BytecodeLength,
										ID3D11ClassLinkage* pClassLinkage,
										ID3D11PixelShader** ppPixelShader);

	/*
	 * @brief Crea un buffer en la GPU para almacenar datos como vértices, índices o constantes.
	 *
	 * @param pDesc       Descripción del buffer.
	 * @param pInitialData Datos iniciales que se asignarán al buffer.
	 * @param ppBuffer    Puntero donde se almacenará la referencia al buffer creado.
	 * @return            Devuelve un HRESULT indicando el éxito o fallo de la operación.
	 */
	HRESULT
	CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
							 const D3D11_SUBRESOURCE_DATA* pInitialData,
							 ID3D11Buffer** ppBuffer);

	/*
	 * @brief Crea un SamplerState para definir cómo se aplicarán las texturas en la GPU.
	 *
	 * @param pSamplerDesc   Descripción del SamplerState.
	 * @param ppSamplerState Puntero donde se almacenará la referencia al SamplerState creado.
	 * @return               Devuelve un HRESULT indicando el éxito o fallo de la operación.
	 */
	HRESULT 
	CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
									   ID3D11SamplerState** ppSamplerState);
public:
	/*
	 * @brief Puntero a ID3D11Device.
	 *
	 * Encargado de la creación de todos los recursos en DirectX 11.
	 */
	ID3D11Device* m_device = nullptr;
};