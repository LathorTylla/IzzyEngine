#pragma once
#include "Prerequisites.h"

/*
 * @brief Device.
 *
 * Clase encargada de la creaci�n y gesti�n de recursos gr�ficos en DirectX 11.
 * Proporciona m�todos para inicializar, actualizar, renderizar y destruir.
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
	 * @brief Actualiza la l�gica interna del Device.
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
	 * @param pResource   Recurso base sobre el cual se crear� el RenderTargetView.
	 * @param pDesc       Descripci�n del RenderTargetView.
	 * @param ppRTView    Puntero donde se almacenar� la referencia al RenderTargetView creado.
	 * @return            Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
	 */
	HRESULT
	CreateRenderTargetView(ID3D11Resource* pResource,
												 const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
												 ID3D11RenderTargetView** ppRTView);

	/*
	 * @brief Crea una textura 2D en memoria.
	 *
	 * @param pDesc       Descripci�n de la textura a crear.
	 * @param pInitialData Datos iniciales que se asignar�n a la textura.
	 * @param ppTexture2D  Puntero donde se almacenar� la referencia a la textura creada.
	 * @return            Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
	 */
	HRESULT
	CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
									const D3D11_SUBRESOURCE_DATA* pInitialData,
									ID3D11Texture2D** ppTexture2D);

	/*  
   * @brief Crea una DepthStencilView utilizada para gestionar la profundidad en la escena.
   *
   * @param pResource          Recurso base sobre el cual se crear� el DepthStencilView.
   * @param pDesc              Descripci�n de la vista del Depth Stencil.
   * @param ppDepthStencilView Puntero donde se almacenar� la referencia al DepthStencilView creado.
   * @return                   Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
   */
	HRESULT
	CreateDepthStencilView(ID3D11Resource* pResource,
												 const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
												 ID3D11DepthStencilView** ppDepthStencilView);

	/*
	 * @brief Crea un VertexShader a partir de los datos compilados del shader.
	 *
	 * @param pShaderBytecode C�digo binario del shader.
	 * @param BytecodeLength  Tama�o del c�digo en bytes.
	 * @param pClassLinkage   Puntero opcional para el enlace de clases del shader.
	 * @param ppVertexShader  Puntero donde se almacenar� la referencia al VertexShader creado.
	 * @return                Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
	 */
	HRESULT
	CreateVertexShader(const void* pShaderBytecode,
										 unsigned int BytecodeLength,
										 ID3D11ClassLinkage* pClassLinkage,
										 ID3D11VertexShader** ppVertexShader);

	/*
	 * @brief Crea un InputLayout para definir la estructura de los v�rtices en la GPU.
	 *
	 * @param pInputElementDescs                 Arreglo que define los elementos del input layout.
	 * @param NumElements                        N�mero de elementos en el input layout.
	 * @param pShaderBytecodeWithInputSignature  C�digo del shader con la firma de entrada.
	 * @param BytecodeLength                     Tama�o del c�digo en bytes.
	 * @param ppInputLayout                      Puntero donde se almacenar� la referencia al InputLayout creado.
	 * @return                                   Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
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
	 * @param pShaderBytecode C�digo binario del shader.
	 * @param BytecodeLength  Tama�o del c�digo en bytes.
	 * @param pClassLinkage   Puntero opcional para el enlace de clases del shader.
	 * @param ppPixelShader   Puntero donde se almacenar� la referencia al PixelShader creado.
	 * @return                Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
	 */
	HRESULT
	CreatePixelShader(const void* pShaderBytecode,
										unsigned int BytecodeLength,
										ID3D11ClassLinkage* pClassLinkage,
										ID3D11PixelShader** ppPixelShader);

	/*
	 * @brief Crea un buffer en la GPU para almacenar datos como v�rtices, �ndices o constantes.
	 *
	 * @param pDesc       Descripci�n del buffer.
	 * @param pInitialData Datos iniciales que se asignar�n al buffer.
	 * @param ppBuffer    Puntero donde se almacenar� la referencia al buffer creado.
	 * @return            Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
	 */
	HRESULT
	CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
							 const D3D11_SUBRESOURCE_DATA* pInitialData,
							 ID3D11Buffer** ppBuffer);

	/*
	 * @brief Crea un SamplerState para definir c�mo se aplicar�n las texturas en la GPU.
	 *
	 * @param pSamplerDesc   Descripci�n del SamplerState.
	 * @param ppSamplerState Puntero donde se almacenar� la referencia al SamplerState creado.
	 * @return               Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
	 */
	HRESULT 
	CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
									   ID3D11SamplerState** ppSamplerState);
public:
	/*
	 * @brief Puntero a ID3D11Device.
	 *
	 * Encargado de la creaci�n de todos los recursos en DirectX 11.
	 */
	ID3D11Device* m_device = nullptr;
};