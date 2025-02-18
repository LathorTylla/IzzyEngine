#pragma once
#include "Prerequisites.h"

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

private:
};