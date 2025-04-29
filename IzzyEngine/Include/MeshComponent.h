#pragma once
#include "Prerequisites.h"
#include "DeviceContext.h"
#include "ECS/Component.h"

/*
* @brief MeshComponent.
* Clase encargada de gestionar la información de la malla en DirectX 11.
* Contiene los vértices y los índices de la malla, así como su nombre.
*/
class 
MeshComponent : public Component {
public:
  MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}
  virtual
  ~MeshComponent() = default;

  /*
  * @brief Actualiza la lógica de la malla.
  * @param deltaTime Tiempo transcurrido desde la última actualización.
  */
  void
  update(float deltaTime) override {}

  /*
  * @brief Renderiza la malla.
  * @param deviceContext Contexto del dispositivo encargado de administrar los recursos gráficos.
  */
  void 
  render(DeviceContext& deviceContext) override {};

public:
  std::string m_name; // Nombre de la malla
  std::vector<SimpleVertex> m_vertex; // Vector que contiene los vértices de la malla
  std::vector<unsigned int> m_index; // Vector que contiene los índices de la malla
  int m_numVertex; // Número de vértices en la malla
  int m_numIndex; // Número de índices en la malla

};

