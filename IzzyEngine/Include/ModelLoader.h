#pragma once
#include "Prerequisites.h"
#include "MeshComponent.h"
#include "fbxsdk.h"

/*
* @brief ModelLoader.
*
* Clase encargada de cargar modelos 3D en formato FBX y OBJ.
* Utiliza la biblioteca FBX SDK para la carga de modelos FBX.
*/
class 
ModelLoader {
public:
  ModelLoader() = default;  // Constructor por defecto
  ~ModelLoader() = default; // Destructor por defecto

  /*
  * @brief Inicializa FBX Manager.
	*/
	bool
	InitializeFBXManager();

	/*
  * @brief carga un modelo FBX.
  * @param filePath: Ruta del archivo FBX a cargar.
	*/
	bool 
	LoadFBXModel(const std::string & filePath);

	/*
  * @brief Procesa los nodos FBX.
  * @param node: Nodo FBX a procesar.
	*/
	void 
  ProcessFBXNode(FbxNode* node);

  /*
  * @brief Procesa la malla FBX.
  * @param node: Nodo FBX que contiene la malla a procesar.
  */
  void 
  ProcessFBXMesh(FbxNode* node);

  /*
  * @brief Procesa los materiales FBX.
  * @param material: Material FBX a procesar.
  */
  void 
  ProcessFBXMaterials(FbxSurfaceMaterial* material);

  /*
  * @brief vector de nombres de texturas.
  */
	std::vector<std::string> 
  GetTextureFileNames() const { return textureFileNames; }

  /*
  * @brief Carga un modelo OBJ.
  * @param filePath: Ruta del archivo OBJ a cargar.
  */
  bool 
	LoadObjModel(const std::string& filePath);
private:
  FbxManager* lSdkManager;  // FBX SDK Manager
  FbxScene* lScene;  // FBX Scene
  std::vector<std::string> textureFileNames; // Vector de nombres de texturas
public:
  std::vector<MeshComponent> meshes; // Vector de componentes de malla
};