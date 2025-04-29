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
#include "userInterface.h"
#include "ModelLoader.h"
#include "ECS/Actor.h"

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

  void
  InputActionMap(float deltaTime);

  HRESULT 
  resizeWindow(HWND hWnd, LPARAM lParam);

  void
  updateCamera();

  void
  rotateCamera(int mouseX, int mouseY);
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
  // Variables miembro de la clase BaseApp
  Window															m_window;
  Device															m_device;
  DeviceContext												m_deviceContext;
  SwapChain														m_swapchain;
  Texture															m_backBuffer;
  Texture															m_depthStencil;
  RenderTargetView										m_renderTargetView;
  DepthStencilView										m_depthStencilView;
  Viewport														m_viewport;
  ShaderProgram												m_shaderProgram;
  Buffer 															m_neverChanges;
  Buffer 															m_changeOnResize;
  Buffer 															m_changeEveryFrame;
  XMMATRIX                            m_View;
  XMMATRIX                            m_Projection;
  XMFLOAT4                            m_vMeshColor;

  CBNeverChanges                      cbNeverChanges;
  CBChangeOnResize                    cbChangesOnResize;

  Camera                              m_camera;

  UserInterface                       m_userInterface;

  //Modelos FBX
  ModelLoader                         m_psyduck;
  EngineUtilities::TSharedPointer<Actor> APsyduck;
 	std::vector<Texture>								m_psyduckTextures;
 	Texture                             m_default;

  //Modelos OBJ
  ModelLoader                         m_objModel;
  EngineUtilities::TSharedPointer<Actor> AObjModel;
  std::vector<Texture>								m_objTextures;

  //Actores
  std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors;  // contenedor de todos los actores
  int selectedActorIndex = 0; // �ndice del actor seleccionado


  bool keys[256] = { false }; // Arreglo de teclas para manejar los inputs de teclado
  bool mouseLeftDown = false; // Variable para manejar el clic izquierdo del mouse
  int lastX;                  // Variable para almacenar la �ltima posici�n en X del mouse
  int lastY;                  // Variable para almacenar la �ltima posici�n en Y del mouse
  float sensitivity = 0.002f; // Sensibilidad del movimiento del mouse

};