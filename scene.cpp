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

  res.geom.vpos4f = {-0.5,-0.5,0,1, 
                     0,0.5,0,1, 
                     0.5,-0.5,0,1};
  
  res.geom.vcol4f = {1,0,0,1, 
                     0,1,0,1, 
                     0,0,1,1};

  res.geom.vtex2f  = {0,0, 0,0, 0,0};
  res.geom.indices = {0, 1, 2};

  //std::vector<SimpleScene> res_v = {res};
  //res_v[0] = res;
  return {res};
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
  
  res[0].geom.vpos4f  = {0,0.4,0,1, -0.4,-0.4,0,1, 0.4,-0.4,0,1};
  res[0].geom.vcol4f  = {1,1,1,1, 1,1,1,1, 1,1,1,1};
  res[0].geom.vtex2f  = {0,0, 0,0, 0,0};
  res[0].geom.indices = {0, 1, 2};
  
  // quad
  //
  res[1].instances.resize(2);
  {
    memcpy(res[1].instances[0].worldViewMatrix, trans2,   sizeof(trans2));
    memcpy(res[1].instances[0].projMatrix,      identity, sizeof(identity));

    memcpy(res[1].instances[1].worldViewMatrix, trans5,   sizeof(trans2));
    memcpy(res[1].instances[1].projMatrix,      identity, sizeof(identity));
  }

  res[1].geom.vpos4f  = {-0.4, 0.4, 0, 1, 
                          0.4, 0.4, 0, 1, 
                          0.4,-0.4, 0, 1, 
                         -0.4,-0.4, 0, 1};
                    
  res[1].geom.vcol4f  = {1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1};
  res[1].geom.vtex2f  = {0,0, 0,0, 0,0, 0,0};
  res[1].geom.indices = {0, 1, 2, 0, 2, 3};

  return res;
}

GeomStorage make_plane()
{
  GeomStorage geom;
  geom.vpos4f  = {-1,-1,1,1, 1,-1,1,1, 1,-1,-1,1, -1,-1,-1,1};
  geom.vcol4f  = {1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0};
  geom.vtex2f  = {1,0, 0,0, 0,1, 1,1};
  geom.indices = {0, 1, 2, 0, 2, 3};
  return geom;
}

GeomStorage make_pyramid()
{
  GeomStorage geom;
  geom.vpos4f  = {0,1,0,1, -1,-1,1,1, 1,-1,1,1, 0,1,0,1, 1,-1,1,1, 1,-1,-1,1, 0,1,0,1, 1,-1,-1,1, -1,-1,-1,1, 0,1,0,1, -1,-1,-1,1, -1,-1,1,1};
  geom.vcol4f  = {1,0,0,0, 0,1,0,0, 0,0,1,0, 1,0,0,0, 0,0,1,0, 0,1,0,0, 1,0,0,0, 0,1,0,0, 0,0,1,0, 1,0,0,0, 0,0,1,0, 0,1,0,0};
  geom.vtex2f  = {0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0};
  geom.indices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  return geom;
}

GeomStorage make_cube()
{
  GeomStorage geom;
  geom.vpos4f  = {-1,-1,1,1, 1,-1,1,1, 1,1,1,1, -1,1,1,1, -1,-1,-1,1, -1,1,-1,1, 1,1,-1,1, 1,-1,-1,1, -1,1,-1,1, -1,1,1,1, 1,1,1,1, 1,1,-1,1, -1,-1,-1,1, 1,-1,-1,1, 1,-1,1,1, -1,-1,1,1, 1,-1,-1,1, 1,1,-1,1, 1,1,1,1, 1,-1,1,1, -1,-1,-1,1, -1,-1,1,1, -1,1,1,1, -1,1,-1,1};
  geom.vcol4f  = {1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,1,0};
  geom.vtex2f  = {0,0, 1,0, 1,1, 0,1, 1,0, 1,1, 0,1, 0,0, 0,1, 0,0, 1,0, 1,1, 1,1, 0,1, 0,0, 1,0, 1,0, 1,1, 0,1, 0,0, 0,0, 1,0, 1,1, 0,1};
  geom.indices = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23};
  return geom;
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
  
  res[0].geom = make_pyramid();

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
  
  // Note: don't use make_cube() here because we want to paint cube faces in different colors
  //
  res[1].geom.vpos4f  = {1,1,-1,1, -1,1,-1,1, -1,1,1,1, 1,1,1,1, 1,-1,1,1, -1,-1,1,1, -1,-1,-1,1, 1,-1,-1,1, 1,1,1,1, -1,1,1,1, -1,-1,1,1, 1,-1,1,1, 1,-1,-1,1, -1,-1,-1,1, -1,1,-1,1, 1,1,-1,1, -1,1,1,1, -1,1,-1,1, -1,-1,-1,1, -1,-1,1,1, 1,1,-1,1, 1,1,1,1, 1,-1,1,1, 1,-1,-1,1};
  res[1].geom.vcol4f  = {0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 1,0.5,0,0, 1,0.5,0,0, 1,0.5,0,0, 1,0.5,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0, 1,1,0,0, 1,1,0,0, 1,1,0,0, 1,1,0,0, 0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0};
  res[1].geom.vtex2f  = {0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0};
  res[1].geom.indices = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23};

  return res;
}


std::vector<SimpleScene> scn04_cube(uint32_t a_texId)
{
  std::vector<SimpleScene> res;
  res.resize(1);
  
  // pyramid
  //
  float proj1[16] = {2.41421, 0, 0, 0, 
                     0, 2.41421, 0, 0, 
                     0, 0, -1.002, -0.2002, 
                     0, 0, -1, 0 };

  float worldView1[16] = {0.884825, 0.412601, 0.21644, 0, 
                          -0.315381, 0.872324, -0.373612, 0, 
                          -0.342958, 0.262321, 0.90198, -5, 
                          0, 0, 0, 1 };
  
  res[0].instances.resize(1);
  memcpy(res[0].instances[0].worldViewMatrix, worldView1, sizeof(worldView1));
  memcpy(res[0].instances[0].projMatrix,      proj1,      sizeof(proj1));

  res[0].geom     = make_cube();
  res[0].textures = {a_texId};
  return res;
}

std::vector<SimpleScene> scn05_cubes_many(uint32_t a_texId1, uint32_t a_texId2, uint32_t a_texId3)
{
  float projM[16] = {2.41421, 0, 0, 0, 
                     0, 2.41421, 0, 0, 
                     0, 0, -1.002, -0.2002, 
                     0, 0, -1, 0 };
  
  float pyr1World[16] = {1.35946, 0, 0.633927, 0, 
                         0, 1.5, 0, 6.5, 
                         -0.633927, 0, 1.35946, -20, 
                         0, 0, 0, 1 };

  float pyr2World[16] = {0.906308, 0, 0.422618, -7.97356, 
                         0, 1, 0, -1, 
                         -0.422618, 0, 0.906308, -22.9021, 
                         0, 0, 0, 1 };

  float pyr3World[16] = {0.906308, 0, 0.422618, -2.90214, 
                         0, 1, 0, -1, 
                         -0.422618, 0, 0.906308, -12.0264, 
                         0, 0, 0, 1 };

  float pyr4World[16] = {0.906308, 0, 0.422618, 2.90214, 
                         0, 1, 0, -1, 
                         -0.422618, 0, 0.906308, -27.9736, 
                         0, 0, 0, 1 };

  float pyr5World[16] = {0.906308, 0, 0.422618, 7.97356, 
                         0, 1, 0, -1, 
                         -0.422618, 0, 0.906308, -17.0979, 
                         0, 0, 0, 1 };

  std::vector<SimpleScene> res;
  res.resize(3);

  res[0].geom = make_pyramid();
  res[0].instances.resize(5);

  memcpy(res[0].instances[0].worldViewMatrix, pyr1World,  sizeof(pyr1World));
  memcpy(res[0].instances[0].projMatrix,      projM,      sizeof(projM));

  memcpy(res[0].instances[1].worldViewMatrix, pyr2World,  sizeof(pyr2World));
  memcpy(res[0].instances[1].projMatrix,      projM,      sizeof(projM));

  memcpy(res[0].instances[2].worldViewMatrix, pyr3World,  sizeof(pyr3World));
  memcpy(res[0].instances[2].projMatrix,      projM,      sizeof(projM));

  memcpy(res[0].instances[3].worldViewMatrix, pyr4World,  sizeof(pyr4World));
  memcpy(res[0].instances[3].projMatrix,      projM,      sizeof(projM));

  memcpy(res[0].instances[4].worldViewMatrix, pyr5World,  sizeof(pyr5World));
  memcpy(res[0].instances[4].projMatrix,      projM,      sizeof(projM));

  res[1].geom = make_plane();
  res[1].textures = {a_texId1};
  res[1].instances.resize(1);

  float planeWorld[16] = {9.06308, 0, 4.22618, 0, 
                          0, 10, 0, 6, 
                          -4.22618, 0, 9.06308, -20, 
                          0, 0, 0, 1};

  memcpy(res[1].instances[0].worldViewMatrix, planeWorld, sizeof(planeWorld));
  memcpy(res[1].instances[0].projMatrix,      projM,      sizeof(projM));

  res[2].geom     = make_cube();
  res[2].textures = {a_texId3, a_texId2, a_texId2, a_texId2, a_texId2, a_texId2};

  float cube0World[16] = {2.71892, 0, 1.26785, 0, 
                          0, 3, 0, -1, 
                          -1.26785, 0, 2.71892, -20, 
                          0, 0, 0, 1 };

  float cube1World[16] = {1.35946, 0, 0.633927, 0, 
                          0, 1.5, 0, 3.5, 
                          -0.633927, 0, 1.35946, -20, 
                          0, 0, 0, 1};

  float cube2World[16] = {0.906308, 0, 0.422618, -7.97356, 
                          0, 1, 0, -3, 
                          -0.422618, 0, 0.906308, -22.9021, 
                          0, 0, 0, 1 };

  float cube3World[16] = {0.906308, 0, 0.422618, -2.90214, 
                          0, 1, 0, -3, 
                          -0.422618, 0, 0.906308, -12.0264, 
                          0, 0, 0, 1 };

  float cube4World[16] = {0.906308, 0, 0.422618, 2.90214, 
                          0, 1, 0, -3, 
                          -0.422618, 0, 0.906308, -27.9736, 
                          0, 0, 0, 1 };

  float cube5World[16] = {0.906308, 0, 0.422618, 7.97356, 
                          0, 1, 0, -3, 
                          -0.422618, 0, 0.906308, -17.0979, 
                          0, 0, 0, 1 };

  res[2].instances.resize(6);

  memcpy(res[2].instances[0].worldViewMatrix, cube0World, sizeof(cube0World));
  memcpy(res[2].instances[0].projMatrix,      projM,      sizeof(projM));

  memcpy(res[2].instances[1].worldViewMatrix, cube1World, sizeof(cube1World));
  memcpy(res[2].instances[1].projMatrix,      projM,      sizeof(projM));

  memcpy(res[2].instances[2].worldViewMatrix, cube2World, sizeof(cube2World));
  memcpy(res[2].instances[2].projMatrix,      projM,      sizeof(projM));

  memcpy(res[2].instances[3].worldViewMatrix, cube3World, sizeof(cube3World));
  memcpy(res[2].instances[3].projMatrix,      projM,      sizeof(projM));

  memcpy(res[2].instances[4].worldViewMatrix, cube4World, sizeof(cube4World));
  memcpy(res[2].instances[4].projMatrix,      projM,      sizeof(projM));

  memcpy(res[2].instances[5].worldViewMatrix, cube5World, sizeof(cube5World));
  memcpy(res[2].instances[5].projMatrix,      projM,      sizeof(projM));

  return res;
}