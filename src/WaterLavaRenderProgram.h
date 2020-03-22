#pragma once

#include "RenderProgram.h"
#include "GpuProgram.h"

// terrain mesh shader
class WaterLavaRenderProgram: public RenderProgram
{
public:
    WaterLavaRenderProgram(): RenderProgram("shaders/water_lava.glsl")
    {
    }

    void SetViewProjectionMatrix(const glm::mat4& viewProjectionMatrix)
    {
        debug_assert(IsProgramLoaded());
        mGpuProgram->SetUniformParam(mUniformID_view_projection_matrix, viewProjectionMatrix);
    }

    void SetTranslucency(float translucency)
    {
        debug_assert(IsProgramLoaded());
        mGpuProgram->SetUniformParam(mUniformID_translucency, translucency);
    }

    void SetWaveParams(float waveTime, float waveWidth, float waveHeight, float waterLine)
    {
        debug_assert(IsProgramLoaded());

        glm::vec4 waveParams(waveTime, waveWidth, waveHeight, waterLine);
        mGpuProgram->SetUniformParam(mUniformID_wave_params, waveParams);
    }

private:
    void OnProgramLoad() override
    {
        mUniformID_view_projection_matrix = mGpuProgram->QueryUniformLocation("view_projection_matrix");
        debug_assert(mUniformID_view_projection_matrix != GpuVariable_NULL);

        mUniformID_translucency = mGpuProgram->QueryUniformLocation("translucency");
        debug_assert(mUniformID_translucency != GpuVariable_NULL);

        mUniformID_wave_params = mGpuProgram->QueryUniformLocation("wave_params");
        debug_assert(mUniformID_wave_params != GpuVariable_NULL);

        // configure input layout
        mGpuProgram->BindAttribute(eVertexAttribute_Position0, "in_pos");
        mGpuProgram->BindAttribute(eVertexAttribute_Texcoord0, "in_texcoord");
    }

    void OnProgramFree() override
    {
        mUniformID_view_projection_matrix = GpuVariable_NULL;
        mUniformID_translucency = GpuVariable_NULL;
        mUniformID_wave_params = GpuVariable_NULL;
    }

private:
    // render constants
    GpuVariableLocation mUniformID_view_projection_matrix = GpuVariable_NULL;
    GpuVariableLocation mUniformID_translucency = GpuVariable_NULL;
    GpuVariableLocation mUniformID_wave_params = GpuVariable_NULL;
};