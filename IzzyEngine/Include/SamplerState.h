#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

class
SamplerState {
public:
  SamplerState() = default;
  ~SamplerState() = default;

  HRESULT
  init(Device& device);

  void
  update();

  void
  render(DeviceContext& deviceContext,
         unsigned int StartSlot,
         unsigned int NumSamplers);

  void
  destroy();

public:
  ID3D11SamplerState* m_sampler = nullptr;
};