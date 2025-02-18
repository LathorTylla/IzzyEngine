#pragma once
#include "Prerequisites.h"

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

private:
};