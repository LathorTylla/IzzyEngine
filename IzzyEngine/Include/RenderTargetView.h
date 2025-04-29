#pragma once
#include "Prerequisites.h"

/*
 * @brief Forward Declarations.
 *
 * Se utilizan para declarar clases sin necesidad de incluir sus archivos de encabezado completos.
 * Esto optimiza el tiempo de compilaci�n y evita dependencias circulares.
 */

class Device;             /* Encargado de la creaci�n y gesti�n de recursos. */
class DeviceContext;      /* Maneja la ejecuci�n de comandos en la GPU. */
class Texture;            /* Representa una textura utilizada en el proceso de renderizado. */
class DepthStencilView;   /* Gestiona la profundidad y stencil en la escena. */

/*
 * @brief RenderTargetView.
 *
 * Gestiona la vista del render target, permitiendo definir el �rea
 * donde se dibujar�n los gr�ficos antes de enviarlos a la pantalla.
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
   * para almacenar la imagen renderizada antes de su visualizaci�n en pantalla.
   *
   * @param device        Dispositivo encargado de la creaci�n de recursos gr�ficos.
   * @param backBuffer    Textura donde se almacenar� la imagen renderizada.
   * @param Format        Formato de la textura utilizada en el render target.
   * @return             Devuelve un HRESULT indicando el �xito o fallo de la inicializaci�n.
   */
  HRESULT
  init(Device& device, 
       Texture& backBuffer, 
       DXGI_FORMAT Format);

  /*
   * @brief Actualiza el RenderTargetView.
   *
   * Permite actualizar din�micamente los recursos asociados si es necesario.
   */
  void
  update();

  /*
   * @brief Renderiza la escena utilizando el RenderTargetView y DepthStencilView.
   *
   * Configura los buffers de renderizado y de profundidad, adem�s de limpiar el
   * render target antes de la generaci�n del nuevo frame.
   *
   * @param deviceContext     Contexto del dispositivo que maneja los comandos de renderizado.
   * @param depthStencilView  Vista de profundidad utilizada para calcular la distancia de los objetos en la escena.
   * @param numViews          N�mero de vistas a configurar en el pipeline de renderizado.
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
   * Garantiza la correcta liberaci�n de memoria evitando posibles fugas de recursos.
   */
  void
  destroy();

public:

  /*
   * @brief Puntero a ID3D11RenderTargetView.
   *
   * Define la superficie de renderizado en DirectX 11 donde se almacenan los resultados
   * antes de su presentaci�n en pantalla.
   */
  ID3D11RenderTargetView* m_renderTargetView = nullptr;
};