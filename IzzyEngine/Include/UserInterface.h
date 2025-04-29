#pragma once

#include "Prerequisites.h"
#include "ECS/Actor.h"
#include "ECS/Transform.h"

/* 
 * @brief UserInterface.
 * 
 *  Clase que gestiona la interfaz de usuario de la aplicación.
 *
*/
class 
UserInterface{
public:
  UserInterface();  // constructor por defecto
  ~UserInterface(); // destructor por defecto

  /*
   *@brief Inicializa la interfaz de usuario.
   * param window: Puntero a la ventana de la aplicación.
   * param device: Puntero al dispositivo de DirectX 11.
   * param deviceContext: Puntero al contexto de dispositivo de DirectX 11.
   */
  void 
  init(void* window, 
       ID3D11Device* device, 
       ID3D11DeviceContext* deviceContext);

  /*
   * @brief Actualiza la interfaz de usuario.
   */
  void 
  update();

  /*
   * @brief Renderiza la interfaz de usuario.
   */
  void 
  render();

  /*
   * @brief Destruye la interfaz de usuario.
   */
  void 
  destroy();

  /*
   * @brief Configura el estilo de la interfaz de usuario.
   */
  void 
  setupStyle();

  /*
  * @brief Crea una ventana de actores.
  * param actors: Vector de punteros compartidos a actores.
  * param selectedIndex: Índice del actor seleccionado.
  * 
  * Esta función crea una ventana que muestra una lista de actores y permite seleccionar uno de ellos.
  * La ventana se actualiza automáticamente para reflejar los cambios en la lista de actores.
  */
  void 
  actorsWindow(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors, 
               int& selectedIndex);

  /*
  * @brief Crea una ventana de transformaciones.
  * param actor: Puntero compartido al actor seleccionado.
  */
  void 
  transformWindow(EngineUtilities::TSharedPointer<Actor>& actor);

  /*
  * @brief Crea una ventana de prueba.
  */
  void 
  drawTestDock();


  /*
   * @brief Crea un botón en la interfaz de usuario.
   * param label: Etiqueta del botón.
   * param value: Valor del botón.
   * param resetValue: Valor de reinicio del botón.
   * param columnWidth: Ancho de la columna.
   */
  void 
  vec3Control(std::string label, 
              float* values, 
              float resetValue = 0.0f, 
              float columnWidth = 100.0f);

private:

};
