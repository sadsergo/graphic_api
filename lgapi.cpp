
#include "lgapi.h"
#include <memory>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>

float E(const LiteMath::float2 &A, const LiteMath::float2 &B, const LiteMath::float2 &P) 
{
  return ((P.x - A.x) * (B.y - A.y) - (P.y - A.y) * (B.x - A.x));
}

float E(const LiteMath::float2 &V, const LiteMath::float2 &VP)
{
  return (V.x * VP.y - V.y * VP.x);
}

struct MyRender : public IRender
{
private:
  Image2D fb;
  std::vector<float> depthbuff;
  TextureContainer Textures;
public:
  ~MyRender() override {
    depthbuff.clear();
  }
    
  unsigned int AddImage(const Image2D &a_img) override;
  void BeginRenderPass(Image2D &fb) override;
  void Draw(PipelineStateObject a_state, Geom a_geom) override;
  void EndRenderPass(Image2D &fb) override;
  void AA_Draw(PipelineStateObject a_state, Geom a_geom) override;
  void get_tr_border(float p[3][4], int &x0, int &y0, int &x1, int &y1) override;
};

std::shared_ptr<IRender> MakeMyImpl() 
{ 
  return std::make_shared<MyRender>(); 
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MyRender::BeginRenderPass(Image2D &fb)
{
  size_t size = fb.height * fb.height;
	this->fb = fb;
	std::fill(&this->fb.data[0], &this->fb.data[size - 1], 0);
	this->depthbuff = std::vector<float>(size, 0);
}

unsigned int MyRender::AddImage(const Image2D &a_img)
{
  unsigned int ind = Textures.addTexture(a_img);

  return ind;
}

void
MyRender::Draw(PipelineStateObject a_state, Geom a_geom)
{
  LiteMath::float4x4 worldViewProj = LiteMath::float4x4(a_state.projMatrix) * LiteMath::float4x4(a_state.worldViewMatrix);
  LiteMath::float4 vertex_vec;

  for (unsigned int tr_num = 0; tr_num < a_geom.primsNum; tr_num++) 
  {
    unsigned vert_indx[3] = 
    {
      a_geom.indices[tr_num * 3 + 0],
      a_geom.indices[tr_num * 3 + 1],
      a_geom.indices[tr_num * 3 + 2]
    };

    float p[3][4] = {{}};
    float col[3][4] = {{}};
    float uv[3][2] = {{}};
    float p_n[3][4] = {{}};

    vertexProcessing(worldViewProj, a_geom.vpos4f, a_geom.vtex2f, a_geom.vcol4f, 
                    vert_indx, LiteMath::int2(fb.width, fb.height), a_state.imgId, p, col, uv);

    LiteMath::float2 A(p[0][0], p[0][1]), B(p[1][0], p[1][1]), C(p[2][0], p[2][1]);
    
    int x0 = 0, x1 = 0, y0 = 0, y1 = 0;
    get_tr_border(p, x0, y0, x1, y1);

    float e = abs(E(A, B, C));

    for (uint32_t x = x0; x <= x1; x++) 
    {
      for (uint32_t y = y0; y <= y1; y++) 
      {
        LiteMath::float2 Point((float)x, (float)y);
        float w0 = E(B - A, Point - A), w1 = E(C - B, Point - B), w2 = E(A - C, Point - C);

        if ((w0 > 0 && w1 > 0 && w2 > 0) || (w0 < 0 && w1 < 0 && w2 < 0)) 
        {
          w0 = abs(w0) / e;
          w1 = abs(w1) / e;
          w2 = abs(w2) / e;

          float w = (p[2][2] * w0 + p[0][2] * w1 + p[1][2] * w2);

          if (1 / w < 1 / depthbuff[fb.width * y + x]) 
          {
            depthbuff[fb.width * y + x] = w;

            if (a_state.imgId != uint32_t(-1)) 
            {
              auto &texture = Textures.textures[a_state.imgId];
              fb.data[fb.width * y + x] = a_state.shaders->textureShader(texture.data, LiteMath::int2(texture.width, texture.height), uv, LiteMath::float4(w0, w1, w2, w));
            }
            else 
            {
              fb.data[fb.width * y + x] = a_state.shaders->colorShader(col, LiteMath::float4(w0, w1, w2, w));
            }
          }
        }
      }
    }  
  }
}

void 
MyRender::AA_Draw(PipelineStateObject a_state, Geom a_geom)
{

}

void MyRender::EndRenderPass(Image2D &fb)
{
   std::fill(&depthbuff[0], &depthbuff[(size_t)fb.width * fb.height - 1], 0);
   // In you software implementation this functionm will likely to be empty
  // but you could wait, for example, for some threads if use multi-threading
}

void
MyRender::get_tr_border(float p[3][4], int &x0, int &y0, int &x1, int &y1)
{
  float xmin = std::min(p[0][0], std::min(p[1][0], p[2][0])), xmax = std::max(p[0][0], std::max(p[1][0], p[2][0])); 
  float ymin = std::min(p[0][1], std::min(p[1][1], p[2][1])), ymax = std::max(p[0][1], std::max(p[1][1], p[2][1]));

  x0 = LiteMath::clamp((int32_t)(xmin), 0, (int32_t)fb.width - 1);
  y0 = LiteMath::clamp((int32_t)(ymin), 0, (int32_t)fb.height - 1);
  x1 = LiteMath::clamp((int32_t)(xmax), 0, (int32_t)fb.width - 1);
  y1 = LiteMath::clamp((int32_t)(ymax), 0, (int32_t)fb.height - 1);
}