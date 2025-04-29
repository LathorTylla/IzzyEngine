#include "ShaderProgram.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT
ShaderProgram::init(Device& device, 
										const std::string& fileName, 
										std::vector<D3D11_INPUT_ELEMENT_DESC> Layout) {
	if (!device.m_device) {
		ERROR("ShaderProgram", "init", "Device is nullptr");
		return E_POINTER;
	}
	if (Layout.empty()) {
		ERROR("ShaderProgram", "init", "Input layout vector is empty");
		return E_INVALIDARG;
	}

  m_shaderFileName = fileName;	//	Safe the shader file name

	// Create the Vertex Shader
	HRESULT hr = CreateShader(device, ShaderType::VERTEX_SHADER);
	if (FAILED(hr)) return hr;

	// Create the Input Layout
	hr = CreateInputLayout(device, Layout);
	if (FAILED(hr)) return hr;

	// Create the Pixel Shader
	hr = CreateShader(device, ShaderType::PIXEL_SHADER);
	return hr;
}

void
ShaderProgram::update() {
}

void
ShaderProgram::render(DeviceContext& deviceContext) {
	if (!m_VertexShader || !m_PixelShader || !m_inputLayout.m_inputLayout) {
		ERROR("ShaderProgram", "render", "Shaders or InputLayout not initialized");
		return;
	}

  m_inputLayout.render(deviceContext);	// Set the input layout
  deviceContext.VSSetShader(m_VertexShader, nullptr, 0);	// Set the vertex shader
	deviceContext.PSSetShader(m_PixelShader, nullptr, 0);	//Set the pixel shader
}

void
ShaderProgram::destroy() {
  SAFE_RELEASE(m_VertexShader);	// Release the vertex shader
  m_inputLayout.destroy();  // Release the input layout
  SAFE_RELEASE(m_PixelShader); // Release the pixel shader
  SAFE_RELEASE(m_vertexShaderData);	// Release the vertex shader data
  SAFE_RELEASE(m_pixelShaderData);	// Release the pixel shader data
}

HRESULT
ShaderProgram::CreateInputLayout(Device& device, 
																 std::vector<D3D11_INPUT_ELEMENT_DESC> Layout) {
	if (!m_vertexShaderData) {
		ERROR("ShaderProgram", "CreateInputLayout", "VertexShaderData is nullptr");
		return E_POINTER;
	}

  HRESULT hr = m_inputLayout.init(device, Layout, m_vertexShaderData);	// Create the input layout
	SAFE_RELEASE(m_vertexShaderData);

	if (FAILED(hr)) {
		ERROR("ShaderProgram", "CreateInputLayout", "Failed to create InputLayout");
	}

	return hr;
}

HRESULT
ShaderProgram::CreateShader(Device& device, 
														ShaderType type) {
  HRESULT hr = S_OK;	// Check if the device is valid
	ID3DBlob* shaderData = nullptr;
  const char* shaderEntryPoint = (type == PIXEL_SHADER) ? "PS" : "VS";	// Entry point for the shader
  const char* shaderModel = (type == PIXEL_SHADER) ? "ps_4_0" : "vs_4_0";	// Shader model

	// Compilar el Shader
	hr = CompileShaderFromFile(m_shaderFileName.data(),
														 shaderEntryPoint,
														 shaderModel,
														 &shaderData);
	if (FAILED(hr)) {
		ERROR("ShaderProgram", "CreateShader", "Failed to compile shader");
		return hr;
	}

	// Crear el shader
	if (type == PIXEL_SHADER) {
		hr = device.CreatePixelShader(shaderData->GetBufferPointer(),
																	shaderData->GetBufferSize(),
																	nullptr,
																	&m_PixelShader);
	}
	else {
		hr = device.CreateVertexShader(shaderData->GetBufferPointer(),
																	 shaderData->GetBufferSize(),
																	 nullptr,
																	 &m_VertexShader);
	}

	if (FAILED(hr)) {
		ERROR("ShaderProgram", "CreateShader", "Failed to create shader " + type);
		shaderData->Release();
		return hr;
	}

	// Almacenar el código compilado
	if (type == PIXEL_SHADER) {
		SAFE_RELEASE(m_pixelShaderData);
		m_pixelShaderData = shaderData;
	}
	else {
		SAFE_RELEASE(m_vertexShaderData);
		m_vertexShaderData = shaderData;
	}

	return S_OK;
}

HRESULT ShaderProgram::CompileShaderFromFile(char* szFileName, 
																						 LPCSTR szEntryPoint, 
																						 LPCSTR szShaderModel, 
																						 ID3DBlob** ppBlobOut){
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, 
														 nullptr, 
														 nullptr, 
														 szEntryPoint,
														 szShaderModel,
														 dwShaderFlags, 
														 0, 
														 nullptr,
														 ppBlobOut, 
														 &pErrorBlob, 
														 nullptr);
	if (FAILED(hr)) {
		if (pErrorBlob != nullptr)
			//std::string error = std::string("Shader compilation error: ") +
			//static_cast<char*>(pErrorBlob->GetBufferPointer());
			//ERROR("ShaderProgram", "CompileShaderFromFile", error.c_str());

			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	SAFE_RELEASE(pErrorBlob)

		return S_OK;
}