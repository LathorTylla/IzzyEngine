#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;
class MeshComponent;

/*
  Buffer class
  Esta clase es responsable de la creación y gestión de buffers en Direct3D 11.
  Soporta Vertex Buffers, Index Buffers y Constant Buffers.
*/
class
Buffer {
public:
  Buffer() = default;  // Constructor por defecto
  ~Buffer() = default; // Destructor por defecto

  // Inicializa Vertex e Index Buffers 
  HRESULT
  init(Device& device, 
       const MeshComponent& mesh, 
       unsigned int bindFlag);

  /*
  * Inicializa el Constant Buffer
  * @param device: Dispositivo de Direct3D 11
  * @param ByteWidth: Tamaño del buffer
  * @return HRESULT: Resultado de la operación
  */
  HRESULT
  init(Device& device, 
       unsigned int ByteWidth);

  /*
  * Actualiza el buffer en el GPU
  * @param deviceContext: Contexto de Direct3D 11
  * @param DstSubresource: Subrecurso de destino
  * @param pDstBox: Caja de destino
  * @param pSrcData: Datos de origen
  * @param SrcRowPitch: Ancho de fila de origen
  * @param SrcDepthPitch: Profundidad de origen
  */
  void
  update(DeviceContext& deviceContext,
         unsigned int DstSubresource,
         const D3D11_BOX* pDstBox,
         const void* pSrcData,
         unsigned int SrcRowPitch,
         unsigned int SrcDepthPitch);

  /*
  * Renderiza el buffer
  * @param deviceContext: Contexto de Direct3D 11
  * @param StartSlot: Slot de inicio
  * @param NumBuffers: Número de buffers
  * @param setPixelShader: Bandera para establecer el pixel shader
  * @param format: Formato del buffer
  */
  void
  render(DeviceContext& deviceContext,
         unsigned int StartSlot,
         unsigned int NumBuffers,
         bool setPixelShader = false,
         DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN);

  //Destroy el buffer
  void
  destroy();

private:
  HRESULT
  createBuffer(Device& device,
               D3D11_BUFFER_DESC& desc,
               D3D11_SUBRESOURCE_DATA* initData);

private:
  ID3D11Buffer* m_buffer = nullptr; // Buffer de Direct3D 11
  unsigned int m_stride = 0;        // Tamaño del buffer
  unsigned int m_offset = 0;        // Offset del buffer
  unsigned int m_bindFlag = 0;      // Bandera de binding 
};