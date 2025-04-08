#pragma once
#include "Prerequisites.h"
#include "MeshComponent.h"
#include "fbxsdk.h"

class 
ModelLoader{
public:
  ModelLoader() = default;
  ~ModelLoader() = default;

  bool 
  LoadModel(const std::string& filePath);

  void 
  ProcessFBXNode(FbxNode* node);

  void 
  ProcessFBXMesh(FbxNode* node);

  void 
  ProcessFBXMaterial(FbxSurfaceMaterial* material);

  std::vector<std::string>
    GetTextureFileNames() const { return textureFileNames; }

private:

  FbxManager* lSdkManager;
  FbxScene* lScene;
  std::vector<std::string> textureFileNames;

public:
  std::vector<MeshComponent> meshes;

};

