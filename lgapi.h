#pragma once 

enum RENDER_MODE { MODE_FILL_COLOR = 0,
                   MODE_VERT_COLOR = 1,
                   MODE_TEXURE_3D  = 2, };

struct PipelineStateObject
{
  float worldViewMatrix[16]; ///< by rows, i.e. M[0], M[1], M[2], M[3] is the first row of the matrix
  float projMatrix[16];      ///< by rows, i.e. M[0], M[1], M[2], M[3] is the first row of the matrix
  RENDER_MODE mode;
};

enum GEOM_TYPE { GEOM_TRIANGLES = 1, GEOM_QUADS = 2 };

struct Geom
{
  const float*        vpos4f  = nullptr; ///< quads of vertex coordinates for vertex positions x,y,z,w; w is unused
  const float*        vcol4f  = nullptr; ///< quads of vertex color attributes r,g,b,a; a is unused
  const float*        vtex2f  = nullptr; ///< pairs of x and y coordinates
  const unsigned int* indices = nullptr; ///< index buffer of size 3*primsNum for triangle meshes and 4*primsNum for qual meshes

  unsigned int vertNum  = 0;
  unsigned int primsNum = 0;
  GEOM_TYPE    geomType = GEOM_TRIANGLES;
};

struct FrameBuffer
{
  FrameBuffer(){}
  FrameBuffer(unsigned int w, unsigned int h, unsigned int* a_data) : data(a_data), width(w), height(h) {}

  unsigned int* data;   ///< access pixel(x,y) as data[y*width+x]
  unsigned int  width;
  unsigned int  height; 
};

struct IBatchRender
{
  IBatchRender(){}
  virtual ~IBatchRender(){}
  
  virtual void BeginRenderPass(FrameBuffer fb) = 0;
  virtual void Draw(PipelineStateObject a_state, Geom a_geom) = 0;
  virtual void EndRenderPass(FrameBuffer fb) = 0;
};