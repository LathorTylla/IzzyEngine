#pragma once

#include "Prerequisites.h"

class 
UserInterface{
public:
	UserInterface();
	~UserInterface();

  void 
  init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);

  void 
  update();

  void 
  render();

  void 
  destroy();

  void 
  setupStyle();

  void 
  vec3Control(std::string label, 
              float* values, 
              float resetValue = 0.0f, 
              float columnWidth = 100.0f);

private:

};
