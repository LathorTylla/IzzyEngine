#pragma once
#include "Prerequisites.h"

//Forward declaration
class Window;
class DeviceContext;

/*
 * @brief Viewport.
 *
 * Clase encargada de gestionar el viewport de la aplicación.
 * Permite definir la región de la ventana donde se renderizará la escena.
 */
class 
Viewport {
public:
  Viewport() = default; // constructor por defecto
  ~Viewport() = default;// destructor por defecto

  /*
   * @brief Inicializa el viewport.
   *
   * @param window: Referencia a la ventana de la aplicación.
   * @return Devuelve un HRESULT que indica si la inicialización fue exitosa o si hubo un error.
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
   * param deviceContext: Contexto del dispositivo encargado de administrar los recursos gráficos.
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


