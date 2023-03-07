#pragma once

#include <cstdint>
#include <vector>

struct InstanceInfo
{
  float worldViewMatrix[16]; 
  float projMatrix[16];     
};

struct SimpleScene
{
  std::vector<float>    vpos4f;
  std::vector<float>    vcol4f;
  std::vector<float>    vtex2f;
  std::vector<uint32_t> indices;

  std::vector<InstanceInfo> instances;
};

std::vector<SimpleScene> scn01_colored_triangle();
std::vector<SimpleScene> scn02_tri_and_quad();
std::vector<SimpleScene> scn03_pyr_and_cube();
std::vector<SimpleScene> scn04_cube();
