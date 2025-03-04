#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;
class MeshComponent;

class
Buffer {
public:
  Buffer() = default;
  ~Buffer() = default;

  // Inicializa Vertex e Index Buffers 
  HRESULT
  init(Device& device, 
       const MeshComponent& mesh, 
       unsigned int bindFlag);

  // Inicializa Constant Buffers
  HRESULT
  init(Device& device, 
       unsigned int ByteWidth);

  // Actualizamos la logica del Constant Buffer
  void
  update(DeviceContext& deviceContext,
         unsigned int DstSubresource,
         const D3D11_BOX* pDstBox,
         const void* pSrcData,
         unsigned int SrcRowPitch,
         unsigned int SrcDepthPitch);

  // Actualiza en render el Vertex, Index y Constant Buffer
  void
  render(DeviceContext& deviceContext,
         unsigned int StartSlot,
         unsigned int NumBuffers,
         bool setPixelShader = false,
         DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN);

  void
  destroy();

private:
  HRESULT
  createBuffer(Device& device,
               D3D11_BUFFER_DESC& desc,
               D3D11_SUBRESOURCE_DATA* initData);

private:
  ID3D11Buffer* m_buffer = nullptr;
  unsigned int m_stride = 0;
  unsigned int m_offset = 0;
  unsigned int m_bindFlag = 0;
};