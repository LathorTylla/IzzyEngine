#include "ECS/Actor.h"
#include "MeshComponent.h"
#include "Device.h"


Actor::Actor(Device& device) {
  // Componentes por defecto
  EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
  addComponent(transform);
  EngineUtilities::TSharedPointer<MeshComponent> mesh = EngineUtilities::MakeShared<MeshComponent>();
  addComponent(mesh);

  // Inicializar el actor
  HRESULT hr;
  std::string classNameType = "Actor -> " + m_name;

  // Initialize the model buffer

  hr = m_modelBuffer.init(device, sizeof(CBChangesEveryFrame));
  if (FAILED(hr)) {
    ERROR("Actor", classNameType.c_str(), "Failed to create new CBChangesEveryFrame");
  }
  // Initialize the model buffer with default values
  hr = m_sampler.init(device);
  if (FAILED(hr)) {
    ERROR("Actor", classNameType.c_str(), "Failed to create new SamplerState");
  }

  //hr = m_rasterizer.init(device);
  //if (FAILED(hr)) {
  //	ERROR("Actor", classNameType.c_str(), "Failed to create new Rasterizer");
  //}

  //hr = m_blendState.init(device);
  //if (FAILED(hr)) {
  //	ERROR("Actor", classNameType.c_str(), "Failed to create new BlendState");
  //}
}

void
Actor::update(float deltaTime, DeviceContext& deviceContext) {
  // Update Transform Component
  getComponent<Transform>()->update(deltaTime);

  // Update Mesh Component
  m_model.mWorld = XMMatrixTranspose(getComponent<Transform>()->matrix);
  // Update the model matrix in the constant buffer
  m_model.vMeshColor = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);

  // Update attributes
  m_modelBuffer.update(deviceContext, 0, nullptr, &m_model, 0, 0);

}

void
Actor::render(DeviceContext& deviceContext) {

  m_sampler.render(deviceContext, 0, 1);

  // Update buffers for each individual mesh on the actor
  for (unsigned int i = 0; i < m_meshes.size(); i++) {
    m_vertexBuffers[i].render(deviceContext, 0, 1);
    m_indexBuffers[i].render(deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);

    if (m_textures.size() > 0) {
      if (i < m_textures.size()) {
        //std::string msg = std::to_string(i) + " Mesh asignada con textura.";
        //MESSAGE("Actor", "render", msg.c_str());
        m_textures[i].render(deviceContext, 0, 1);
      }
      else {
        //std::string msg = std::to_string(i) + " NO tiene textura asignada.";
        //MESSAGE("Actor", "render", msg.c_str());
      }
    }

    m_modelBuffer.render(deviceContext, 2, 1, true);

    deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext.DrawIndexed(m_meshes[i].m_numIndex, 0, 0);
  }
}

void
Actor::destroy() {
  // Destroy all buffers and textures
  for (auto& vertexBuffer : m_vertexBuffers) {
    vertexBuffer.destroy();
  }
  // Destroy all index buffers
  for (auto& indexBuffer : m_indexBuffers) {
    indexBuffer.destroy();
  }
  // Destroy all textures
  for (auto& tex : m_textures) {
    tex.destroy();
  }
  m_modelBuffer.destroy();

  m_sampler.destroy();
}

void
Actor::setMesh(Device& device, std::vector<MeshComponent> meshes) {
  m_meshes = meshes;  // Asignar los meshes al actor
  HRESULT hr;         // Inicializar el resultado de HRESULT
  // Limpiar los buffers de vértices e índices
  for (auto& mesh : m_meshes) {
    // Crear vertex buffer
    Buffer vertexBuffer;
    hr = vertexBuffer.init(device, mesh, D3D11_BIND_VERTEX_BUFFER);
    // Comprobar si se ha creado correctamente
    if (FAILED(hr)) {
      ERROR("Actor", "setMesh", "Failed to create new vertexBuffer");
    }
    // Comprobar si el buffer de vértices ya existe
    else {
      m_vertexBuffers.push_back(vertexBuffer);
    }

    // Crear index buffer
    Buffer indexBuffer;
    hr = indexBuffer.init(device, mesh, D3D11_BIND_INDEX_BUFFER);
    if (FAILED(hr)) {
      ERROR("Actor", "setMesh", "Failed to create new indexBuffer");
    }
    // Comprobar si el buffer de índices ya existe
    else {
      m_indexBuffers.push_back(indexBuffer);
    }
  }
}