#pragma once

/*
 * @brief Librerías estándar (STD).
 *
 * Conjunto de librerías utilizadas para la gestión de datos, flujo de entrada/salida
 * y operaciones matemáticas dentro del sistema.
 */
#include <string>     /* Manejo de cadenas de texto. */
#include <sstream>    /* Flujo de datos para conversión de strings. */
#include <vector>     /* Contenedor dinámico de elementos. */
#include <windows.h>  /* Librería base de Windows API. */
#include <xnamath.h>  /* Librería matemática utilizada para cálculos gráficos. */

//<memory>
#include <thread>     /* Librería para manejo de múltiples hilos de ejecución. */

//Librerias DirectX
#include <D3D11.h>        /* Interfaz principal para la gestión de Direct3D 11. */
#include <D3DX11.h>       /* Extensiones de Direct3D 11 (deprecated en versiones recientes). */
#include <d3dcompiler.h>  /* Compilador de shaders para DirectX 11. */
#include "resource.h"     /* Archivo de recursos. */
#include "Resource.h"     /* Archivo de recursos adicional. */

/*
 * @brief Macros utilizadas para depuración y gestión de recursos en DirectX 11.
 */

/*
 * @brief Libera un recurso de DirectX y lo establece en nullptr para evitar accesos inválidos.
 *
 * @param x Puntero al recurso que se desea liberar.
 */
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

/*
 * @brief Muestra un mensaje en la consola de depuración cuando se crea un recurso exitosamente.
 *
 * @param classObj Nombre de la clase donde se genera el mensaje.
 * @param method   Método en el que se genera el mensaje.
 * @param state    Estado o mensaje adicional sobre la creación del recurso.
 */

#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

/*
 * @brief Muestra un mensaje de error en la consola de depuración e interrumpe la ejecución en caso de fallo crítico.
 *
 * @param classObj Nombre de la clase donde ocurre el error.
 * @param method   Método en el que ocurre el error.
 * @param errorMSG Mensaje de error específico.
 */
#define ERROR( classObj, method, errorMSG )  \
{                                            \
   std::wostringstream os_;                  \
   os_ << "ERROR : " << classObj << "::" << method << " : " << "  Error in data from params [" << errorMSG << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
   exit(1);                                  \
}

 /*
  * @brief Estructuras utilizadas para la gestión de datos en Direct3D 11.
  */


/*
 * @brief Estructura para definir un vértice simple con posición y coordenadas de textura.
 */
struct 
SimpleVertex{
  XMFLOAT3 Pos;   /* Coordenadas en el espacio 3D. */
  XMFLOAT2 Tex;   /* Coordenadas de textura. */
};

/*
 * @brief Constante del buffer para la vista de la cámara, que no cambia durante la ejecución.
 */
struct 
CBNeverChanges{
  XMMATRIX mView; /* Matriz de vista utilizada en la renderización. */
};

/*
 * @brief Constante del buffer para manejar cambios en el tamaño de la ventana.
 */
struct 
CBChangeOnResize{
  XMMATRIX mProjection; /* Matriz de proyección ajustada al tamaño de la ventana. */
};


/*
 * @brief Constante del buffer para objetos que cambian en cada fotograma.
 */
struct 
CBChangesEveryFrame{
  XMMATRIX mWorld;      /* Matriz de transformación del objeto en el mundo 3D. */
  XMFLOAT4 vMeshColor;  /* Color del objeto renderizado. */
};

/*
 * @brief Enumeración para definir los diferentes formatos de textura soportados.
 */
enum 
ExtensionType {
  DDS = 0,      /* Formato DDS, optimizado para DirectX. */
  PNG = 1,      /* Formato PNG, comprimido sin pérdida de calidad. */
  JPG = 2       /* Formato JPG, comprimido con pérdida de calidad. */
};

enum 
ShaderType {
  VERTEX_SHADER = 0,
  PIXEL_SHADER = 1
};