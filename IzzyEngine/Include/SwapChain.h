#pragma once
#include "Prerequisites.h"

/*
 * @brief Forward Declarations.
 *
 * Declaración anticipada de clases para optimizar compilación y evitar dependencias circulares.
 */
class Device;          /* Encargado de la creación y gestión de recursos gráficos. */
class DeviceContext;   /* Encargado de asignar y ejecutar los recursos gráficos. */
class Window;          /* Representa la ventana de la aplicación. */
class Texture;         /* Representa una textura utilizada en el proceso de renderizado. */

/*
 * @brief SwapChain.
 *
 * Clase encargada de gestionar el intercambio de buffers en la ventana de la aplicación.
 * Permite presentar los resultados renderizados en pantalla.
 */
class 
SwapChain{
public:
	SwapChain() = default;
	~SwapChain() = default;

  /*
   * @brief Inicializa el SwapChain.
   *
   * @param device         Dispositivo encargado de la creación de recursos gráficos.
   * @param deviceContext  Contexto del dispositivo que maneja los comandos de renderizado.
   * @param backBuffer     Textura donde se almacenará la imagen renderizada.
   * @param window         Ventana de la aplicación.
   * @return               Devuelve un HRESULT indicando el éxito o fallo de la inicialización.
   */
	HRESULT
	init(Device& device,
			 DeviceContext& deviceContext,
			 Texture& backBuffer,
			 Window window);

  /*
   * @brief Actualiza el SwapChain.
	 */
	void 
	update();

  /*
   * @brief Renderiza el SwapChain.
   */
	void 
	render();

  /*
   * @brief Libera los recursos utilizados por el SwapChain.
   */	
	void 
	destroy();

  /*
   * @brief Presenta el contenido renderizado en pantalla.
   */	
	void 
	present();

public:
  /*
   * @brief Puntero a IDXGISwapChain.
   *
   * Se utiliza para gestionar el intercambio de buffers en la ventana de la aplicación.
   */
	IDXGISwapChain* m_swapchain = nullptr;
  /*
   * @brief Tipo de controlador utilizado por DirectX.
   *
   * Define el modo en que la aplicación interactúa con la GPU.
   */
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
private:

  /*
   * @brief Nivel de características de DirectX utilizadas en el renderizado.
   *
   * Determina la compatibilidad del hardware con DirectX 11.
   */
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

  /*
   * @brief Cantidad de muestras utilizadas en la renderización.
   */
	unsigned int m_sampleCount;
  /*
   * @brief Niveles de calidad soportados en la técnica de muestreo.
   */
	unsigned int m_qualityLevels;

  /*
   * @brief Puntero a IDXGIDevice.
   *
   * Interfaz de DirectX Graphics Infrastructure (DXGI) para la gestión de dispositivos gráficos.
   */
	IDXGIDevice* m_dxgiDevice = nullptr;

  /*
   * @brief Puntero a IDXGIAdapter.
   *
   * Interfaz utilizada para acceder al adaptador gráfico en el sistema.
   */
  IDXGIAdapter* m_dxgiAdapter = nullptr;

  /*
   * @brief Puntero a IDXGIFactory.
   *
   * Interfaz utilizada para crear instancias de objetos DXGI.
   */
	IDXGIFactory* m_dxgiFactory = nullptr;

private:

};