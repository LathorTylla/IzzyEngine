#pragma once
#include "Prerequisites.h"
#include "Component.h"
class DeviceContext;

class
Component {
public:
  /**
   * @brief Constructor por defecto.
   */
  Component() = default;

  /**
   * @brief Constructor con tipo de componente.
   * @param type Tipo del componente.
   */
  Component(const ComponentType type) : m_type(type) {}

  /**
   * @brief Destructor virtual.
   */
  virtual
    ~Component() = default;

  /**
   * @brief Método virtual puro para actualizar el componente.
   * @param deltaTime El tiempo transcurrido desde la última actualización.
   */
  virtual void
    update(float deltaTime) = 0;

  /**
   * @brief Método virtual puro para renderizar el componente.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  virtual void
    render(DeviceContext& deviceContext) = 0;

  /**
   * @brief Obtiene el tipo del componente.
   * @return El tipo del componente.
   */
  ComponentType
    getType() const { return m_type; }

protected:
  ComponentType m_type; ///< Tipo del componente.
};