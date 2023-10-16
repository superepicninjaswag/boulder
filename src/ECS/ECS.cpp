#include "ECS.h"

IDManager &ECS::GetIDs()
{
    return _ids;
}

Pool<MeshComponent> &ECS::GetMeshes()
{
    return _meshes;
}

Pool<TransformComponent> &ECS::GetTransforms()
{
    return _transforms;
}