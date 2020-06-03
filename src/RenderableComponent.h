#pragma once

#include "GameObjectComponent.h"

// base class for renderable objects
class RenderableComponent: public GameObjectComponent
{
    decl_rtti(RenderableComponent, GameObjectComponent)

    friend class SceneRenderList;

public:
    RenderableComponent(GameObject* sceneObject);

    // register itself for rendering on current frame
    // @param renderList: Current frame render list
    void RegisterForRendering(SceneRenderList& renderList);

    // setup renderable component mesh materials
    void SetMeshMaterialsCount(int numMaterials);
    void SetMeshMaterial(int materialIndex, const MeshMaterial& meshMaterial);
    void ClearMeshMaterials();

    // access renderable component mesh materials by index
    int GetMaterialsCount() const;
    MeshMaterial* GetMeshMaterial(int materialIndex);
    MeshMaterial* GetMeshMaterial();
    // readonly acceess to materials by index
    const MeshMaterial* GetMeshMaterial(int materialIndex) const;
    const MeshMaterial* GetMeshMaterial() const;

    // test whether renderable component mesh has opaque or transparent parts
    bool HasOpaqueMeshParts() const;
    bool HasTransparentMeshParts() const;

    // prepare/unload renderable component mesh for rendering
    virtual void PrepareRenderResources();
    virtual void ReleaseRenderResources();

    // issue draw on specific render pass
    // @param renderContext: Scene render context
    virtual void RenderFrame(SceneRenderContext& renderContext);

    // destroy renderable component instance
    void DestroyComponent() override;

protected:
    // setup draw calls for renderable component
    void SetDrawCallsCount(int numDrawCalls);
    void SetDrawCall(int drawCall, int materialIndex, int vertexOffset, int indexOffset, int vertexCount, int triangleCount);
    void ClearDrawCalls();

protected:

    // defines single draw call operation
    struct DrawCall
    {
    public:
        // geometry offset within vertex/index buffers, in bytes
        int mVertexDataOffset = 0;
        int mIndexDataOffset = 0;

        // geometry elements count
        int mVertexCount = 0;
        int mTriangleCount = 0;

        // material index within mesh materials array
        int mMaterialIndex = 0;
    };

    std::vector<MeshMaterial> mMeshMaterials;
    std::vector<DrawCall> mDrawCalls;

    GpuBuffer* mVertexBuffer = nullptr;
    GpuBuffer* mIndexBuffer = nullptr;
    RenderProgram* mRenderProgram = nullptr;
};