#pragma once

#include "../external/LiteMath/Image2d.h"

struct ShaderContainer
{
    LiteMath::float4 (*vertexShader)(const LiteMath::float4x4 &worldViewProj, const LiteMath::float4 &vpos4f_i);
    uint32_t (*colorShader)(const float col[3][4], const LiteMath::float4 &ws);
    uint32_t (*textureShader)(uint32_t *texture, const LiteMath::int2 &resolution, const float uv[3][2], const LiteMath::float4 &ws);
    void (*vertexProcessing)(const LiteMath::float4x4 &worldViewProj, const float *vpos4f, const float *vtex2f, const float *vcol4f, const unsigned vert_indx[3], LiteMath::int2 resolution, const uint32_t &imgId, float p[3][4], float col[3][4], float uv[3][2]);
};

LiteMath::float4 vertexShader(const LiteMath::float4x4 &worldViewProj, const LiteMath::float4 &vpos4f_i);
uint32_t colorShader(const float col[3][4], const LiteMath::float4 &ws);
uint32_t textureShader(uint32_t *texture, const LiteMath::int2 &resolution, const float uv[3][2], const LiteMath::float4 &ws);
void vertexProcessing(const LiteMath::float4x4 &worldViewProj, const float *vpos4f, const float *vtex2f, const float *vcol4f, const unsigned vert_indx[3], LiteMath::int2 resolution, const uint32_t &imgId, float p[3][4], float col[3][4], float uv[3][2]);
