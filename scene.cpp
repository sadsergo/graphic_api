#include "scene.h"
#include <cstring>

SimpleScene CreateSimpleTriangle()
{
  SimpleScene res;

  float identity[16] ={1, 0, 0, 0, 
                       0, 1, 0, 0, 
                       0, 0, 1, 0, 
                       0, 0, 0, 1 };

  memcpy(res.worldViewMatrix, identity, sizeof(res.worldViewMatrix));
  memcpy(res.projMatrix,      identity, sizeof(res.projMatrix));

  res.vpos4f  = {-0.5,-0.5,0,1, 
                 0,0.5,0,1, 
                 0.5,-0.5,0,1};
  
  res.vcol4f  = {1,0,0,1, 
                 0,1,0,1, 
                 0,0,1,1};

  res.vtex2f  = {0,0, 0,0, 0,0};
  res.indices = {0, 1, 2};

  return res;
}