
#include "lgapi.h"


struct MyRender : public IRender
{
public:
  ~MyRender() override 
  {
	  depthbuff.clear();
  }
  
  unsigned int AddImage(Image2D a_img) override;

  void BeginRenderPass(Image2D fb) override;
  void Draw(PipelineStateObject a_state, Geom a_geom) override;
  void EndRenderPass(Image2D fb) override;
  float E(const float2&, const float2&, const float2&);
private:
	Image2D fb;
	std::vector<float> depthbuff;
	TextureContainer textures;
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
	this->fb = fb;

	size_t size = fb.height * fb.height;
	this->depthbuff.resize(size);
}

float 
MyRender::E(const float2 &A, const float2 &B, const float2 &P)
{
	return (P.x - A.x) * (B.y - A.y) - (P.y - A.y) * (B.x - A.x);
}

unsigned int MyRender::AddImage(Image2D a_img)
{
	size_t ind = textures.addTexture(a_img);
	
	return ind;
}

void MyRender::Draw(PipelineStateObject a_state, Geom a_geom)
{
	float4x4 worldViewProj = float4x4(a_state.worldViewMatrix) * float4x4(a_state.worldViewMatrix);
	float4 vertex_vec = { 0, 0, 0, 0 };
	
	for (uint64_t tr_num = 0; tr_num < a_geom.primsNum; ++tr_num)
	{
		uint32_t vert_indx[3] = {a_geom.indices[tr_num * 3 + 0], a_geom.indices[tr_num * 3 + 1], a_geom.indices[tr_num * 3 + 2]};
		
	}
}

void MyRender::EndRenderPass(Image2D fb)
{
	
  // In you software implementation this functionm will likely to be empty
  // but you could wait, for example, for some threads if use multi-threading
}