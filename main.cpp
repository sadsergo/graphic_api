#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstring>
#include <cstdint>
#include <chrono>

#include "Bitmap.h"
#include "lgapi.h"
#include "scene.h"
#include "external/LiteMath/Image2d.h"

using namespace LiteMath;
using namespace std;

std::shared_ptr<IRender> MakeReferenceImpl(); ///< reference implementation via OpenGL
std::shared_ptr<IRender> MakeMyImpl();        ///< your implementation

void DrawInstances(const SimpleScene& scn, std::shared_ptr<IRender> pRender, RENDER_MODE a_mode)
{
  Geom  geom;
  geom.vpos4f   = scn.geom.vpos4f.data();
  geom.vcol4f   = scn.geom.vcol4f.data();
  geom.vtex2f   = scn.geom.vtex2f.data();
  geom.indices  = scn.geom.indices.data();
  geom.vertNum  = uint32_t(scn.geom.vpos4f.size()/4);
  geom.primsNum = uint32_t(scn.geom.indices.size()/3);

  for(size_t instId = 0; instId < scn.instances.size(); instId++)
  {
    PipelineStateObject pso;
    memcpy(pso.worldViewMatrix, scn.instances[instId].worldViewMatrix, sizeof(pso.worldViewMatrix));
    memcpy(pso.projMatrix,      scn.instances[instId].projMatrix,      sizeof(pso.projMatrix));
    pso.mode  = a_mode;
    if(instId < scn.textures.size())     // do we have texture for this instance?
      pso.imgId = scn.textures[instId];  
    else
      pso.imgId = uint32_t(-1);          
    pRender->Draw(pso, geom);
  }
}

uint32_t WIN_WIDTH  = 1024;
uint32_t WIN_HEIGHT = 1024;

int main(int argc, const char** argv)
{
  std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
  Image2D fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());
  
  #ifdef USE_OPENGL
  std::shared_ptr<IRender> pRender = MakeReferenceImpl();
  std::string imgName = "wref_";
  #else
  std::shared_ptr<IRender> pRender = MakeMyImpl();
  std::string imgName = "zout_";
  #endif

  
  uint32_t testTexId, mosaicTexId, bricksTexId, terrainTex;
  {
    int w, h;
    std::vector<unsigned> pixels;
    pixels      = LoadBMP("data/texture1.bmp", &w, &h);
    testTexId   = pRender->AddImage(Image2D(w,h,pixels.data()));
  
    pixels      = LoadBMP("data/mosaic.bmp", &w, &h);
    mosaicTexId = pRender->AddImage(Image2D(w,h,pixels.data()));
  
    pixels      = LoadBMP("data/red_brick.bmp", &w, &h);
    bricksTexId = pRender->AddImage(Image2D(w,h,pixels.data()));

    pixels      = LoadBMP("data/terrain.bmp", &w, &h);
    terrainTex  = pRender->AddImage(Image2D(w,h,pixels.data()));
  }

  // test #01
  /*{
    auto objects = scn01_colored_triangle();
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_VERT_COLOR);
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
    std::cout << "test_01: " << time << " ms" << std::endl;

    std::string name = imgName + "01.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

    std::fill(&fb.data[0], &fb.data[fb.width * fb.height - 1], 0);
  }*/

  //// test #02
  //{
  //  auto objects = scn02_tri_and_quad();
  //  auto before  = std::chrono::high_resolution_clock::now();
  //  
  //  pRender->BeginRenderPass(fb);
  //  for(const auto& obj : objects)
  //    DrawInstances(obj, pRender, MODE_VERT_COLOR);
  //  pRender->EndRenderPass(fb);

  //  float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
  //  std::cout << "test_02: " << time << " ms" << std::endl;

  //  std::string name = imgName + "02.bmp";  
  //  SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

  //  std::fill(&fb.data[0], &fb.data[fb.width * fb.height - 1], 0);
  //}

  //// test #03
  //{
  //  auto objects = scn03_pyr_and_cube();
  //  auto before  = std::chrono::high_resolution_clock::now();
  //  
  //  pRender->BeginRenderPass(fb);
  //  for(const auto& obj : objects)
  //    DrawInstances(obj, pRender, MODE_VERT_COLOR);
  //  pRender->EndRenderPass(fb);

  //  float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
  //  std::cout << "test_03: " << time << " ms" << std::endl;

  //  std::string name = imgName + "03.bmp";  
  //  SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

  //  std::fill(&fb.data[0], &fb.data[fb.width * fb.height - 1], 0);
  //}

  //// test #04
  //{
  //  auto objects = scn04_cube(testTexId);
  //  auto before  = std::chrono::high_resolution_clock::now();
  //  
  //  pRender->BeginRenderPass(fb);
  //  for(const auto& obj : objects)
  //    DrawInstances(obj, pRender, MODE_TEXURE_3D);
  //  pRender->EndRenderPass(fb);

  //  float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
  //  std::cout << "test_04: " << time << " ms" << std::endl;

  //  std::string name = imgName + "04.bmp";  
  //  SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

  //  std::fill(&fb.data[0], &fb.data[fb.width * fb.height - 1], 0);
  //}

  //// test #05
  //{
  //  auto objects = scn05_cubes_many(testTexId, mosaicTexId, bricksTexId);
  //  auto before  = std::chrono::high_resolution_clock::now();
  //  
  //  pRender->BeginRenderPass(fb);
  //  for(const auto& obj : objects)
  //    DrawInstances(obj, pRender, MODE_TEXURE_3D);
  //  pRender->EndRenderPass(fb);

  //  float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
  //  std::cout << "test_05: " << time << " ms" << std::endl;

  //  std::string name = imgName + "05.bmp";  
  //  SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

  //  std::fill(&fb.data[0], &fb.data[fb.width * fb.height - 1], 0);
  //}

  //// test #06
  //{
  //  auto objects = scn06_teapot(testTexId, mosaicTexId);
  //  auto before  = std::chrono::high_resolution_clock::now();
  //  
  //  pRender->BeginRenderPass(fb);
  //  for(const auto& obj : objects)
  //    DrawInstances(obj, pRender, MODE_TEXURE_3D);
  //  pRender->EndRenderPass(fb);

  //  float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
  //  std::cout << "test_06: " << time << " ms" << std::endl;

  //  std::string name = imgName + "06.bmp";  
  //  SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

  //  std::fill(&fb.data[0], &fb.data[fb.width * fb.height - 1], 0);
  //}

  // test #07
  {
    auto objects = scn07_teapots_many(testTexId, mosaicTexId);
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_TEXURE_3D);
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
    std::cout << "test_07: " << time << " ms" << std::endl;

    std::string name = imgName + "07.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

    std::fill(&fb.data[0], &fb.data[fb.width * fb.height - 1], 0);
  }

  //// test #08
  //{
  //  auto objects = scn08_terrain(terrainTex);
  //  auto before  = std::chrono::high_resolution_clock::now();
  //  
  //  pRender->BeginRenderPass(fb);
  //  for(const auto& obj : objects)
  //    DrawInstances(obj, pRender, MODE_TEXURE_3D);
  //  pRender->EndRenderPass(fb);

  //  float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
  //  std::cout << "test_08: " << time << " ms" << std::endl;

  //  std::string name = imgName + "08.bmp";  
  //  SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

  //  std::fill(&fb.data[0], &fb.data[fb.width * fb.height - 1], 0);
  //}

  return 0;
}
