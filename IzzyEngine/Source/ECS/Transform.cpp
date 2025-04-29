#include "ECS\Transform.h"
#include "DeviceContext.h"

void
Transform::init() {
scale.one();

  matrix = XMMatrixIdentity();
}

void
Transform::update(float deltaTime) {
  // Aplicar escala
  XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);
  // Aplicar rotacion
  XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
  // Aplicar traslacion
  XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

  // Componer la matriz final en el orden: scale -> rotation -> translation
  matrix = scaleMatrix * rotationMatrix * translationMatrix;
}

void
Transform::setTransform(const EngineUtilities::Vector3& newPos,
                        const EngineUtilities::Vector3& newRot,
                        const EngineUtilities::Vector3& newSca) {
  position = newPos;
  rotation = newRot;
  scale = newSca;
}