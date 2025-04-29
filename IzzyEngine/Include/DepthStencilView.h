#pragma once
#include "Prerequisites.h"

/*
 * @brief Forward Declarations.
 *
 * Se utilizan para declarar clases sin necesidad de incluir sus archivos de encabezado completos.
 * Esto optimiza el tiempo de compilaci�n.
 */
class Device;					/* Representa el encargado de la gesti�n de recursos gr�ficos. */
class DeviceContext;  /* Encargado de asignar y ejecutar los recursos gr�ficos. */
class Texture;		    /* Clase que representa una textura utilizada en la renderizaci�n. */

/*
 * @brief DepthStencilView.
 *
 * Clase que representa Depth Stencil View en DirectX 11.
 * Su prop�sito es gestionar Depth Stencil View, permitiendo determinar
 * qu� objetos est�n m�s cerca y cu�les deben ocultarse detr�s de otros.
 */
class
DepthStencilView {
public:
	DepthStencilView() = default;
	~DepthStencilView() = default;

 /*
  * @brief Inicializa DepthStencilView a partir de una textura existente.
  *
  * @param device        Dispositivo encargado de la creaci�n de recursos gr�ficos.
  * @param depthStencil  Textura utilizada para almacenar la informaci�n de profundidad.
  * @param format        Formato de la textura que se utilizar� como depth stencil.
  * @return             Devuelve un HRESULT indicando el �xito o fallo de la inicializaci�n.
  */
	HRESULT
	init(Device& device, 
       Texture& depthStencil, 
       DXGI_FORMAT format);

 /*
  * @brief M�todo encargado de actualizar la l�gica.
  */
	void
	update();

 /*
  * @brief Renderiza DepthStencilView y la limpia antes de cada frame.
  *
  * @param deviceContext Contexto del dispositivo encargado de administrar los recursos gr�ficos.
  */
	void
	render(DeviceContext& deviceContext);

 /*
  * @brief Libera los recursos utilizados por DepthStencilView.
  */
	void
	destroy();

public:
 /*
  * @brief Puntero a ID3D11DepthStencilView.
  *
  * Se usa para gestionar DepthStencilView.
  */
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
};