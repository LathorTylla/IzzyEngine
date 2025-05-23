#pragma once

/*
 * @brief Librer�as est�ndar (STD).
 *
 * Conjunto de librer�as utilizadas para la gesti�n de datos, flujo de entrada/salida
 * y operaciones matem�ticas dentro del sistema.
 */
#include <string>     /* Manejo de cadenas de texto. */
#include <sstream>    /* Flujo de datos para conversi�n de strings. */
#include <vector>     /* Contenedor din�mico de elementos. */
#include <windows.h>  /* Librer�a base de Windows API. */
#include <xnamath.h>  /* Librer�a matem�tica utilizada para c�lculos gr�ficos. */

//<memory>
#include <thread>     /* Librer�a para manejo de m�ltiples hilos de ejecuci�n. */

// Third Parties
#include "Utilities\Memory\TSharedPointer.h"
#include "Utilities\Memory\TWeakPointer.h"
#include "Utilities\Memory\TStaticPtr.h"
#include "Utilities\Memory\TUniquePtr.h"
//Librerias DirectX
#include <D3D11.h>        /* Interfaz principal para la gesti�n de Direct3D 11. */
#include <D3DX11.h>       /* Extensiones de Direct3D 11 (deprecated en versiones recientes). */
#include <d3dcompiler.h>  /* Compilador de shaders para DirectX 11. */
#include "resource.h"     /* Archivo de recursos. */
#include "Resource.h"     /* Archivo de recursos adicional. */

/*
 * @brief Macros utilizadas para depuraci�n y gesti�n de recursos en DirectX 11.
 */

/*
* @brief Librer�as de ImGui.
*/

#include "imgui.h"            // Librer�a principal de ImGui.
#include "imgui_impl_win32.h" // Implementaci�n de ImGui para Windows.
#include "imgui_impl_dx11.h"  // Implementaci�n de ImGui para DirectX 11.
#include <imgui_internal.h>   // Implementaci�n interna de ImGui.

/*
 * @brief Libera un recurso de DirectX y lo establece en nullptr para evitar accesos inv�lidos.
 *
 * @param x Puntero al recurso que se desea liberar.
 */
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

/*
 * @brief Muestra un mensaje en la consola de depuraci�n cuando se crea un recurso exitosamente.
 *
 * @param classObj Nombre de la clase donde se genera el mensaje.
 * @param method   M�todo en el que se genera el mensaje.
 * @param state    Estado o mensaje adicional sobre la creaci�n del recurso.
 */

#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

/*
 * @brief Muestra un mensaje de error en la consola de depuraci�n e interrumpe la ejecuci�n en caso de fallo cr�tico.
 *
 * @param classObj Nombre de la clase donde ocurre el error.
 * @param method   M�todo en el que ocurre el error.
 * @param errorMSG Mensaje de error espec�fico.
 */
#define ERROR( classObj, method, errorMSG )  \
{                                            \
   std::wostringstream os_;                  \
   os_ << "ERROR : " << classObj << "::" << method << " : " << "  Error in data from params [" << errorMSG << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
   exit(1);                                  \
}

 /*
  * @brief Estructuras utilizadas para la gesti�n de datos en Direct3D 11.
  */


/*
 * @brief Estructura para definir un v�rtice simple con posici�n y coordenadas de textura.
 */
struct 
SimpleVertex{
  XMFLOAT3 Pos;   /* Coordenadas en el espacio 3D. */
  XMFLOAT2 Tex;   /* Coordenadas de textura. */
};

/*
 * @brief Constante del buffer para la vista de la c�mara, que no cambia durante la ejecuci�n.
 */
struct 
CBNeverChanges{
  XMMATRIX mView; /* Matriz de vista utilizada en la renderizaci�n. */
};

/*
 * @brief Constante del buffer para manejar cambios en el tama�o de la ventana.
 */
struct 
CBChangeOnResize{
  XMMATRIX mProjection; /* Matriz de proyecci�n ajustada al tama�o de la ventana. */
};


/*
 * @brief Constante del buffer para objetos que cambian en cada fotograma.
 */
struct 
CBChangesEveryFrame{
  XMMATRIX mWorld;      /* Matriz de transformaci�n del objeto en el mundo 3D. */
  XMFLOAT4 vMeshColor;  /* Color del objeto renderizado. */
};

/*
 * @brief Enumeraci�n para definir los diferentes formatos de textura soportados.
 */
enum 
ExtensionType {
  DDS = 0,      /* Formato DDS, optimizado para DirectX. */
  PNG = 1,      /* Formato PNG, comprimido sin p�rdida de calidad. */
  JPG = 2       /* Formato JPG, comprimido con p�rdida de calidad. */
};
/*
 * @brief Enumeraci�n para definir los diferentes tipos de componentes en el sistema.
 *
 * Esta enumeraci�n se utiliza para identificar el tipo de componente que un objeto puede tener,
 * como TRANSFORM, MESH, MATERIAL, entre otros.
 */
enum
  ComponentType {
  NONE = 0,     ///< Tipo de componente no especificado.
  TRANSFORM = 1,///< Componente de transformaci�n.
  MESH = 2,     ///< Componente de malla.
  MATERIAL = 3  ///< Componente de material.
};

enum 
ShaderType {
  VERTEX_SHADER = 0,
  PIXEL_SHADER = 1
};

/*
 * @brief Estructura para definir la c�mara en el espacio 3D.
 */
struct 
Camera {
  XMFLOAT3 pos;      /* Posici�n de la c�mara en el espacio 3D. */
  XMFLOAT3 target;   /* Punto al que la c�mara apunta. */

  XMFLOAT3 up;       /* Vector de direcci�n hacia arriba. */
  XMFLOAT3 forward;  /* Vector de direcci�n hacia adelante. */
  XMFLOAT3 right;    /* Vector de direcci�n hacia la derecha. */

  float yaw;         /* �ngulo de rotaci�n horizontal. */
  float pitch;       /* �ngulo de rotaci�n vertical. */

  Camera() {
    pos = XMFLOAT3(0.0f, 0.0f, -6.0f);    // Posici�n inicial de la c�mara
    target = XMFLOAT3(0.0f, 2.0f, 0.0f);  // Punto al que la c�mara apunta
    up = XMFLOAT3(0.0f, 1.0f, 0.0f);      // Vector de direcci�n hacia arriba
    forward = XMFLOAT3(0.0f, 0.0f, 1.0f); // Vector de direcci�n hacia adelante
    right = XMFLOAT3(1.0f, 0.0f, 0.0f);   // Vector de direcci�n hacia la derecha
    yaw = 0.0f;                           // �ngulo de rotaci�n horizontal
    pitch = 0.0f;                         // �ngulo de rotaci�n vertical
  }
};