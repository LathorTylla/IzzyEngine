# IzzyEngine
IzzyEngine es un motor gráfico 3D en C++ desarrollado utilizando DirectX 11, ImGui, y carga de modelos FBX y OBJ.
Objetivo demostrar conceptos fundamentales de renderizado en tiempo real, arquitectura de motores gráficos, y desarrollo de herramientas de edición con un ECS básico.


# Características
• Carga de Modelos 3D: Soporte para .obj y .fbx.

• Sistema ECS Ligero: Entidades y componentes como Actor, Transform y MeshComponent.

• Interfaz de Usuario: Basada en Dear ImGui con Docking y Viewports.

• Transformaciones en Tiempo Real: Mover, rotar y escalar actores desde la interfaz.

• Renderizado DirectX 11: Manejo manual de buffers, swapchain, viewport.

• Estilo de UI Personalizado: Apariencia retro (estilo neón).

• Sistema Modular: Código limpio y separado en subsistemas: ECS, Utilities.

# Estructura del Proyecto
Está dividido en varias partes que organizan sus componentes principales:

IzzyEngine

• ECS -->                 Entity Component System (Actor, Transform, Component)

• Utilities -->           Utilidades de matemáticas

• obj -->                 Carga de modelos OBJ

• fbx -->                 Carga de modelos FBX

• BaseApp.h/cpp -->          Núcleo de inicialización y ciclo de vida

• DepthStencilView.h -->     Manejo de Depth Buffer

• Device.h -->               Inicialización del dispositivo DirectX11

• DeviceContext.h -->        Contexto de dispositivos

• InputLayout.h -->         Input Layout para los shaders

• ModelLoader.h -->         Carga de modelos 3D

• RenderTargetView.h -->     Vista de renderizado

• SamplerState.h -->        Estados de muestreo de texturas

• ShaderProgram.h -->        Carga y administración de shaders

• SwapChain.h -->           Administración de la swapchain

• Texture.h -->             Manejo de texturas

• Viewport.h -->            Configuración de viewport

• stb_image.h -->            Carga de imágenes para texturas

• Prerequisites.h -->       Includes globales y definiciones

• Resource.h -->             Manejo básico de recursos

• UserInterface.h/cpp -->    Manager para ImGui y paneles Docking

• Window.h -->               # Ventana principal (Win32)

# Uso de la Interfaz
• Actors Panel: Lista todos los actores de la escena. Permite seleccionar cuál editar.

• Transform Panel: Modifica position, rotation, y scale del actor seleccionado en tiempo real.

• Test Docking Panel: Demostración del sistema de ventanas docking de ImGui.

# Capturas de Pantalla

![image](https://github.com/user-attachments/assets/bdaa348e-64cb-48d0-95a5-ad9bcaf688ac)

![image](https://github.com/user-attachments/assets/67da9850-4fc2-44eb-b0b5-eda63404767a)

![image](https://github.com/user-attachments/assets/0a61c2af-697c-4af3-9b1b-1ca4069de8d0)

# Créditos
Desarrollador: Lathor_Tylla

Inspirado por: Roberto Charretón Kaplun, Microsoft DirectX Samples, ImGui, Bly7.

# Licencia
Este proyecto está bajo la licencia MIT.
