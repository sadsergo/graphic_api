#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstring>
#include <cstdint>

#include "Bitmap.h"
#include "lgapi.h"
#include "scene.h"

std::shared_ptr<IBatchRender> MakeReferenceImpl();

int main(int argc, const char** argv)
{
  const uint32_t WIN_WIDTH = 512;
  const uint32_t WIN_HEIGHT = 512;
  std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
 
  for(auto& pixel : pixelData)
    pixel = 0x00FF00FF;

  std::shared_ptr<IBatchRender> pRender = MakeReferenceImpl();

  SimpleScene scn = CreateSimpleTriangle();

  PipelineStateObject pso;
  memcpy(pso.worldViewMatrix, scn.worldViewMatrix, sizeof(pso.worldViewMatrix));
  memcpy(pso.projMatrix,      scn.projMatrix,      sizeof(pso.projMatrix));
  pso.mode = MODE_VERT_COLOR;

  Geom  geom;
  geom.vpos4f   = scn.vpos4f.data();
  geom.vcol4f   = scn.vcol4f.data();
  geom.vtex2f   = scn.vtex2f.data();
  geom.indices  = scn.indices.data();
  geom.vertNum  = uint32_t(scn.vpos4f.size()/4);
  geom.primsNum = uint32_t(scn.indices.size()/3);

  FrameBuffer fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());

  pRender->Render(pso, geom, fb);

  SaveBMP("test.bmp", pixelData.data(), WIN_WIDTH, WIN_HEIGHT);
  
  return 0;
}
