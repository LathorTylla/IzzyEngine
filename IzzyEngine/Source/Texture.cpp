#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "Texture.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT 
Texture::init(Device device, 
              const std::string& textureName, 
              ExtensionType extensionType) {
  if (!device.m_device) {
    ERROR("Texture", "init", "Device is nullptr in texture loading method");
    return E_POINTER;
  }
  HRESULT hr = S_OK;
  switch (extensionType) {
  case DDS:
    // Cargar textura DDS
    hr = D3DX11CreateShaderResourceViewFromFile(device.m_device,
                                                textureName.c_str(),
                                                nullptr,
                                                nullptr,
                                                &m_textureFromImg,
                                                nullptr);
    if (FAILED(hr)) {
      ERROR("Texture", "init",
        ("Failed to load DDS texture. Verify filepath: " + textureName).c_str());
      return hr;
    }
    break;
  case PNG: {
    int width, height, channels;
    unsigned char* data = stbi_load(textureName.c_str(), 
                                    &width, 
                                    &height, 
                                    &channels, 
                                    4);
    if (!data) {
      ERROR("Texture", "init",
        ("Failed to load PNG texture: " + std::string(stbi_failure_reason())).c_str());
      return E_FAIL;
    }
    D3D11_TEXTURE2D_DESC textureDesc = {};
    textureDesc.Width = width;
    textureDesc.Height = height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;
    initData.SysMemPitch = width * 4;
    hr = device.CreateTexture2D(&textureDesc, 
                                &initData, 
                                &m_texture);
    stbi_image_free(data); 
    if (FAILED(hr)) {
      ERROR("Texture", "init", "Failed to create texture from PNG data");
      return hr;
    }
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    hr = device.m_device->CreateShaderResourceView(m_texture, 
                                                   &srvDesc, 
                                                   &m_textureFromImg);
    SAFE_RELEASE(m_texture);
    if (FAILED(hr)) {
      ERROR("Texture", "init", "Failed to create shader resource view for PNG texture");
      return hr;
    }
    break;
  }
  default:
    ERROR("Texture", "init", "Unsupported extension type");
    return E_INVALIDARG;
  }
  return hr;
}
HRESULT 
Texture::init(Device device,
              unsigned int width,
              unsigned int height,
              DXGI_FORMAT format,
              unsigned int bindFlags,
              unsigned int sampleCount,
              unsigned int qualityLevels) {
  if (!device.m_device) {
    ERROR("Texture", "init", "Device is nullptr in texture initialization method");
    return E_POINTER;
  }
  if (width == 0 || height == 0) {
    ERROR("Texture", "init", "Width and height must be greater than 0");
    return E_INVALIDARG;
  }
  HRESULT hr = S_OK;
  // Configuración de la textura
  D3D11_TEXTURE2D_DESC desc = {};
  desc.Width = width;
  desc.Height = height;
  desc.MipLevels = 1;
  desc.ArraySize = 1;
  desc.Format = format;
  desc.SampleDesc.Count = sampleCount;
  desc.SampleDesc.Quality = qualityLevels;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.BindFlags = bindFlags;
  hr = device.CreateTexture2D(&desc, nullptr, &m_texture);
  if (FAILED(hr)) {
    ERROR("Texture", "init", "Failed to create texture with the specified parameters");
    return hr;
  }
  return hr;
}
void 
Texture::update() {
}
void 
Texture::render(DeviceContext& deviceContext, 
                unsigned int StartSlot, 
                unsigned int NumViews) {
  if (m_textureFromImg) {
    ID3D11ShaderResourceView* nullSRV[] = { nullptr };
    deviceContext.PSSetShaderResources(StartSlot, 
                                       NumViews, 
                                       nullSRV);
    deviceContext.PSSetShaderResources(StartSlot, 
                                       NumViews, 
                                       &m_textureFromImg);
  }
  else {
    ERROR("Texture", "render", "Texture resource is not initialized");
  }
}
void 
Texture::destroy() {
  SAFE_RELEASE(m_texture);
  SAFE_RELEASE(m_textureFromImg);
}