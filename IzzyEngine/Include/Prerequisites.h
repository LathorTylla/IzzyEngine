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



//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
  XMFLOAT3 Pos;
  XMFLOAT2 Tex;
};

struct CBNeverChanges
{
  XMMATRIX mView;
};

struct CBChangeOnResize
{
  XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
  XMMATRIX mWorld;
  XMFLOAT4 vMeshColor;
};