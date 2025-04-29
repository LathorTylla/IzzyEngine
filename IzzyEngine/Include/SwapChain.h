#pragma once
#include "Prerequisites.h"

/*
 * @brief Forward Declarations.
 *
 * Declaraci�n anticipada de clases para optimizar compilaci�n y evitar dependencias circulares.
 */
class Device;          /* Encargado de la creaci�n y gesti�n de recursos gr�ficos. */
class DeviceContext;   /* Encargado de asignar y ejecutar los recursos gr�ficos. */
class Window;          /* Representa la ventana de la aplicaci�n. */
class Texture;         /* Representa una textura utilizada en el proceso de renderizado. */

/*
 * @brief SwapChain.
 *
 * Clase encargada de gestionar el intercambio de buffers en la ventana de la aplicaci�n.
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
   * @param device         Dispositivo encargado de la creaci�n de recursos gr�ficos.
   * @param deviceContext  Contexto del dispositivo que maneja los comandos de renderizado.
   * @param backBuffer     Textura donde se almacenar� la imagen renderizada.
   * @param window         Ventana de la aplicaci�n.
   * @return               Devuelve un HRESULT indicando el �xito o fallo de la inicializaci�n.
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
   * Se utiliza para gestionar el intercambio de buffers en la ventana de la aplicaci�n.
   */
	IDXGISwapChain* m_swapchain = nullptr;
  /*
   * @brief Tipo de controlador utilizado por DirectX.
   *
   * Define el modo en que la aplicaci�n interact�a con la GPU.
   */
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
private:

  /*
   * @brief Nivel de caracter�sticas de DirectX utilizadas en el renderizado.
   *
   * Determina la compatibilidad del hardware con DirectX 11.
   */
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

  /*
   * @brief Cantidad de muestras utilizadas en la renderizaci�n.
   */
	unsigned int m_sampleCount;
  /*
   * @brief Niveles de calidad soportados en la t�cnica de muestreo.
   */
	unsigned int m_qualityLevels;

  /*
   * @brief Puntero a IDXGIDevice.
   *
   * Interfaz de DirectX Graphics Infrastructure (DXGI) para la gesti�n de dispositivos gr�ficos.
   */
	IDXGIDevice* m_dxgiDevice = nullptr;

  /*
   * @brief Puntero a IDXGIAdapter.
   *
   * Interfaz utilizada para acceder al adaptador gr�fico en el sistema.
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