#pragma once

//Librerias STD
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>

//<memory>
#include <thread>

//Librerias DirectX
#include <D3D11.h>
#include <D3DX11.h>
#include <d3dcompiler.h>
#include "resource.h"
#include "Resource.h"

//Macros
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

#define ERROR( classObj, method, errorMSG )  \
{                                            \
   std::wostringstream os_;                  \
   os_ << "ERROR : " << classObj << "::" << method << " : " << "  Error in data from params [" << errorMSG << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
   exit(1);                                  \
}

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct 
SimpleVertex{
  XMFLOAT3 Pos;
  XMFLOAT2 Tex;
};

struct 
CBNeverChanges{
  XMMATRIX mView;
};

struct 
CBChangeOnResize{
  XMMATRIX mProjection;
};

struct 
CBChangesEveryFrame{
  XMMATRIX mWorld;
  XMFLOAT4 vMeshColor;
};