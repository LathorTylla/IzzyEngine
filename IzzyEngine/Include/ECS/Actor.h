#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "Buffer.h"
#include "Texture.h"
#include "SamplerState.h"
#include "Transform.h"

class Device;
class MeshComponent;

/**
 * @class Actor
 * @brief Clase que representa un actor en el juego.
 *
 * La clase Actor hereda de Entity y representa un objeto en el juego que puede tener mallas,
 * texturas y varios componentes. Proporciona métodos para actualizar, renderizar y destruir el actor.
 */
class
Actor : public Entity {
public:
  /**
   * @brief Constructor por defecto.
   */
  Actor() = default;

  /**
   * @brief Constructor que inicializa el actor con un dispositivo.
   * @param device El dispositivo con el cual se inicializa el actor.
   */
  Actor(Device& device);

  /**
   * @brief Destructor virtual.
   */
  virtual
  ~Actor() = default;

  /**
   * @brief Actualiza el actor.
   * @param deltaTime El tiempo transcurrido desde la última actualización.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  void
  update(float deltaTime, 
         DeviceContext& deviceContext) override;

  /**
   * @brief Renderiza el actor.
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  void
  render(DeviceContext& deviceContext) override;

  /**
   * @brief Destruye el actor y libera los recursos asociados.
   */
  void
  destroy();

  /**
   * @brief Establece las mallas del actor.
   * @param device El dispositivo con el cual se inicializan las mallas.
   * @param meshes Vector de componentes de malla que se van a establecer.
   */
  void
  setMesh(Device& device, 
          std::vector<MeshComponent> meshes);

  /**
   * @brief Establece las texturas del actor.
   * @param textures Vector de texturas que se van a establecer.
   */
  void
  setTextures(std::vector<Texture> textures) {
    m_textures = textures;
  }

  /**
   * @brief Obtiene el nombre del actor.
   * @return El nombre del actor.
   */
  std::string
  getName() {
    return m_name;
  }

  /*
  * @brief Establece el nombre del actor.
  * @param name El nuevo nombre del actor.
  */
  void 
  setName(std::string name) {
    m_name = name;
  }

  /**
   * @brief Obtiene un componente específico del actor.
   * @tparam T Tipo del componente que se va a obtener.
   * @return Puntero compartido al componente, o nullptr si no se encuentra.
   */
  template <typename T>
  EngineUtilities::TSharedPointer<T>
    getComponent();

private:
  std::vector<MeshComponent> m_meshes;  // Vector de componentes de malla.
  std::vector<Texture> m_textures;      // Vector de texturas.
  std::vector<Buffer> m_vertexBuffers;  // Buffers de vértices.
  std::vector<Buffer> m_indexBuffers;   // Buffers de índices.

  CBChangesEveryFrame m_model;            // Constante del buffer para cambios en cada frame.

  Buffer m_modelBuffer;                 // Buffer del modelo.
  
  SamplerState m_sampler;               // Estado del muestreador.

  std::string m_name = "Actor";         // Nombre del actor.
};

/*
* @brief Obtiene un componente específico del actor.
* @param T Tipo del componente que se va a obtener.
* @return Puntero compartido al componente, o nullptr si no se encuentra.
*
* Este método busca en la lista de componentes del actor y devuelve el primer componente que coincide con el tipo T.
*/
template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
  for (auto& component : m_components) {
    EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
    if (specificComponent) {
      return specificComponent;
    }
  }
  // Devuelve un TSharedPointer vacío si no se encuentra el componente
  return EngineUtilities::TSharedPointer<T>();
}