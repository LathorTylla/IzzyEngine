#pragma once
#include "Prerequisites.h"
#include "Utilities\Vectors\Vector3.h"
#include "Component.h"

class
  Transform : public Component {
public:
  // Constructor que inicializa posición, rotación y escala por defecto
  Transform() : position(),
    rotation(),
    scale(),
    matrix(),
    Component(ComponentType::TRANSFORM) {}

  // Métodos para inicialización, actualización, renderizado y destrucción
  // Inicializa el objeto Transform
  void
    init();

  // Actualiza el estado del objeto Transform basado en el tiempo transcurrido
  // @param deltaTime: Tiempo transcurrido desde la última actualización
  void
    update(float deltaTime) override;

  // Renderiza el objeto Transform
  // @param deviceContext: Contexto del dispositivo de renderizado
  void
    render(DeviceContext& deviceContext) override {}

  // Destruye el objeto Transform y libera recursos
  void
    destroy() {}

  // Métodos de acceso a los datos de posición
  // Retorna la posición actual
  const EngineUtilities::Vector3&
    getPosition() const { return position; }

  // Establece una nueva posición
  void
    setPosition(const EngineUtilities::Vector3& newPos) { position = newPos; }

  // Métodos de acceso a los datos de rotación
  // Retorna la rotación actual
  const EngineUtilities::Vector3&
    getRotation() const { return rotation; }

  // Establece una nueva rotación
  void
    setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

  // Métodos de acceso a los datos de escala
  // Retorna la escala actual
  const EngineUtilities::Vector3&
    getScale() const { return scale; }

  // Establece una nueva escala
  void
    setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

  void
    setTransform(const EngineUtilities::Vector3& newPos,
      const EngineUtilities::Vector3& newRot,
      const EngineUtilities::Vector3& newSca);

  // Método para trasladar la posición del objeto
  // @param translation: Vector que representa la cantidad de traslado en cada eje
  void
    translate(const EngineUtilities::Vector3& translation);

private:
  EngineUtilities::Vector3 position;  // Posición del objeto
  EngineUtilities::Vector3 rotation;  // Rotación del objeto
  EngineUtilities::Vector3 scale;     // Escala del objeto

public:
  XMMATRIX matrix;    // Matriz de transformación
};