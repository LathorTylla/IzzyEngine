#pragma once
#include "Prerequisites.h"
#include "Component.h"
class DeviceContext;

/*
 * @class Entity
 * @brief Clase base para todas las entidades en el sistema ECS.
 *
 * Esta clase define la interfaz básica para las entidades que pueden tener componentes asociados.
 * Las entidades pueden ser actualizadas y renderizadas, y pueden contener múltiples componentes.
 */
class
Entity {
public:
  /**
   * @brief Destructor virtual.
   */
  virtual
  ~Entity() = default;

  /**
   * @brief Método virtual puro para actualizar la entidad.
   * @param deltaTime El tiempo transcurrido desde la última actualización.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  virtual 
  void
  update(float deltaTime, DeviceContext& deviceContext) = 0;

  /**
   * @brief Método virtual puro para renderizar la entidad.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  virtual 
  void
  render(DeviceContext& deviceContext) = 0;

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
    m_components.push_back(component.template dynamic_pointer_cast<Component>());
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
    for (auto& component : m_components) {
      EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
      if (specificComponent) {
        return specificComponent;
      }
    }
    return EngineUtilities::TSharedPointer<T>();
  }
protected:

  bool isActive;
  int id;
  std::vector<EngineUtilities::TSharedPointer<Component>> m_components;
};