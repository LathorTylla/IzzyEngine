#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Swapchain.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "MeshComponent.h"
#include "SamplerState.h"

/*
 * @brief BaseApp.
 *
 * Clase base para la aplicación. Gestiona la inicialización,
 * actualización, renderizado y destrucción.
 */
class
BaseApp {
public:
  BaseApp() = default;	// constructor por defecto
  ~BaseApp() = default; // destructor por defecto

 /*
	* @brief Inicializa la aplicación y sus componentes esenciales.
	*
	* @return Devuelve un HRESULT que indica si la inicialización fue exitosa o si hubo un error.
	*/
	HRESULT
	init();

 /*
  * @brief Método encargado de actualizar la lógica de la aplicación en cada ciclo de ejecución.
  */
	void
	update();

 /*
  * @brief Ejecuta el proceso de renderizado en cada ciclo de la aplicación.
  */
	void
	render();

 /*
  * @brief Libera los recursos y cierra la aplicación correctamente.
  */
	void
	destroy();

 /*
  * @brief Método principal de ejecución de la aplicación.
  *
  * Gestiona el ciclo de vida de la aplicación, manejando la creación de la ventana
  * y el procesamiento de eventos.
  *
  * @param hInstance      Identificador de la instancia de la aplicación.
  * @param hPrevInstance  Identificador de la instancia previa (sin uso en Windows moderno).
  * @param lpCmdLine      Línea de comandos con parámetros opcionales.
  * @param nCmdShow       Especifica cómo se debe mostrar la ventana.
  * @param wndproc        Función de procesamiento de eventos de la ventana.
  * @return              Devuelve un entero que indica el estado de finalización de la aplicación.
  */
	int
	run(HINSTANCE hInstance,
			HINSTANCE hPrevInstance,
			LPWSTR lpCmdLine,
			int nCmdShow,
			WNDPROC wndproc);

public:
  // Global Variables
  Window															g_window;
  Device															g_device;
  DeviceContext												g_deviceContext;
  SwapChain														g_swapchain;
  Texture															g_backBuffer;
  Texture															g_depthStencil;
  RenderTargetView										g_renderTargetView;
  DepthStencilView										g_depthStencilView;
  Viewport														g_viewport;
  ShaderProgram												g_shaderProgram;

  Buffer															g_vertexBuffer;
  Buffer															g_indexBuffer;
  Buffer 															g_neverChanges;
  Buffer 															g_changeOnResize;
  Buffer 															g_changeEveryFrame;
  Texture 														g_textureCubeImg;
  SamplerState 												g_samplerState;
  //ID3D11ShaderResourceView*           g_pTextureRV = nullptr;
  //ID3D11SamplerState*                 g_pSamplerLinear = nullptr;
  XMMATRIX                            g_World;
  XMMATRIX                            g_View;
  XMMATRIX                            g_Projection;
  XMFLOAT4                            g_vMeshColor;

  CBChangesEveryFrame cb;
  CBNeverChanges cbNeverChanges;
  CBChangeOnResize cbChangesOnResize;

  MeshComponent m_meshComponent;
};