//#include "ModelLoader.h"
//
//bool 
//ModelLoader::LoadModel(const std::string& filePath){
//  FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
//
//  if (!lImporter->Initialize(filePath.c_str(), -1, lSdkManager->GetIOSettings())){
//    ERROR("ModelLoader", "LoadFBXModel", "Error al cargar el archivo FBX: " << filePath.c_str());
//    ERROR("ModelLoader", "LoadFBXModel", "Error: " << lImporter->GetStatus().GetErrorString());
//    return false;
//  }
//
//  if (lImporter->Import(lScene)){
//    ERROR("ModelLoader", "lImporter->Import", "Unable to import the FBX file: " << filePath.c_str());
//    lImporter->Destroy();
//    return false;
//
//  }
//
//  lImporter->Destroy();
//  MESSAGE("ModelLoader", "LoadFBXModel", "Successfuly imported the FBX scene from file: " << filePath.c_str());
//
//  return false;
//}
//
//void 
//ModelLoader::ProcessFBXNode(FbxNode* node){
//  if (node->GetNodeAttribute()) {
//    if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh) {
//      ProcessFBXMesh(node);
//    }
//  }
//
//  for (int i = 0; i < node->GetChildCount(); i++) {
//    ProcessFBXNode(node->GetChild(i));
//  }
//}
//
//void 
//ModelLoader::ProcessFBXMesh(FbxNode* node){
//  //01. Get the mesh if node has one. exit early
//  FbxMesh* mesh = node->GetMesh();
//  if (!mesh) return;
//
//  std::vector<SimpleVertex> vertices;
//  std::vector<unsigned int> indices;
//
//  //02. Process the vertices, extract the position, normal and uv
//  for (int i = 0; i < mesh->GetControlPointsCount(); i++) {
//    SimpleVertex vertex;
//    FbxVector4* controlPoint = mesh->GetControlPoints();
//    vertex.Pos = XMFLOAT3((float)controlPoint[i][0], 
//                          (float)controlPoint[i][1], 
//                          (float)controlPoint[i][2]);
//    vertices.push_back(vertex);
//  }
//  //03. Process UV coordinates
//  if (mesh->GetElementUVCount() > 0) {
//    FbxGeometryElementUV* uvElement = mesh->GetElementUV(0);
//    FbxGeometryElement::EMappingMode mappingMode = uvElement->GetMappingMode();
//    FbxGeometryElement::EReferenceMode referenceMode = uvElement->GetReferenceMode();
//    int polyIndexCounter = 0;
//
//    //03.1 Iterate through the polygons in mesh
//    for (int polyIndex = 0; polyIndex < mesh->GetPolygonCount(); polyIndex++) {
//      int polySize = mesh->GetPolygonSize(polyIndex);
//
//      //03.1.1 Process the vertices in the polygon
//      for (int vertIndex = 0; vertIndex < polySize; vertIndex++) {
//        int controlPointIndex = mesh->GetPolygonVertex(polyIndex, vertIndex);
//        int uvIndex = -1;
//      
//      //03.1.1.1 Handle the UV mapping mode by control point
//      if (mappingMode == FbxGeometryElement::eByControlPoint) {
//        if (referenceMode == FbxGeometryElement::eDirect) { 
//          uvIndex = controlPointIndex;
//        }
//        else if (referenceMode == FbxGeometryElement::eIndexToDirect) {
//          uvIndex = uvElement->GetIndexArray().GetAt(controlPointIndex);
//        }
//      }
//      //03.1.1.2 Handle UV mapping mode by poligon vertex
//      else if (mappingMode == FbxGeometryElement::eByPolygonVertex) {
//        if (referenceMode == FbxGeometryElement::eDirect ||
//          referenceMode == FbxGeometryElement::eIndexToDirect) {
//          uvIndex = uvElement->GetIndexArray().GetAt(polyIndexCounter);
//          polyIndexCounter++;
//        }
//      }
//      //03.1.1.3 if valid uv index, set the texture coordinates
//      if (uvIndex != -1) {
//        FbxVector2 uv = uvElement->GetDirectArray().GetAt(uvIndex);
//        vertices[controlPointIndex].Tex = XMFLOAT2((float)uv[0], (float)uv[1]);
//      }
//     }
//    }
//  }
//  //04. Process the indices, store each polygon vertex index
//  for (int i = 0; i < mesh->GetPolygonCount(); i++) {
//    for (int j = 0; j < mesh->GetPolygonSize(i); j++) {
//      indices.push_back(mesh->GetPolygonVertex(i, j));
//    }
//  }
//  //05. Create a new mesh component and store the vertices and indices
//  MeshComponent meshData;
//  meshData.m_name = node->GetName();
//  meshData.m_vertex = vertices;
//  meshData.m_index = indices;
//  meshData.m_numVertex = vertices.size();
//  meshData.m_numIndex = indices.size();
//
//  //06. Add the processed mesh to the meshes vector
//  meshes.push_back(meshData);
//}
