
#include "lgapi.h"


struct MyRender : public IRender
{
public:
	~MyRender() override 
	{
		depthbuff.clear();
	}
  
	size_t AddImage(Image2D a_img) override;

	void BeginRenderPass(Image2D fb) override;
	void Draw(PipelineStateObject a_state, Geom a_geom) override;
	void EndRenderPass(Image2D fb) override;
	float E(const float3&, const float3&, const float3&);
	float E(const float3&, const float3&);
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
	std::fill(&depthbuff.data()[0], &depthbuff.data()[size - 1], 0);
}

float 
MyRender::E(const float3 &A, const float3 &B, const float3 &P)
{
	return (P.x - A.x) * (B.y - A.y) - (P.y - A.y) * (B.x - A.x);
}

float 
MyRender::E(const float3 &V, const float3 &VP)
{
	return (V.x * VP.y - V.y * VP.x);
}

size_t MyRender::AddImage(Image2D a_img)
{
	size_t ind = textures.addTexture(a_img);
	
	return ind;
}

void MyRender::Draw(PipelineStateObject a_state, Geom a_geom)
{
	float4x4 worldViewProj = float4x4(a_state.worldViewMatrix) * float4x4(a_state.worldViewMatrix);
	
	for (uint64_t tr_num = 0; tr_num < a_geom.primsNum; ++tr_num)
	{
		uint32_t vert_indx[3] = {a_geom.indices[tr_num * 3 + 0], a_geom.indices[tr_num * 3 + 1], a_geom.indices[tr_num * 3 + 2]};
		float4 vertex_vec = { 0, 0, 0, 0 };

		float p[3 * 4] = { 0 };
		float col[3 * 4] = { 0 };
		float uv[3 * 2] = { 0 };

		for (int ind_ver = 0; ind_ver < 3; ++ind_ver)
		{
			float4 vpos4f_i = { 
				a_geom.vpos4f[4 * vert_indx[ind_ver]],
				a_geom.vpos4f[4 * vert_indx[ind_ver] + 1],
				a_geom.vpos4f[4 * vert_indx[ind_ver] + 2],
				a_geom.vpos4f[4 * vert_indx[ind_ver] + 3], 
			};

			vertex_vec = worldViewProj * vpos4f_i;

			std::cout << a_geom.vpos4f[4 * vert_indx[ind_ver]] << " " << a_geom.vpos4f[4 * vert_indx[ind_ver] + 1] << " " << a_geom.vpos4f[4 * vert_indx[ind_ver] + 2] << " " << a_geom.vpos4f[4 * vert_indx[ind_ver] + 3] << std::endl;
			
			//float w = vertex_vec.w;
			//vertex_vec /= w;
			//
			//p[4 * ind_ver + 0] = vertex_vec.x;
			//p[4 * ind_ver + 1] = vertex_vec.y;
			//p[4 * ind_ver + 2] = vertex_vec.z;
			//p[4 * ind_ver + 3] = vertex_vec.w;

			//for (int i = 0; i < 2; i++) {
			//	p[4 * ind_ver + i] = (p[4 * ind_ver + i] * 0.5f + 0.5f);
			//}

			//p[4 * ind_ver + 0] = p[4 * ind_ver + 0] * (float)fb.width - 0.5f;
			//p[4 * ind_ver + 1] = p[4 * ind_ver + 1] * (float)fb.height - 0.5f;

			//p[4 * ind_ver + 2] = 1.f / w;

			///*if (a_state.imgId != uint32_t(-1)) {
			//	uv[2 * ind_ver + 0] = a_geom.vtex2f[2 * vert_indx[ind_ver]] / w;
			//	uv[2 * ind_ver + 1] = a_geom.vtex2f[2 * vert_indx[ind_ver] + 1] / w;
			//}
			//else {*/
			//	col[4 * ind_ver + 0] = a_geom.vcol4f[4 * vert_indx[ind_ver]] / w;
			//	col[4 * ind_ver + 1] = a_geom.vcol4f[4 * vert_indx[ind_ver] + 1] / w;
			//	col[4 * ind_ver + 2] = a_geom.vcol4f[4 * vert_indx[ind_ver] + 2] / w;
			//	col[4 * ind_ver + 3] = a_geom.vcol4f[4 * vert_indx[ind_ver] + 3] / w;
			////}
		}

		//float3 A(p[0 * 4 + 0], p[0 * 4 + 1], p[0 * 4 + 2]), B(p[1 * 4 + 0], p[1 * 4 + 1], p[1 * 4 + 2]), C(p[2 * 4 + 0], p[2 * 4 + 1], p[2 * 4 + 2]);
		//
		////	Triangle boundary on 2D plane
		//float xmin = std::min(A.x, std::min(B.x, C.x)), xmax = std::max(A.x, std::max(B.x, C.x));
		//float ymin = std::min(A.y, std::min(B.y, C.y)), ymax = std::max(A.y, std::max(B.y, C.y));

		////	Triangle boundary on user's monitor
		//int x0 = clamp((int32_t)xmin, 0, (int32_t)fb.width), y0 = clamp((int32_t)ymin, 0, (int32_t)fb.height);
		//int x1 = clamp((int32_t)xmax, 0, (int32_t)fb.width), y1 = clamp((int32_t)ymax, 0, (int32_t)fb.height);
		//float e = E(A, B, C);
		////std::cout << e << std::endl;
		//for (int x = x0; x <= x1 && x < fb.width; ++x)
		//{
		//	for (int y = y0; y <= y1 && y < fb.height; ++y)
		//	{
		//		float3 Point((float)x, float(y), 0.f);
		//		float w0 = E(B - A, Point - A) / e, w1 = E(C - B, Point - B) / e, w2 = E(A - C, Point - C) / e;
		//		
		//		if (w0 > 0 && w1 > 0 && w2 > 0 || w0 < 0 && w1 < 0 && w2 < 0)
		//		{
		//			w0 = abs(w0);
		//			w1 = abs(w1);
		//			w2 = abs(w2);

		//			float cur_w = C.z * w0 + A.z * w1 + B.z * w2;

		//			if (1 / cur_w < 1 / depthbuff[fb.width * y + x])
		//			{
		//				depthbuff[fb.width * y + x] = cur_w;

		//				float3 color_vec;

		//				color_vec.x = (col[2 * 4 + 0] * w0 + col[0 * 4 + 0] * w1 + col[1 * 4 + 0] * w2) / cur_w * 255;
		//				color_vec.y = (col[2 * 4 + 1] * w0 + col[0 * 4 + 1] * w1 + col[1 * 4 + 1] * w2) / cur_w * 255;
		//				color_vec.z = (col[2 * 4 + 2] * w0 + col[0 * 4 + 2] * w1 + col[1 * 4 + 2] * w2) / cur_w * 255;

		//				uint32_t color = ((unsigned char)(color_vec.x) << 16) + ((unsigned char)(color_vec.y) << 8) + ((unsigned char)(color_vec.z));
		//				fb.data[fb.width * y + x] = color;
		//			}
		//		}
		//	}
		//}
	}
}

void MyRender::EndRenderPass(Image2D fb)
{
	size_t size = fb.height * fb.height;
	std::fill(&depthbuff.data()[0], &depthbuff.data()[size - 1], 0);
  // In you software implementation this functionm will likely to be empty
  // but you could wait, for example, for some threads if use multi-threading
}