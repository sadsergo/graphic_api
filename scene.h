#pragma once

#include <cstdint>
#include <vector>

struct SimpleScene
{
  float worldViewMatrix[16]; 
  float projMatrix[16];      
  std::vector<float> vpos4f;
  std::vector<float> vcol4f;
  std::vector<float> vtex2f;
  std::vector<uint32_t> indices;
};

SimpleScene CreateSimpleTriangle();