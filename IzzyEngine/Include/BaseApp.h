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
 * Clase base para la aplicaci�n. Gestiona la inicializaci�n,
 * actualizaci�n, renderizado y destrucci�n.
 */
class
BaseApp {
public:
  BaseApp() = default;	// constructor por defecto
  ~BaseApp() = default; // destructor por defecto

 /*
	* @brief Inicializa la aplicaci�n y sus componentes esenciales.
	*
	* @return Devuelve un HRESULT que indica si la inicializaci�n fue exitosa o si hubo un error.
	*/
	HRESULT
	init();

 /*
  * @brief M�todo encargado de actualizar la l�gica de la aplicaci�n en cada ciclo de ejecuci�n.
  */
	void
	update();

 /*
  * @brief Ejecuta el proceso de renderizado en cada ciclo de la aplicaci�n.
  */
	void
	render();

 /*
  * @brief Libera los recursos y cierra la aplicaci�n correctamente.
  */
	void
	destroy();

 /*
  * @brief M�todo principal de ejecuci�n de la aplicaci�n.
  *
  * Gestiona el ciclo de vida de la aplicaci�n, manejando la creaci�n de la ventana
  * y el procesamiento de eventos.
  *
  * @param hInstance      Identificador de la instancia de la aplicaci�n.
  * @param hPrevInstance  Identificador de la instancia previa (sin uso en Windows moderno).
  * @param lpCmdLine      L�nea de comandos con par�metros opcionales.
  * @param nCmdShow       Especifica c�mo se debe mostrar la ventana.
  * @param wndproc        Funci�n de procesamiento de eventos de la ventana.
  * @return              Devuelve un entero que indica el estado de finalizaci�n de la aplicaci�n.
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