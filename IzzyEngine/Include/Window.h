#pragma once
#include "Prerequisites.h"

/*
 * @brief Window.
 *
 * Clase encargada de gestionar la ventana de la aplicación.
 * Permite la creación, actualización, renderizado y destrucción de la ventana.
 */
class 
Window{
public:
  Window() = default;  // constructor por defecto
  ~Window() = default; // destructor por defecto

	/*
   * @brief Inicializa la ventana con los parámetros proporcionados.
	 *
	 * @param hInstance  Instancia de la aplicación en ejecución.
	 * @param cCmdShow   Parámetro que define cómo debe mostrarse la ventana.
	 * @param wndproc    Puntero a la función de procesamiento de eventos de la ventana.
	 * @return          Devuelve un HRESULT indicando el éxito o fallo de la operación.
	 */
	HRESULT
	init(HINSTANCE hInstance, 
			 int cCmdShow, 
		   WNDPROC wndproc);

	/*
	 * @brief Actualiza la lógica de la ventana si es necesario.
	 */
	void
	update();

  /*
   * @brief Renderiza la ventana.
   */
	void
	render();

  /*
   * @brief Libera los recursos utilizados por la ventana.
   */
	void
	destroy();

public:
  /*
   * @brief Puntero a la ventana de la aplicación.
   *
   * Se utiliza para gestionar la ventana de la aplicación.
   */
	HWND m_hWnd = nullptr;

  /*
   * @brief Ancho de la ventana.
   */
	unsigned int m_width;

  /*
   * @brief Alto de la ventana.
   */
	unsigned int m_height;

private:

  /*
   * @brief Instancia de la aplicación.
   */
	HINSTANCE m_hInst = nullptr;
  /*
   * @brief Rectángulo que define el tamaño de la ventana.
   */
	RECT m_rect;
  /*
   * @brief Nombre de la ventana.
   */
	std::string m_windowName = "IzzyEngine";

};