#include "BaseApp.h"

HRESULT
BaseApp::init() {
  HRESULT hr = S_OK;

  // Create Swapchain and BackBuffer
  hr = m_swapchain.init(m_device, 
                        m_deviceContext, 
                        m_backBuffer, 
                        m_window);
  if (FAILED(hr)) {
    return hr;
  }

  // Create a render target view
  hr = m_renderTargetView.init(m_device,
                               m_backBuffer,
                               DXGI_FORMAT_R8G8B8A8_UNORM);

  if (FAILED(hr)) {
    return hr;
  }

  // Create a depth stencil
  hr = m_depthStencil.init(m_device,
                           m_window.m_width,
                           m_window.m_height,
                           DXGI_FORMAT_D24_UNORM_S8_UINT,
                           D3D11_BIND_DEPTH_STENCIL,
                           4,
                           0);
  if (FAILED(hr))
    return hr;

  // Create the depth stencil view
  hr = m_depthStencilView.init(m_device,
                               m_depthStencil,
                               DXGI_FORMAT_D24_UNORM_S8_UINT);

  if (FAILED(hr))
    return hr;


  // Setup the viewport
  hr = m_viewport.init(m_window);

  if (FAILED(hr))
    return hr;

  // Define the input layout
  std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

  // Create the input layout
  D3D11_INPUT_ELEMENT_DESC position;
  position.SemanticName = "POSITION";
  position.SemanticIndex = 0;
  position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
  position.InputSlot = 0;
  position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*0*/;
  position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  position.InstanceDataStepRate = 0;
  Layout.push_back(position);

  // Create the input layout
  D3D11_INPUT_ELEMENT_DESC texcoord;
  texcoord.SemanticName = "TEXCOORD";
  texcoord.SemanticIndex = 0;
  texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
  texcoord.InputSlot = 0;
  texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
  texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  texcoord.InstanceDataStepRate = 0;
  Layout.push_back(texcoord);

  // Create the Shader Program
  hr = m_shaderProgram.init(m_device, "IzzyEngine.fx", Layout);

  if (FAILED(hr))
    return hr;

  // Load Model
  m_psyduck.LoadFBXModel("Models/Psyduck.FBX");

  // Create vertex buffer
  SimpleVertex
    vertices[] = {
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
  };

  // Create vertex buffer
  unsigned int
    indices[] = {
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
  };

  // Create the mesh component
  for (SimpleVertex vertex : vertices) {
    m_meshComponent.m_vertex.push_back(vertex);
  }

  for (unsigned int index : indices) {
    m_meshComponent.m_index.push_back(index);
  }
  // Set the number of vertices and indices
  m_meshComponent.m_numVertex = m_meshComponent.m_vertex.size();
  m_meshComponent.m_numIndex = m_meshComponent.m_index.size();
  // Create the vertex buffer
  hr = m_vertexBuffer.init(m_device, m_meshComponent, D3D11_BIND_VERTEX_BUFFER);

  if (FAILED(hr))
    return hr;
  // Create the index buffer
  hr = m_indexBuffer.init(m_device, m_meshComponent, D3D11_BIND_INDEX_BUFFER);

  if (FAILED(hr))
    return hr;

  // Create the constant buffer
  hr = m_neverChanges.init(m_device, sizeof(CBNeverChanges));
  if (FAILED(hr))
    return hr;

  hr = m_changeOnResize.init(m_device, sizeof(CBChangeOnResize));
  if (FAILED(hr))
    return hr;

  hr = m_changeEveryFrame.init(m_device, sizeof(CBChangesEveryFrame));
  if (FAILED(hr))
    return hr;
  // Create the texture
  hr = m_textureCubeImg.init(m_device, "seafloor.dds", ExtensionType::DDS);
  if (FAILED(hr))
    return hr;

  // Create the sample state
  hr = m_samplerState.init(m_device);

  if (FAILED(hr))
    return hr;

  //Matriz de identidad
  scale.x = 1;
  scale.y = 1;
  scale.z = 1;
  // Initialize the world matrices
  m_modelMatrix = XMMatrixIdentity();

  // Initialize the view matrix
  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  m_View = XMMatrixLookAtLH(Eye, At, Up);

  // Initialize the projection matrix
  m_userInterface.init(m_window.m_hWnd, m_device.m_device, m_deviceContext.m_deviceContext);

  return S_OK;
	return E_NOTIMPL;
}

void
BaseApp::update() {

  // Actualizar la interfaz de usuario
  m_userInterface.update();

  // ventana de transform
  ImGui::Begin("Transform", nullptr, ImGuiWindowFlags_NoCollapse);

  //Ventana transform x, y, z
  m_userInterface.vec3Control("Position", &position.x, 0.0f);

  ImGui::End();

  //Ventana de prueba docking
  ImGui::Begin("Test Docking", nullptr, ImGuiWindowFlags_NoCollapse);
  //Ventana de texto
  ImGui::Text("Wenas profe");
  ImGui::End();
  // Actualizar tiempo y rotación
  static float t = 0.0f;
  if (m_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE) {
    t += (float)XM_PI * 0.0125f;
  }
  else {
    // Actualizar el tiempo
    static DWORD dwTimeStart = 0;
    DWORD dwTimeCur = GetTickCount();
    if (dwTimeStart == 0)
      dwTimeStart = dwTimeCur;
    t = (dwTimeCur - dwTimeStart) / 1000.0f;
  }

  // Actualizar la rotación del objeto
  InputActionMap(t);
  rotation.y = t;
  //Esto seria como nuestro transform
  // Actualizar la rotación del objeto y el color
  XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);
  XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
  XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

  // Actualizar la matriz del modelo por escala, rotación y traslación
  m_modelMatrix = scaleMatrix * rotationMatrix * translationMatrix;
  m_vMeshColor = XMFLOAT4(
                         (sinf(t * 1.0f) + 1.0f) * 0.5f,
                         (cosf(t * 3.0f) + 1.0f) * 0.5f,
                         (sinf(t * 5.0f) + 1.0f) * 0.5f,
                         1.0f);

  // componer la matriz en orden de escala, rotacion y traslación
  // Actualizar el buffer constante del frame
  cb.mWorld = XMMatrixTranspose(m_modelMatrix);
  cb.vMeshColor = m_vMeshColor;
  m_changeEveryFrame.update(m_deviceContext, 0, nullptr, &cb, 0, 0);

  float FOV = XMConvertToRadians(90.0f);
  m_Projection = XMMatrixPerspectiveFovLH(FOV, m_window.m_width / (float)m_window.m_height, 0.01f, 100.0f);
  updateCamera();

  // Actualizar la proyección en el buffer constante
  cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
  m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
}

void
BaseApp::render() {
  // Limpiar los buffers
  const float ClearColor[4] = { 0.0f,
                                0.125f,
                                0.3f,
                                1.0f }; // red, green, blue, alpha

  // Set Render Target View
  m_renderTargetView.render(m_deviceContext,
    m_depthStencilView,
    1,
    ClearColor);
  // Set Viewport
  m_viewport.render(m_deviceContext);
  // Set Depth Stencil View
  m_depthStencilView.render(m_deviceContext);

  
  m_shaderProgram.render(m_deviceContext);
  m_vertexBuffer.render(m_deviceContext, 0, 1);
  m_indexBuffer.render(m_deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);
  m_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  m_neverChanges.render(m_deviceContext, 0, 1);
  m_changeOnResize.render(m_deviceContext, 1, 1);
  m_changeEveryFrame.render(m_deviceContext, 2, 1);

  m_changeEveryFrame.render(m_deviceContext, 2, 1, true);

  m_textureCubeImg.render(m_deviceContext, 0, 1);

  m_samplerState.render(m_deviceContext, 0,1);

  m_deviceContext.DrawIndexed(m_meshComponent.m_index.size(), 0, 0);

  m_userInterface.render();

  m_swapchain.present();
}

void
BaseApp::destroy() {

  if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();

  m_textureCubeImg.destroy();
  m_neverChanges.destroy();
  m_changeOnResize.destroy();
  m_changeEveryFrame.destroy();
  m_vertexBuffer.destroy();
  m_indexBuffer.destroy();
  m_shaderProgram.destroy();


  m_depthStencil.destroy();
  m_depthStencilView.destroy();
  m_renderTargetView.destroy();
  m_swapchain.destroy();
  m_deviceContext.destroy();
  m_device.destroy();

  m_userInterface.destroy();
}

void 
BaseApp::InputActionMap(float deltaTime) {

  float sensibility = 0.0001f;     //sensibilidad del movimiento
  float moveSpeedCamera = 0.0001f; //velocidad de la camara

  //movmiento del cubo por teclas W A S D

  if (keys['W']) {
    position.y += sensibility * deltaTime;
  }
  if (keys['S']) {
    position.y -= sensibility * deltaTime;
  }
  if (keys['A']) {
    position.x -= sensibility * deltaTime;
  }
  if (keys['D']) {
    position.x += sensibility * deltaTime;
  }
  if (keys['E']) {
    position.z += sensibility * deltaTime;
  }
  if (keys['Q']) {
    position.z -= sensibility * deltaTime;
  }

  XMVECTOR position = XMLoadFloat3(&m_camera.pos);
  XMVECTOR forward = XMLoadFloat3(&m_camera.forward);
  XMVECTOR right = XMLoadFloat3(&m_camera.right);

  //movimiento de la camara por teclas flechas

  /*if (keys['W']) pos += forward * moveSpeedCamera;
  if (keys['S']) pos -= forward * moveSpeedCamera;
  if (keys['A']) pos -= right * moveSpeedCamera;
  if (keys['D']) pos += right * moveSpeedCamera;*/

  XMStoreFloat3(&m_camera.pos, position);

}

void 
BaseApp::updateCamera() {
  XMVECTOR position = XMLoadFloat3(&m_camera.pos);
  XMVECTOR dir = XMLoadFloat3(&m_camera.forward);
  XMVECTOR up = XMLoadFloat3(&m_camera.up);

  m_View = XMMatrixLookAtLH(position,position+ dir, up);

  cbNeverChanges.mView = XMMatrixTranspose(m_View);
  m_neverChanges.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
}

void
BaseApp::rotateCamera(int mouseX, int mouseY) {
  float offsetX = (mouseX - lastX) * sensitivity; //sensibilidad del movimiento X
  float offsetY = (mouseY - lastY) * sensitivity; //sensibilidad del movimiento Y
  lastX = mouseX; //actualiza la ultima posicion en X
  lastY = mouseY; //actualiza la ultima posicion en Y

  m_camera.yaw += offsetX;   //actualiza el yaw
  m_camera.pitch += offsetY; //actualiza el pitch

  // Limitar la inclinación de la cámara
  if (m_camera.pitch > 1.5f) m_camera.pitch = 1.5f;
  if (m_camera.pitch < -1.5f) m_camera.pitch = -1.5f;

  // Recalcular la dirección hacia adelante
  XMVECTOR forward = XMVectorSet(
    cosf(m_camera.yaw) * cosf(m_camera.pitch),
    sinf(m_camera.pitch),
    sinf(m_camera.yaw) * cosf(m_camera.pitch),
    0.0f
  );

  XMVECTOR right = XMVector3Cross(forward, XMLoadFloat3(&m_camera.up));

  XMStoreFloat3(&m_camera.forward, XMVector3Normalize(forward)); //normaliza el vector forward
  XMStoreFloat3(&m_camera.right, XMVector3Normalize(right));     //normaliza el vector right
}
  
 

HRESULT 
BaseApp::resizeWindow(HWND hWnd, LPARAM lParam){
  //Si existe el swapchain
  if (m_swapchain.m_swapchain) {
    // Destruir el Depth Stencil View, Depth Stencil, Render Target View y Back Buffer
    m_renderTargetView.destroy();
    m_depthStencil.destroy();
    m_depthStencilView.destroy();
    m_backBuffer.destroy();

    // Redimensionar los datos del ancho y alto de la ventana
    m_window.m_width = LOWORD(lParam);
    m_window.m_height = HIWORD(lParam);

    // Redimensionar el buffer del swapchain
    HRESULT hr = m_swapchain.m_swapchain->ResizeBuffers(0,
                                                        m_window.m_width,
                                                        m_window.m_height,
                                                        DXGI_FORMAT_R8G8B8A8_UNORM,
                                                        0);
    // Si falla la redimensión del buffer
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "SwapChain", "Failed to resize buffers");
      return hr;
    }

    // Recrear el back buffer
    hr = m_swapchain.m_swapchain->GetBuffer(0,
                                            __uuidof(ID3D11Texture2D),
                                            reinterpret_cast<void**>(&m_backBuffer.m_texture));
    // Si falla la obtención del buffer
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "ResizeWindow", "Failed to recreate back buffer");
      return hr;
    }

    // Recrear el render target view
    hr = m_renderTargetView.init(m_device,
                                 m_backBuffer,
                                 DXGI_FORMAT_R8G8B8A8_UNORM);
    // Si falla la creación del render target view
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "Render Target View", "Failed to create Render Target View");
      return hr;
    }

    // Recrear el depth stencil
    hr = m_depthStencil.init(m_device,
                             m_window.m_width,
                             m_window.m_height,
                             DXGI_FORMAT_D24_UNORM_S8_UINT,
                             D3D11_BIND_DEPTH_STENCIL,
                             4,
                             0);
    // Si falla la creación del depth stencil
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "Depth Stencil", "Failed to create Depth Stencil");
      return hr;
    }

    // Recrear el depth stencil view
    hr = m_depthStencilView.init(m_device,
                                 m_depthStencil,
                                 DXGI_FORMAT_D24_UNORM_S8_UINT);
    // Si falla la creación del depth stencil view
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "Depth Stencil View", "Failed to create new Depth Stencil View");
      return hr;
    }

    // Actualizar el viewport
    m_viewport.init(m_window);

    // Actualizar la proyección
    m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, 
                                            m_window.m_width / (float)m_window.m_height, 
                                            0.01f, 
                                            100.0f);
    cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
    m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
  }
}



int
BaseApp::run(HINSTANCE hInstance,
						 HINSTANCE hPrevInstance,
						 LPWSTR lpCmdLine,
						 int nCmdShow,
						 WNDPROC wndproc) {
             UNREFERENCED_PARAMETER(hPrevInstance);
             UNREFERENCED_PARAMETER(lpCmdLine);

  if (FAILED(m_window.init(hInstance, nCmdShow, wndproc)))
    return 0;
  if (FAILED(init())) {
    destroy();
    return 0;
  }

  // Main message loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message) {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else {
      update();
      render();
    }
  }

  destroy();

  return (int)msg.wParam;

  return 0;
}
	