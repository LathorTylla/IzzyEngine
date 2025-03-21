#pragma once
#include "Prerequisites.h"
#include "InputLayout.h"

// Forward declaration
class Device;
class DeviceContext;
/*
  * @brief ShaderProgram.
  * 
  * Clase encargada de gestionar los shaders utilizados en la aplicación.
  *
*/
class
ShaderProgram {
public:
  ShaderProgram() = default; // constructor por defecto
  ~ShaderProgram() = default;// destructor por defecto

  /*
   * @brief Inicializa el ShaderProgram.
   * 
   * @param device: Referencia al dispositivo de DirectX 11.
   * @param fileName: Nombre del archivo que contiene el shader.
   * @param Layout: Descripción de los elementos de entrada.
   * @return Devuelve un HRESULT que indica si la inicialización fue exitosa o si hubo un error.
   */
  HRESULT
  init(Device& device,
       const std::string& fileName,
       std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

 /*
  * @brief Método encargado de actualizar la lógica.
  */
  void
  update();

  /*
  * @brief Renderiza ShaderProgram.
  * PARAM deviceContext: Contexto del dispositivo encargado de administrar los recursos gráficos.
  */
  void
  render(DeviceContext& deviceContext);

  /*
  * @brief Libera los recursos utilizados por ShaderProgram.
  */
  void
  destroy();

  /*
  * @brief Crea un InputLayout a partir de una descripción de elementos de entrada.
  * PARAM device: Referencia al dispositivo de DirectX 11.
  * PARAM Layout: Descripción de los elementos de entrada.
  */
  HRESULT
  CreateInputLayout(Device& device, 
                    std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /*
  * @brief Crea un Shader a partir de un tipo.
  * PARAM device: Referencia al dispositivo de DirectX 11.
  * PARAM type: Tipo de Shader.
  */
  HRESULT
  CreateShader(Device& device, ShaderType type);

  /*
  * @brief Compila un shader a partir de un archivo.
  * PARAM szFileName: Nombre del archivo que contiene el shader.
  * PARAM szEntryPoint: Punto de entrada del shader.
  * PARAM szShaderModel: Modelo del shader.
  * PARAM ppBlobOut: Puntero al blob que contiene el shader compilado.
  */
  HRESULT
  CompileShaderFromFile(char* szFileName,
                          LPCSTR szEntryPoint,
                          LPCSTR szShaderModel,
                          ID3DBlob** ppBlobOut);
private:
public:
  ID3D11VertexShader* m_VertexShader = nullptr; // Puntero a ID3D11VertexShader
  ID3D11PixelShader* m_PixelShader = nullptr;   // Puntero a ID3D11PixelShader
  InputLayout m_inputLayout;                    // InputLayout
private:
  std::string m_shaderFileName;                 // Nombre del archivo que contiene el shader
  ID3DBlob* m_vertexShaderData = nullptr;       // Puntero a ID3DBlob
  ID3DBlob* m_pixelShaderData = nullptr;        // Puntero a ID3DBlob
};