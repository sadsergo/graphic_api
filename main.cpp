#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "Bitmap.h"

int main(int argc, const char** argv)
{
  const uint32_t WIN_WIDTH = 512;
  const uint32_t WIN_HEIGHT = 512;
  std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
 
  for(auto& pixel : pixelData)
    pixel = 0x00FF00FF;
  
  SaveBMP("test.bmp", pixelData.data(), WIN_WIDTH, WIN_HEIGHT);
  
  return 0;
}
