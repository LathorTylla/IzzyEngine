#include "Buffer.h"
#include "Device.h"
#include "DeviceContext.h"
#include "MeshComponent.h"

HRESULT
Buffer::createBuffer(Device& device,
                     D3D11_BUFFER_DESC& desc,
                     D3D11_SUBRESOURCE_DATA* initData) {
  // Check if the device is valid
  if (!device.m_device) {
    ERROR("Buffer", "createBuffer", "Device is nullptr");
    return E_POINTER;
  }
  // Check if the buffer description is valid
  HRESULT 
  hr = device.CreateBuffer(&desc, initData, &m_buffer);
  if (FAILED(hr)) {
    ERROR("Buffer", "createBuffer", "Failed to create buffer");
    return hr;
  }
  return S_OK;
}

HRESULT
Buffer::init(Device& device, 
             const MeshComponent& mesh, 
             unsigned int bindFlag) {
  if (!device.m_device) {
    // Check if the device is valid
    ERROR("Buffer", "init", "Device is nullptr");
    return E_POINTER;
  }

  if ((bindFlag & D3D11_BIND_VERTEX_BUFFER) && mesh.m_vertex.empty()) {
    // Check if the vertex buffer is empty
    ERROR("Buffer", "init", "Vertex Buffer is empty");
    return E_INVALIDARG;
  }

  if ((bindFlag & D3D11_BIND_INDEX_BUFFER) && mesh.m_index.empty()) {
    // Check if the index buffer is empty
    ERROR("Buffer", "init", "Index buffer is empty");
    return E_INVALIDARG;
  }

  D3D11_BUFFER_DESC desc = {};  // Initialize the buffer description
  D3D11_SUBRESOURCE_DATA InitData = {}; // Initialize the subresource data

  desc.Usage = D3D11_USAGE_DEFAULT; // Set the usage to default
  desc.CPUAccessFlags = 0;  // No CPU access
  m_bindFlag = bindFlag;  // Set the bind flag

  // Set the buffer description based on the bind flag
  if (bindFlag & D3D11_BIND_VERTEX_BUFFER) {
    m_stride = sizeof(SimpleVertex);  // Set the stride to the size of SimpleVertex
    desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_vertex.size());// Set the byte width
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;  // Set the bind flag to vertex buffer
    InitData.pSysMem = mesh.m_vertex.data();  // Set the system memory to the vertex data
  }
  else if (bindFlag & D3D11_BIND_INDEX_BUFFER) {
    m_stride = sizeof(unsigned int);  // Set the stride to the size of unsigned int
    desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_index.size()); // Set the byte width 
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;  // Set the bind flag to index buffer
    InitData.pSysMem = mesh.m_index.data();  // Set the system memory to the index data
  }

  return createBuffer(device, desc, &InitData);
}


HRESULT
Buffer::init(Device& device, 
             unsigned int ByteWidth) {
  if (!device.m_device || ByteWidth == 0) {
    // Check if the device is valid
    ERROR("Buffer", "init", "Invalid parameters");
    return E_INVALIDARG;
  }

  m_stride = ByteWidth; // Set the stride to the byte width

  D3D11_BUFFER_DESC desc = {};  // Initialize the buffer description
  desc.Usage = D3D11_USAGE_DEFAULT; // Set the usage to default
  desc.ByteWidth = ByteWidth; // Set the byte width
  desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // Set the bind flag to constant buffer
  m_bindFlag = desc.BindFlags; // Set the bind flag

  return createBuffer(device, desc, nullptr); 
}

void
Buffer::update(DeviceContext& deviceContext,
               unsigned int DstSubresource,
               const D3D11_BOX* pDstBox,
               const void* pSrcData,
               unsigned int SrcRowPitch,
               unsigned int SrcDepthPitch) {
  if (!m_buffer) {
    ERROR("Buffer", "update", "Buffer is nullptr");
    return;
  }

  deviceContext.UpdateSubresource(m_buffer, 
                                  DstSubresource, 
                                  pDstBox, 
                                  pSrcData, 
                                  SrcRowPitch, 
                                  SrcDepthPitch);
}

void 
Buffer::render(DeviceContext& deviceContext,
               unsigned int StartSlot,
               unsigned int NumBuffers,
               bool setPixelShader,
               DXGI_FORMAT format) {
  if (!m_buffer) {
    ERROR("Buffer", "render", "Buffer is nullptr");
    return;
  }

  switch (m_bindFlag) {
  case D3D11_BIND_VERTEX_BUFFER:
    deviceContext.IASetVertexBuffers(StartSlot, NumBuffers, &m_buffer, &m_stride, &m_offset);
    break;

  case D3D11_BIND_CONSTANT_BUFFER:
    deviceContext.VSSetConstantBuffers(StartSlot, NumBuffers, &m_buffer);
    if (setPixelShader) {
      deviceContext.PSSetConstantBuffers(StartSlot, NumBuffers, &m_buffer);
    }
    break;

  case D3D11_BIND_INDEX_BUFFER:
    deviceContext.IASetIndexBuffer(m_buffer, format, m_offset);
    break;

  default:
    ERROR("Buffer", "render", "Unsupported BindFlag");
    break;
  }
}

void Buffer::destroy() {
  SAFE_RELEASE(m_buffer);
}