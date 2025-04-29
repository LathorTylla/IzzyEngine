#pragma once
#include "Prerequisites.h"
class Device;
class DeviceContext;

/*
 * @brief InputLayout.
 *
 * Clase encargada de gestionar el Input Layout en DirectX 11.
 * Define la estructura de los v�rtices que se env�an a la GPU para su procesamiento.
 */

class 
InputLayout{
public:
  InputLayout() = default;	// Constructor por defecto
  ~InputLayout() = default; // Destructor por defecto

  /*
  * @brief Inicializa el InputLayout a partir de un shader compilado.
  * @param device        Dispositivo encargado de la creaci�n de recursos gr�ficos.
  * @param Layout        Vector que contiene la descripci�n del layout de entrada.
  * @param VertexShaderData Puntero a los datos del shader compilado.
	*/
	HRESULT 
	init(Device& device, 
			 std::vector<D3D11_INPUT_ELEMENT_DESC> & Layout, 
			 ID3DBlob* VertexShaderData);

	/*
  * @brief Actualiza la l�gica del InputLayout.
	*/
	void 
	update();

	/*
  * @brief Renderiza el InputLayout.
  * @param deviceContext Contexto del dispositivo encargado de administrar los recursos gr�ficos.
	*/
	void 
	render(DeviceContext& deviceContext);

  /*
  * @brief Libera los recursos utilizados por el InputLayout.
  */
	void 
	destroy();

public:
  ID3D11InputLayout* m_inputLayout = nullptr; // Puntero a ID3D11InputLayout

};
