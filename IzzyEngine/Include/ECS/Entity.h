#pragma once
#include "Prerequisites.h"
#include "Component.h"

class
  Window;

/**
 * @class Entity
 * @brief Clase base para todas las entidades en el motor.
 *
 * La clase Entity representa un objeto en el juego que puede poseer múltiples componentes,
 * permitiendo así comportamientos y características específicas mediante un sistema de entidad-componente.
 */
class
  Entity {
public:

  /**
  * @brief Destructor virtual de la clase Entity.
  *
  * Permite la destrucción correcta de las entidades derivadas.
  */
  virtual
    ~Entity() = default;

  /**
   * @brief Método virtual puro para actualizar la entidad.
   *
   * Este método es sobrescrito por clases derivadas para implementar la lógica de actualización
   * específica de la entidad.
   *
   * @param deltaTime Tiempo transcurrido desde el último cuadro, usado para cálculos dependientes del tiempo.
   */
  virtual
    void
    update(float deltaTime) = 0;

  /**
   * @brief Método virtual puro para renderizar la entidad.
   *
   * Este método es sobrescrito por clases derivadas para implementar la lógica de renderizado específica de la entidad.
   *
   * @param window Referencia a la ventana en la que se renderizará la entidad.
   */
  virtual
    void
    render(Window& window) = 0;

  /*
   * @brief Añade un componente a la entidad.
   *
   * El componente debe ser derivado de la clase Component.
   *
   * @tparam T Tipo del componente a añadir.
   * @param component Puntero compartido al componente a añadir.
  */

  template <typename T>
  void
    addComponent(EngineUtilities::TSharedPointer<T> component) {
    static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
    components.push_back(component.template dynamic_pointer_cast<Component>());
  }
  /*
   * @brief Obtiene un componente de la entidad.
   *
   * Busca un componente del tipo especificado que esté asociado a la entidad.
   *
   * @tparam T Tipo del componente a buscar.
   * @return EngineUtilities::TSharedPointer<T> Puntero compartido al componente si existe,
   * o un puntero compartido vacío si no se encuentra.
  */

  template<typename T>
  EngineUtilities::TSharedPointer<T>
    getComponent() {
    for (auto& component : components) {
      EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
      if (specificComponent) {
        return specificComponent;
      }
    }
    return EngineUtilities::TSharedPointer<T>();
  }
protected:

  bool
    isActive;
  int
    id;
  std::vector<EngineUtilities::TSharedPointer<Component>> components;
};