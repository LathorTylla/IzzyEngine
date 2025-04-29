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
  //m_psyduck.LoadFBXModel("Models/Psyduck.FBX");


  // Create the constant buffer
  hr = m_neverChanges.init(m_device, sizeof(CBNeverChanges));
  if (FAILED(hr))
    return hr;

  hr = m_changeOnResize.init(m_device, sizeof(CBChangeOnResize));
  if (FAILED(hr))
    return hr;

  // Initialize the view matrix
  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  m_View = XMMatrixLookAtLH(Eye, At, Up);

  // Initialize the projection matrix
  m_userInterface.init(m_window.m_hWnd, m_device.m_device, m_deviceContext.m_deviceContext);

  // Load the Texture
  Texture Body;
  Body.init(m_device, "Textures/Body.png", ExtensionType::PNG);
  Texture Eyes;
  Eyes.init(m_device, "Textures/Eye.png", ExtensionType::PNG);
  Texture Iris;
  Iris.init(m_device, "Textures/Iris.png", ExtensionType::PNG);

  m_default.init(m_device, "Textures/Default.png", ExtensionType::PNG);

  m_psyduckTextures.push_back(Body);
  m_psyduckTextures.push_back(Eyes);
  m_psyduckTextures.push_back(Iris);
  m_psyduckTextures.push_back(m_default);

  // Load Model
  m_psyduck.LoadFBXModel("Models/Psyduck.FBX");
  APsyduck = EngineUtilities::MakeShared<Actor>(m_device);
  APsyduck->setName("Psyduck");
  if (!APsyduck.isNull()) {
    // Init Actor Transform
    APsyduck->getComponent<Transform>()->setTransform(EngineUtilities::Vector3(-0.9f, -2.0f, 2.0f),
                                                      EngineUtilities::Vector3(XM_PI / 0.01f, 3.0f, XM_PI / 0.01f),
                                                      EngineUtilities::Vector3(0.03f, 0.03f, 0.03f));
    // Init Actor Mesh
    APsyduck->setMesh(m_device, m_psyduck.meshes);
    // Init Actor Textures
    APsyduck->setTextures(m_psyduckTextures);

    m_actors.push_back(APsyduck);

    std::string msg = APsyduck->getName() + " - Actor accessed successfully.";
    MESSAGE("Actor", "Actor", msg.c_str());
  }
  else {
    MESSAGE("Actor", "Actor", "Actor resource not found.");
  }

  // Load the Texture
  Texture GokuTexturas;
  GokuTexturas.init(m_device, "Textures/GokuTexturas.png", ExtensionType::PNG);
  
  m_objTextures.push_back(GokuTexturas);
  
  m_objTextures.push_back(m_default);

  // Load Model
  m_objModel.LoadObjModel("Models/goku.obj");
  AObjModel = EngineUtilities::MakeShared<Actor>(m_device);
  AObjModel->setName("Goku chiquito");
  if (!AObjModel.isNull()) {
    // Init Actor Transform
    AObjModel->getComponent<Transform>()->setTransform(EngineUtilities::Vector3(3.0f, -2.0f, 2.0f),
      EngineUtilities::Vector3(XM_PI / 0.05f, 6.0f, XM_PI / 0.05f),
      EngineUtilities::Vector3(1.00f, 1.00f, 1.00f));
    // Init Actor Mesh
    AObjModel->setMesh(m_device, m_objModel.meshes);
    // Init Actor Textures
    AObjModel->setTextures(m_objTextures);

    m_actors.push_back(AObjModel);

    std::string msg = AObjModel->getName() + " - Actor accessed successfully.";
    MESSAGE("Actor", "Actor", msg.c_str());
  }
  else {
    MESSAGE("Actor", "Actor", "Actor resource not found.");
  }

  return S_OK;
}

void
BaseApp::update() {
  // 1) Nueva frame de ImGui
  m_userInterface.update();

  // 2) Panel de selección de actores
  m_userInterface.actorsWindow(m_actors, selectedActorIndex);

  // 3) Ventana de prueba de docking
  m_userInterface.drawTestDock();

  // 4) Actualizar tiempo y cámara 
  static float t = 0.0f;
  if (m_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE) {
    t += XM_PI * 0.0125f;
  }
  else {
    static DWORD start = 0;
    DWORD now = GetTickCount();
    if (!start) start = now;
    t = (now - start) / 1000.0f;
  }
  InputActionMap(t);
  float FOV = XMConvertToRadians(90.0f);
  m_Projection = XMMatrixPerspectiveFovLH(FOV,
    m_window.m_width / (float)m_window.m_height,
    0.01f, 100.0f);
  updateCamera();
  cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
  m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

  // 5) Actualizar todos los actores
  for (auto& actor : m_actors) {
    if (actor) actor->update(t, m_deviceContext);
  }

  // 6) Panel de Transform para el actor seleccionado
  m_userInterface.transformWindow(m_actors[selectedActorIndex]);
}

void
BaseApp::render() {
  // Limpiar los buffers
  const float ClearColor[4] = { 0.0f,
                                0.125f,
                                0.3f,
                                1.0f }; // red, green, blue, alpha

  m_viewport.render(m_deviceContext);

  // Set Render Target View
  m_renderTargetView.render(m_deviceContext,
                            m_depthStencilView,
                            1,
                            ClearColor);

  // Set Depth Stencil View
  m_depthStencilView.render(m_deviceContext);

  
  m_shaderProgram.render(m_deviceContext);

  APsyduck->render(m_deviceContext);

  AObjModel->render(m_deviceContext);

  m_neverChanges.render(m_deviceContext, 0, 1);
  m_changeOnResize.render(m_deviceContext, 1, 1);
 // m_changeEveryFrame.render(m_deviceContext, 2, 1);


  m_userInterface.render();

  m_swapchain.present();
}

void
BaseApp::destroy() {

  if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();

  // Destroy the user interface
  AObjModel->destroy();
  APsyduck->destroy();
  m_neverChanges.destroy();
  m_changeOnResize.destroy();
  m_changeEveryFrame.destroy();
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

  /*if (keys['W']) {
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
  }*/

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
	