#include "scene.h"
#include <cstring>

std::vector<SimpleScene> scn01_colored_triangle()
{
  SimpleScene res;
  res.instances.resize(1);

  float identity[16] ={1, 0, 0, 0, 
                       0, 1, 0, 0, 
                       0, 0, 1, 0, 
                       0, 0, 0, 1 };

  memcpy(res.instances[0].worldViewMatrix, identity, sizeof(identity));
  memcpy(res.instances[0].projMatrix,      identity, sizeof(identity));

  res.vpos4f  = {-0.5,-0.5,0,1, 
                 0,0.5,0,1, 
                 0.5,-0.5,0,1};
  
  res.vcol4f  = {1,0,0,1, 
                 0,1,0,1, 
                 0,0,1,1};

  res.vtex2f  = {0,0, 0,0, 0,0};
  res.indices = {0, 1, 2};


  std::vector<SimpleScene> res_v(1);
  res_v[0] = res;
  return res_v;
}

std::vector<SimpleScene> scn02_tri_and_quad()
{
  std::vector<SimpleScene> res;
  res.resize(2);

  float identity[16] = {1, 0, 0, 0, 
                        0, 1, 0, 0, 
                        0, 0, 1, 0, 
                        0, 0, 0, 1 };

  float trans1[16] = {0.5, 0, 0, -0.5, 
                      0, 0.5, 0, +0.25, 
                      0, 0, 1, 0, 
                      0, 0, 0, 1};

  float trans2[16] = {1, 0, 0, +0.5, 
                      0, 1, 0, -0.25, 
                      0, 0, 1, 0, 
                      0, 0, 0, 1};                     

  float trans3[16] = {0.5, 0, 0, -0.5, 
                      0, 0.5, 0, -0.25, 
                      0, 0, 1, 0, 
                      0, 0, 0, 1};

  float trans4[16] = {0.5, 0, 0, -0.5, 
                      0, 0.5, 0, -0.75, 
                      0, 0, 1, 0, 
                      0, 0, 0, 1};
  
  float trans5[16] = {0.5, 0, 0, +0.5, 
                      0, 0.5, 0, +0.5, 
                      0, 0, 1, 0, 
                      0, 0, 0, 1};            

  // triangle
  //
  res[0].instances.resize(3);
  {
    memcpy(res[0].instances[0].worldViewMatrix, trans1,   sizeof(trans1));
    memcpy(res[0].instances[0].projMatrix,      identity, sizeof(identity));
  
    memcpy(res[0].instances[1].worldViewMatrix, trans3,   sizeof(trans1));
    memcpy(res[0].instances[1].projMatrix,      identity, sizeof(identity));

    memcpy(res[0].instances[2].worldViewMatrix, trans4,   sizeof(trans1));
    memcpy(res[0].instances[2].projMatrix,      identity, sizeof(identity));
  }
  
  res[0].vpos4f  = {0,0.4,0,1, -0.4,-0.4,0,1, 0.4,-0.4,0,1};
  res[0].vcol4f  = {1,1,1,1, 1,1,1,1, 1,1,1,1};
  res[0].vtex2f  = {0,0, 0,0, 0,0};
  res[0].indices = {0, 1, 2};
  
  // quad
  //
  res[1].instances.resize(2);
  {
    memcpy(res[1].instances[0].worldViewMatrix, trans2,   sizeof(trans2));
    memcpy(res[1].instances[0].projMatrix,      identity, sizeof(identity));

    memcpy(res[1].instances[1].worldViewMatrix, trans5,   sizeof(trans2));
    memcpy(res[1].instances[1].projMatrix,      identity, sizeof(identity));
  }

  res[1].vpos4f  = {-0.4, 0.4, 0, 1, 
                     0.4, 0.4, 0, 1, 
                     0.4,-0.4, 0, 1, 
                    -0.4,-0.4, 0, 1};
                    
  res[1].vcol4f  = {1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1};
  res[1].vtex2f  = {0,0, 0,0, 0,0, 0,0};
  res[1].indices = {0, 1, 2, 0, 2, 3};

  return res;
}

std::vector<SimpleScene> scn03_pyr_and_cube()
{
  std::vector<SimpleScene> res;
  res.resize(2);
  
  // pyramid
  //
  float proj1[16] = {2.41421, 0, 0, 0, 
                     0, 2.41421, 0, 0, 
                     0, 0, -1.002, -0.2002, 
                     0, 0, -1, 0 };

  float worldView1[16] = {0.866025, 0, 0.5, -1.5, 
                          0, 1, 0, 0, 
                          -0.5, 0, 0.866025, -6, 
                          0, 0, 0, 1};
  
  res[0].instances.resize(1);
  memcpy(res[0].instances[0].worldViewMatrix, worldView1, sizeof(worldView1));
  memcpy(res[0].instances[0].projMatrix,      proj1, sizeof(proj1));

  res[0].vpos4f  = {0,1,0,1, -1,-1,1,1, 1,-1,1,1, 0,1,0,1, 1,-1,1,1, 1,-1,-1,1, 0,1,0,1, 1,-1,-1,1, -1,-1,-1,1, 0,1,0,1, -1,-1,-1,1, -1,-1,1,1};
  res[0].vcol4f  = {1,0,0,0, 0,1,0,0, 0,0,1,0, 1,0,0,0, 0,0,1,0, 0,1,0,0, 1,0,0,0, 0,1,0,0, 0,0,1,0, 1,0,0,0, 0,0,1,0, 0,1,0,0};
  res[0].vtex2f  = {0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0};
  res[0].indices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

  // cube
  //
  float proj2[16] = {2.41421, 0, 0, 0, 
                     0, 2.41421, 0, 0, 
                     0, 0, -1.002, -0.2002, 
                     0, 0, -1, 0 };

  float worldView2[16] = {0.761858, -0.323205, 0.561347, 1.5, 
                          0.561347, 0.761858, -0.323205, 0, 
                          -0.323205, 0.561347, 0.761858, -7, 
                          0, 0, 0, 1 };
  

  res[1].instances.resize(1);
  memcpy(res[1].instances[0].worldViewMatrix, worldView2, sizeof(worldView2));
  memcpy(res[1].instances[0].projMatrix,      proj2, sizeof(proj2));

  res[1].vpos4f  = {1,1,-1,1, -1,1,-1,1, -1,1,1,1, 1,1,1,1, 1,-1,1,1, -1,-1,1,1, -1,-1,-1,1, 1,-1,-1,1, 1,1,1,1, -1,1,1,1, -1,-1,1,1, 1,-1,1,1, 1,-1,-1,1, -1,-1,-1,1, -1,1,-1,1, 1,1,-1,1, -1,1,1,1, -1,1,-1,1, -1,-1,-1,1, -1,-1,1,1, 1,1,-1,1, 1,1,1,1, 1,-1,1,1, 1,-1,-1,1};
  res[1].vcol4f  = {0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 1,0.5,0,0, 1,0.5,0,0, 1,0.5,0,0, 1,0.5,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0, 1,1,0,0, 1,1,0,0, 1,1,0,0, 1,1,0,0, 0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0};
  res[1].vtex2f  = {0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0};
  res[1].indices = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23};

  return res;
}