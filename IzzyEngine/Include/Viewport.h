#pragma once
#include "Prerequisites.h"

//Forward declaration
class Window;
class DeviceContext;

/*
 * @brief Viewport.
 *
 * Clase encargada de gestionar el viewport de la aplicaci�n.
 * Permite definir la regi�n de la ventana donde se renderizar� la escena.
 */
class 
Viewport {
public:
  Viewport() = default; // constructor por defecto
  ~Viewport() = default;// destructor por defecto

  /*
   * @brief Inicializa el viewport.
   *
   * @param window: Referencia a la ventana de la aplicaci�n.
   * @return Devuelve un HRESULT que indica si la inicializaci�n fue exitosa o si hubo un error.
   */
	
	HRESULT
    init(const Window& window);

  /*
   * @brief inicializa el viewport.
   * param width: Ancho del viewport.
   * param height: Alto del viewport.
   */
	HRESULT
  init(unsigned int width, 
			 unsigned int height);

  /*
   * @brief Actualiza el viewport.
   */
	void 
	update();

  /*
   * @brief Renderiza el viewport.
   * param deviceContext: Contexto del dispositivo encargado de administrar los recursos gr�ficos.
   */
	void 
	render(DeviceContext& deviceContext);

  /*
   * @brief Libera los recursos utilizados por el viewport.
   */
	void 
	destroy();
public:
  D3D11_VIEWPORT m_viewport; // Viewport de DirectX 11

};


