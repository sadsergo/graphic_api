#include "lgapi.h"
#include <memory>

struct MyRender : public IRender
{
  ~MyRender() override { }
  
  unsigned int AddImage(Image2D a_img) override;

  void BeginRenderPass(Image2D fb) override;
  void Draw(PipelineStateObject a_state, Geom a_geom) override;
  void EndRenderPass(Image2D fb) override;
};

std::shared_ptr<IRender> MakeMyImpl() 
{ 
  return std::make_shared<MyRender>(); 
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MyRender::BeginRenderPass(Image2D fb)
{ 
  // In you software implementation you will likely to clear fb here unless you don't plan to use some specific internal framebuffer format and copy final image to fb at the end 
  // so, you could clear fb, than save it and later just directly draw to it. 

}

unsigned int MyRender::AddImage(Image2D a_img)
{
  return 0;
}

void MyRender::Draw(PipelineStateObject a_state, Geom a_geom)
{
 
}

void MyRender::EndRenderPass(Image2D fb)
{
  // In you software implementation this functionm will likely to be empty
  // but you could wait, for example, for some threads if use multi-threading
}