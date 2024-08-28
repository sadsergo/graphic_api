#include "shaders.h"

LiteMath::float4 
vertexShader(const LiteMath::float4x4 &worldViewProj, const LiteMath::float4 &vpos4f_i)  
{
  auto vertex_vec = LiteMath::mul(worldViewProj, vpos4f_i);
  float w = vertex_vec.w;
  vertex_vec /= w;
  vertex_vec.w = w;

  return vertex_vec;
}

uint32_t
colorShader(const float col[3][4], const LiteMath::float4 &ws)
{
  float red = (col[2][0] * ws[0] + col[0][0] * ws[1] + col[1][0] * ws[2]) / ws.w;
  float green = (col[2][1] * ws[0] + col[0][1] * ws[1] + col[1][1] * ws[2]) / ws.w;
  float blue = (col[2][2] * ws[0] + col[0][2] * ws[1] + col[1][2] * ws[2]) / ws.w;

  LiteMath::float3 color = {255 * red, 255 * green, 255 * blue};
  
  return ((unsigned char)(255 * red) << 16) + 
    ((unsigned char)(255 * green) << 8) + ((unsigned char)(255 * blue));
}

uint32_t 
textureShader(uint32_t *texture, const LiteMath::int2 &resolution, const float uv[3][2], const LiteMath::float4 &ws)
{
  size_t s = resolution.x * resolution.y;

  int uv1 = (ws[0] * uv[2][0] + ws[1] * uv[0][0] + ws[2] * uv[1][0]) / ws[3] * resolution.x;
  int uv2 = (ws[0] * uv[2][1] + ws[1] * uv[0][1] + ws[2] * uv[1][1]) / ws[3] * resolution.y;

  unsigned int texture_color = texture[(resolution.x * uv2 + uv1) % (s)];

  return texture_color;
}

void
vertexProcessing(const LiteMath::float4x4 &worldViewProj, const float *vpos4f, const float *vtex2f, const float *vcol4f, const unsigned vert_indx[3], LiteMath::int2 resolution, const uint32_t &imgId, float p[3][4], float col[3][4], float uv[3][2])
{
  for (int ind_ver = 0; ind_ver < 3; ++ind_ver) 
  {
    LiteMath::float4 vpos4f_i = 
    {
      vpos4f[4 * vert_indx[ind_ver]],
      vpos4f[4 * vert_indx[ind_ver] + 1],
      vpos4f[4 * vert_indx[ind_ver] + 2],
      vpos4f[4 * vert_indx[ind_ver] + 3],
    };

    auto vertex_vec = LiteMath::mul(worldViewProj, vpos4f_i);
    float w = vertex_vec.w;
    vertex_vec /= w;
    vertex_vec.w = w;

    p[ind_ver][0] = vertex_vec.x;
    p[ind_ver][1] = vertex_vec.y;
    p[ind_ver][2] = vertex_vec.z;
    p[ind_ver][3] = vertex_vec.w;

    for (int i = 0; i < 2; i++) 
    {
      p[ind_ver][i] *= 0.5f;
      p[ind_ver][i] += 0.5f;
    }

    p[ind_ver][0] *= (float)resolution.x;
    p[ind_ver][1] *= (float)resolution.y;

    for (int i = 0; i < 2; i++) 
    {
      p[ind_ver][i] -= 0.5f;
    }

    p[ind_ver][2] = 1 / w;

    if (imgId != uint32_t(-1)) 
    {
      uv[ind_ver][0] = vtex2f[2 * vert_indx[ind_ver]] / w;
      uv[ind_ver][1] = vtex2f[2 * vert_indx[ind_ver] + 1] / w;
    }
    else 
    {
      col[ind_ver][0] = vcol4f[4 * vert_indx[ind_ver]] / w;
      col[ind_ver][1] = vcol4f[4 * vert_indx[ind_ver] + 1] / w;
      col[ind_ver][2] = vcol4f[4 * vert_indx[ind_ver] + 2] / w;
      col[ind_ver][3] = vcol4f[4 * vert_indx[ind_ver] + 3] / w;
    }
  }
}