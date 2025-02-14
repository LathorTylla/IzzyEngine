#pragma once
#include "Prerequisites.h"

/*
 * @brief Forward Declarations.
 *
 * Se utilizan para declarar clases sin necesidad de incluir sus archivos de encabezado completos.
 * Esto optimiza el tiempo de compilación.
 */
class Device;					/* Representa el encargado de la gestión de recursos gráficos. */
class DeviceContext;  /* Encargado de asignar y ejecutar los recursos gráficos. */
class Texture;		    /* Clase que representa una textura utilizada en la renderización. */

/*
 * @brief DepthStencilView.
 *
 * Clase que representa Depth Stencil View en DirectX 11.
 * Su propósito es gestionar Depth Stencil View, permitiendo determinar
 * qué objetos están más cerca y cuáles deben ocultarse detrás de otros.
 */
class
DepthStencilView {
public:
	DepthStencilView() = default;
	~DepthStencilView() = default;

 /*
  * @brief Inicializa DepthStencilView a partir de una textura existente.
  *
  * @param device        Dispositivo encargado de la creación de recursos gráficos.
  * @param depthStencil  Textura utilizada para almacenar la información de profundidad.
  * @param format        Formato de la textura que se utilizará como depth stencil.
  * @return             Devuelve un HRESULT indicando el éxito o fallo de la inicialización.
  */
	HRESULT
	init(Device& device, 
       Texture& depthStencil, 
       DXGI_FORMAT format);

 /*
  * @brief Método encargado de actualizar la lógica.
  */
	void
	update();

 /*
  * @brief Renderiza DepthStencilView y la limpia antes de cada frame.
  *
  * @param deviceContext Contexto del dispositivo encargado de administrar los recursos gráficos.
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