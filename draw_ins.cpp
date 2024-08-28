
#include "draw_ins.h"

void DrawInstances(const SimpleScene& scn, std::shared_ptr<IRender> pRender, RENDER_MODE a_mode, ShaderContainer *shader_container, bool is_AA)
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

    pso.shaders = shader_container;

    memcpy(pso.worldViewMatrix, scn.instances[instId].worldViewMatrix, sizeof(pso.worldViewMatrix));
    memcpy(pso.projMatrix,      scn.instances[instId].projMatrix,      sizeof(pso.projMatrix));
    pso.mode  = a_mode;
    if(instId < scn.textures.size())     // do we have texture for this instance?
      pso.imgId = scn.textures[instId];  
    else
      pso.imgId = uint32_t(-1); 
      
    if (!is_AA)
    {
      pRender->Draw(pso, geom);
    }         
    else
    {
      
    }
  }
}