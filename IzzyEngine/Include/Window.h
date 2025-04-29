#pragma once
#include "Prerequisites.h"

/*
 * @brief Window.
 *
 * Clase encargada de gestionar la ventana de la aplicaci�n.
 * Permite la creaci�n, actualizaci�n, renderizado y destrucci�n de la ventana.
 */
class 
Window{
public:
  Window() = default;  // constructor por defecto
  ~Window() = default; // destructor por defecto

	/*
   * @brief Inicializa la ventana con los par�metros proporcionados.
	 *
	 * @param hInstance  Instancia de la aplicaci�n en ejecuci�n.
	 * @param cCmdShow   Par�metro que define c�mo debe mostrarse la ventana.
	 * @param wndproc    Puntero a la funci�n de procesamiento de eventos de la ventana.
	 * @return          Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
	 */
	HRESULT
	init(HINSTANCE hInstance, 
			 int cCmdShow, 
		   WNDPROC wndproc);

	/*
	 * @brief Actualiza la l�gica de la ventana si es necesario.
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
   * @brief Puntero a la ventana de la aplicaci�n.
   *
   * Se utiliza para gestionar la ventana de la aplicaci�n.
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
   * @brief Instancia de la aplicaci�n.
   */
	HINSTANCE m_hInst = nullptr;
  /*
   * @brief Rect�ngulo que define el tama�o de la ventana.
   */
	RECT m_rect;
  /*
   * @brief Nombre de la ventana.
   */
	std::string m_windowName = "IzzyEngine";

};