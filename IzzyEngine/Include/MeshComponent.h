#pragma once
#include "Prerequisites.h"
#include "DeviceContext.h"
#include "ECS/Component.h"

/*
* @brief MeshComponent.
* Clase encargada de gestionar la informaci�n de la malla en DirectX 11.
* Contiene los v�rtices y los �ndices de la malla, as� como su nombre.
*/
class 
MeshComponent : public Component {
public:
  MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}
  virtual
  ~MeshComponent() = default;

  /*
  * @brief Actualiza la l�gica de la malla.
  * @param deltaTime Tiempo transcurrido desde la �ltima actualizaci�n.
  */
  void
  update(float deltaTime) override {}

  /*
  * @brief Renderiza la malla.
  * @param deviceContext Contexto del dispositivo encargado de administrar los recursos gr�ficos.
  */
  void 
  render(DeviceContext& deviceContext) override {};

public:
  std::string m_name; // Nombre de la malla
  std::vector<SimpleVertex> m_vertex; // Vector que contiene los v�rtices de la malla
  std::vector<unsigned int> m_index; // Vector que contiene los �ndices de la malla
  int m_numVertex; // N�mero de v�rtices en la malla
  int m_numIndex; // N�mero de �ndices en la malla

};

