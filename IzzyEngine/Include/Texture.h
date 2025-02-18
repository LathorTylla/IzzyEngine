#pragma once
#include "Prerequisites.h"

/*
 * @brief Forward Declarations.
 *
 * Declaraci�n anticipada de clases para optimizar compilaci�n y evitar dependencias circulares.
 */
class Device;         /* Encargado de la creaci�n y gesti�n de recursos gr�ficos. */
class DeviceContext;  /* Encargado de asignar y ejecutar los recursos gr�ficos. */

/*
 * @brief Texture.
 *
 * Clase encargada de la creaci�n y manipulaci�n de texturas en DirectX 11.
 * Permite cargar texturas desde archivos o crearlas en memoria.
 */
class
Texture {
public:
  Texture() = default;  //constructor por defecto
  ~Texture() = default; //destructor por defecto
  /*
   * @brief Crea una textura a partir de una imagen en el ordenador.
   *
   * @param device       Dispositivo encargado de la gesti�n de recursos en memoria.
   * @param textureName  Nombre de la textura para su carga en memoria.
   * @param extensionType Tipo de extensi�n de la imagen (DDS, PNG, JPG).
   * @return            Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
   */
  HRESULT
  init(Device device,
       const std::string& textureName,
       ExtensionType extensionType);
  /*
   * @brief Crea una textura 2D en memoria a partir de datos proporcionados por el desarrollador.
   *
   * @param device        Proporciona los recursos necesarios para crear la textura.
   * @param width         Ancho de la textura.
   * @param height        Alto de la textura.
   * @param Format        Formato de la textura en memoria.
   * @param BindFlags     Clasificaci�n de la textura seg�n su uso.
   * @param sampleCount   N�mero de muestras para anti-aliasing (opcional, por defecto 1).
   * @param qualityLevels Niveles de calidad para el muestreo (opcional, por defecto 0).
   * @return             Devuelve un HRESULT indicando el �xito o fallo de la operaci�n.
   */
  HRESULT
    init(Device device,
         unsigned int width,
         unsigned int height,
         DXGI_FORMAT Format,
         unsigned int BindFlags,
         unsigned int sampleCount = 1,
         unsigned int qualityLevels = 0);
  /*
   * @brief Actualiza la l�gica de la textura si es necesario.
   */
  void
  update();

  /*
   * @brief Dibuja los recursos de la textura en la pantalla (solo si es necesario).
   *
   * @param deviceContext Administra la asignaci�n de los recursos para su uso.
   * @param StartSlot     Define el punto inicial en memoria para la textura.
   * @param NumViews      Cantidad de vistas asignadas a la textura.
   */
  void
  render(DeviceContext& deviceContext, 
         unsigned int StartSlot, 
         unsigned int NumViews);
  /*
   * @brief Libera los recursos almacenados en memoria por la textura.
   */
  void
  destroy();

public:
  /*
   * @brief Puntero a ID3D11Texture2D.
   *
   * Maneja la textura como un recurso en memoria.
   */
  ID3D11Texture2D* m_texture = nullptr;
  /*
   * @brief Puntero a ID3D11ShaderResourceView.
   *
   * Permite utilizar la textura como un recurso de imagen en los shaders.
   */
  ID3D11ShaderResourceView* m_textureFromImg;
};