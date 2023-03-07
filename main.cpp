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

std::shared_ptr<IRender> MakeReferenceImpl();

void DrawInstances(const SimpleScene& scn, std::shared_ptr<IRender> pRender, RENDER_MODE a_mode, unsigned int a_texId = 0)
{
  Geom  geom;
  geom.vpos4f   = scn.vpos4f.data();
  geom.vcol4f   = scn.vcol4f.data();
  geom.vtex2f   = scn.vtex2f.data();
  geom.indices  = scn.indices.data();
  geom.vertNum  = uint32_t(scn.vpos4f.size()/4);
  geom.primsNum = uint32_t(scn.indices.size()/3);

  for(size_t instId = 0; instId < scn.instances.size(); instId++)
  {
    PipelineStateObject pso;
    memcpy(pso.worldViewMatrix, scn.instances[instId].worldViewMatrix, sizeof(pso.worldViewMatrix));
    memcpy(pso.projMatrix,      scn.instances[instId].projMatrix,      sizeof(pso.projMatrix));
    pso.mode  = a_mode;
    pso.imgId = a_texId;
    pRender->Draw(pso, geom);
  }
}


int main(int argc, const char** argv)
{
  const uint32_t WIN_WIDTH  = 512;
  const uint32_t WIN_HEIGHT = 512;

  std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
  Image2D fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());

  std::shared_ptr<IRender> pRender = MakeReferenceImpl();
  std::string imgName = "wref_";
  
  int w, h;
  std::vector<unsigned> pixels = LoadBMP("data/texture1.bmp", &w, &h);
  
  auto testTexId = pRender->AddImage(Image2D(w,h,pixels.data()));

  // test #01
  {
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
  }

  // test #02
  {
    auto objects = scn02_tri_and_quad();
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_VERT_COLOR);
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
    std::cout << "test_02: " << time << " ms" << std::endl;

    std::string name = imgName + "02.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);
  }

  // test #03
  {
    auto objects = scn03_pyr_and_cube();
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_VERT_COLOR);
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
    std::cout << "test_03: " << time << " ms" << std::endl;

    std::string name = imgName + "03.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);
  }

  // test #04
  {
    auto objects = scn04_cube();
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_TEXURE_3D, testTexId);
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;
    std::cout << "test_04: " << time << " ms" << std::endl;

    std::string name = imgName + "04.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);
  }

  return 0;
}
