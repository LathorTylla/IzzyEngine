#pragma once
#include "Prerequisites.h"

/*
 * @brief Forward Declarations.
 *
 * Se utilizan para declarar clases sin necesidad de incluir sus archivos de encabezado completos.
 * Esto optimiza el tiempo de compilación y evita dependencias circulares.
 */

class Device;             /* Encargado de la creación y gestión de recursos. */
class DeviceContext;      /* Maneja la ejecución de comandos en la GPU. */
class Texture;            /* Representa una textura utilizada en el proceso de renderizado. */
class DepthStencilView;   /* Gestiona la profundidad y stencil en la escena. */

/*
 * @brief RenderTargetView.
 *
 * Gestiona la vista del render target, permitiendo definir el área
 * donde se dibujarán los gráficos antes de enviarlos a la pantalla.
 */
class
RenderTargetView {
public:
  RenderTargetView() = default;   //constructor por defecto
  ~RenderTargetView() = default;  //destructor por defecto

  /*
   * @brief Inicializa el RenderTargetView a partir de un back buffer.
   *
   * Configura la vista del render target utilizando una textura existente
   * para almacenar la imagen renderizada antes de su visualización en pantalla.
   *
   * @param device        Dispositivo encargado de la creación de recursos gráficos.
   * @param backBuffer    Textura donde se almacenará la imagen renderizada.
   * @param Format        Formato de la textura utilizada en el render target.
   * @return             Devuelve un HRESULT indicando el éxito o fallo de la inicialización.
   */
  HRESULT
  init(Device& device, 
       Texture& backBuffer, 
       DXGI_FORMAT Format);

  /*
   * @brief Actualiza el RenderTargetView.
   *
   * Permite actualizar dinámicamente los recursos asociados si es necesario.
   */
  void
  update();

  /*
   * @brief Renderiza la escena utilizando el RenderTargetView y DepthStencilView.
   *
   * Configura los buffers de renderizado y de profundidad, además de limpiar el
   * render target antes de la generación del nuevo frame.
   *
   * @param deviceContext     Contexto del dispositivo que maneja los comandos de renderizado.
   * @param depthStencilView  Vista de profundidad utilizada para calcular la distancia de los objetos en la escena.
   * @param numViews          Número de vistas a configurar en el pipeline de renderizado.
   * @param ClearColor        Color de limpieza del buffer antes de renderizar un nuevo frame.
   */
  void
  render(DeviceContext& deviceContext,
         DepthStencilView& depthStencilView,
         unsigned int numViews,
         const float ClearColor[4]);

  /*
   * @brief Libera los recursos asociados al RenderTargetView.
   *
   * Garantiza la correcta liberación de memoria evitando posibles fugas de recursos.
   */
  void
  destroy();

public:

  /*
   * @brief Puntero a ID3D11RenderTargetView.
   *
   * Define la superficie de renderizado en DirectX 11 donde se almacenan los resultados
   * antes de su presentación en pantalla.
   */
  ID3D11RenderTargetView* m_renderTargetView = nullptr;
};