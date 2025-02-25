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

	m_shaderFileName = fileName;

	// Crear el Vertex Shader
	HRESULT hr = CreateShader(device, ShaderType::VERTEX_SHADER);
	if (FAILED(hr)) return hr;

	// Crear el Input Layout
	hr = CreateInputLayout(device, Layout);
	if (FAILED(hr)) return hr;

	// Crear el Pixel Shader
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

	m_inputLayout.render(deviceContext);
	deviceContext.VSSetShader(m_VertexShader, nullptr, 0);
	deviceContext.PSSetShader(m_PixelShader, nullptr, 0);
}

void
ShaderProgram::destroy() {
	SAFE_RELEASE(m_VertexShader);
	m_inputLayout.destroy();
	SAFE_RELEASE(m_PixelShader);
	SAFE_RELEASE(m_vertexShaderData);
	SAFE_RELEASE(m_pixelShaderData);
}

HRESULT
ShaderProgram::CreateInputLayout(Device& device, 
																 std::vector<D3D11_INPUT_ELEMENT_DESC> Layout) {
	if (!m_vertexShaderData) {
		ERROR("ShaderProgram", "CreateInputLayout", "VertexShaderData is nullptr");
		return E_POINTER;
	}

	HRESULT hr = m_inputLayout.init(device, Layout, m_vertexShaderData);
	SAFE_RELEASE(m_vertexShaderData);

	if (FAILED(hr)) {
		ERROR("ShaderProgram", "CreateInputLayout", "Failed to create InputLayout");
	}

	return hr;
}

HRESULT
ShaderProgram::CreateShader(Device& device, 
														ShaderType type) {
	HRESULT hr = S_OK;
	ID3DBlob* shaderData = nullptr;
	const char* shaderEntryPoint = (type == PIXEL_SHADER) ? "PS" : "VS";
	const char* shaderModel = (type == PIXEL_SHADER) ? "ps_4_0" : "vs_4_0";

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