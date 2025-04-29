#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;
/*
 * @brief SamplerState.
 *
 * Clase encargada de gestionar el estado del sampler en DirectX 11.
 * Define cómo se muestrean las texturas en la GPU.
 */
class
SamplerState {
public:
  SamplerState() = default; // Constructor por defecto
  ~SamplerState() = default; // Destructor por defecto

  /*
   * @brief Inicializa el SamplerState.
   * @param device Dispositivo de Direct3D 11
   * @return HRESULT Resultado de la operación
   */
  HRESULT
  init(Device& device);

  /*
  * @brief Actualiza el SamplerState.
  */
  void
  update();

  /*
  * @brief Renderiza el SamplerState.
  * @param deviceContext Contexto de Direct3D 11
  * @param StartSlot Slot de inicio
  * @param NumSamplers Número de samplers
  */
  void
  render(DeviceContext& deviceContext,
         unsigned int StartSlot,
         unsigned int NumSamplers);

  /*
  * @brief Libera los recursos utilizados por el SamplerState.
  */
  void
  destroy();

public:
  ID3D11SamplerState* m_sampler = nullptr; // Puntero a ID3D11SamplerState
};