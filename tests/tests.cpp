
#include "tests.h"
#include "../draw_ins.h"
#include <iostream>
#include <chrono>

static uint32_t WIN_WIDTH  = 1024;
static uint32_t WIN_HEIGHT = 1024;
static std::string output = "output/";

float
test_scene1(bool is_AA)
{
    std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
    Image2D fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());
    size_t img_size = WIN_HEIGHT * WIN_WIDTH;

    ShaderContainer *shader_container = new ShaderContainer();

    shader_container->vertexProcessing = vertexProcessing;
    shader_container->colorShader = colorShader;
    shader_container->textureShader = textureShader;
    
    std::shared_ptr<IRender> pRender = MakeMyImpl();
    std::string imgName = "zout_";

    std::string output_path = "output/";
    
    uint32_t testTexId, mosaicTexId, bricksTexId, terrainTex, statueTexId;

    auto objects = scn01_colored_triangle(); 
    auto before  = std::chrono::high_resolution_clock::now();  

    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_VERT_COLOR, shader_container, is_AA);
    pRender->EndRenderPass(fb);

    float time = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f) / 10;

    std::string name = output_path + imgName + "01" + ".bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

    return time;
}

float
test_scene2(bool is_AA)
{
    std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
    Image2D fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());
    size_t img_size = WIN_HEIGHT * WIN_WIDTH;

    ShaderContainer *shader_container = new ShaderContainer();

    shader_container->vertexProcessing = vertexProcessing;
    shader_container->colorShader = colorShader;
    shader_container->textureShader = textureShader;
    
    std::shared_ptr<IRender> pRender = MakeMyImpl();
    std::string imgName = "zout_";

    std::string output_path = "output/";
    
    uint32_t testTexId, mosaicTexId, bricksTexId, terrainTex, statueTexId;

    auto objects = scn02_tri_and_quad();
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_VERT_COLOR, shader_container, is_AA);
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;

    std::string name = output_path + imgName + "02.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

    return time;
}

float
test_scene3(bool is_AA)
{
    std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
    Image2D fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());
    size_t img_size = WIN_HEIGHT * WIN_WIDTH;

    ShaderContainer *shader_container = new ShaderContainer();

    shader_container->vertexProcessing = vertexProcessing;
    shader_container->colorShader = colorShader;
    shader_container->textureShader = textureShader;
    
    std::shared_ptr<IRender> pRender = MakeMyImpl();
    std::string imgName = "zout_";

    std::string output_path = "output/";
    
    uint32_t testTexId, mosaicTexId, bricksTexId, terrainTex, statueTexId;

    auto objects = scn03_pyr_and_cube();
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_VERT_COLOR, shader_container, is_AA);
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;

    std::string name = output_path + imgName + "03.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

    return time;
}

float
test_scene4(bool is_AA)
{
    std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
    Image2D fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());
    size_t img_size = WIN_HEIGHT * WIN_WIDTH;

    ShaderContainer *shader_container = new ShaderContainer();

    shader_container->vertexProcessing = vertexProcessing;
    shader_container->colorShader = colorShader;
    shader_container->textureShader = textureShader;
    
    std::shared_ptr<IRender> pRender = MakeMyImpl();
    std::string imgName = "zout_";

    std::string output_path = "output/";
    
    uint32_t testTexId, mosaicTexId, bricksTexId, terrainTex, statueTexId;

    int w, h;
    std::vector<unsigned> pixels;

    pixels      = LoadBMP("./data/texture1.bmp", &w, &h);
    Image2D A = Image2D(w,h,pixels.data());
    testTexId   = pRender->AddImage(A);

    auto objects = scn04_cube(testTexId);
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_TEXURE_3D, shader_container, is_AA);
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;

    std::string name = output_path + imgName + "04.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

    return time;
}

float
test_scene5(bool is_AA)
{
    return 0;
}

float
test_scene6(bool is_AA)
{
    std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
    Image2D fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());
    size_t img_size = WIN_HEIGHT * WIN_WIDTH;

    ShaderContainer *shader_container = new ShaderContainer();

    shader_container->vertexProcessing = vertexProcessing;
    shader_container->colorShader = colorShader;
    shader_container->textureShader = textureShader;
    
    std::shared_ptr<IRender> pRender = MakeMyImpl();
    std::string imgName = "zout_";

    std::string output_path = "output/";
    
    uint32_t testTexId, mosaicTexId, bricksTexId, terrainTex, statueTexId;

    int w, h;
    std::vector<unsigned> pixels;
    pixels      = LoadBMP("./data/texture1.bmp", &w, &h);
    Image2D A = Image2D(w,h,pixels.data());
    testTexId   = pRender->AddImage(A);
    std::vector<unsigned> pixels1;
    pixels1      = LoadBMP("./data/mosaic.bmp", &w, &h);
    Image2D B = Image2D(w,h,pixels1.data());
    mosaicTexId = pRender->AddImage(B);

    auto objects = scn06_teapot(testTexId, mosaicTexId);
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
    {
      DrawInstances(obj, pRender, MODE_TEXURE_3D, shader_container, is_AA);
    }
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;

    std::string name = output_path + imgName + "06.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

    return time;
}

float
test_scene7(bool is_AA)
{
    std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
    Image2D fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());
    size_t img_size = WIN_HEIGHT * WIN_WIDTH;

    ShaderContainer *shader_container = new ShaderContainer();

    shader_container->vertexProcessing = vertexProcessing;
    shader_container->colorShader = colorShader;
    shader_container->textureShader = textureShader;
    
    std::shared_ptr<IRender> pRender = MakeMyImpl();
    std::string imgName = "zout_";

    std::string output_path = "output/";
    
    uint32_t testTexId, mosaicTexId, bricksTexId, terrainTex, statueTexId;

    int w, h;
    std::vector<unsigned> pixels;
    pixels      = LoadBMP("./data/texture1.bmp", &w, &h);
    Image2D A = Image2D(w,h,pixels.data());
    testTexId   = pRender->AddImage(A);
    std::vector<unsigned> pixels1;
    pixels1      = LoadBMP("./data/mosaic.bmp", &w, &h);
    Image2D B = Image2D(w,h,pixels1.data());
    mosaicTexId = pRender->AddImage(B);

    auto objects = scn07_teapots_many(testTexId, mosaicTexId);
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_TEXURE_3D, shader_container, is_AA);
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;

    std::string name = output_path + imgName + "07.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

    return time;
}

float
test_scene8(bool is_AA)
{
    std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
    Image2D fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());
    size_t img_size = WIN_HEIGHT * WIN_WIDTH;

    ShaderContainer *shader_container = new ShaderContainer();

    shader_container->vertexProcessing = vertexProcessing;
    shader_container->colorShader = colorShader;
    shader_container->textureShader = textureShader;
    
    std::shared_ptr<IRender> pRender = MakeMyImpl();
    std::string imgName = "zout_";

    std::string output_path = "output/";
    
    uint32_t testTexId, mosaicTexId, bricksTexId, terrainTex, statueTexId;

    int w, h;
    std::vector<unsigned> pixels;
    pixels      = LoadBMP("./data/terrain.bmp", &w, &h);
    Image2D D = Image2D(w,h,pixels.data());
    terrainTex  = pRender->AddImage(D);

    auto objects = scn08_terrain(terrainTex);
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for(const auto& obj : objects)
      DrawInstances(obj, pRender, MODE_TEXURE_3D, shader_container, is_AA);
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;

    std::string name = output_path + imgName + "08.bmp";  
    SaveBMP(name.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

    return time;
}

float
test_scene9(bool is_AA)
{
    return 0;
}

float
test_scene10(bool is_AA)
{
    std::vector<uint32_t> pixelData(WIN_WIDTH*WIN_HEIGHT);
    Image2D fb(WIN_WIDTH, WIN_HEIGHT, pixelData.data());
    size_t img_size = WIN_HEIGHT * WIN_WIDTH;

    ShaderContainer *shader_container = new ShaderContainer();

    shader_container->vertexProcessing = vertexProcessing;
    shader_container->colorShader = colorShader;
    shader_container->textureShader = textureShader;
    
    std::shared_ptr<IRender> pRender = MakeMyImpl();
    std::string imgName = "zout_";

    std::string output_path = "output/";
    
    uint32_t testTexId, mosaicTexId, bricksTexId, terrainTex, statueTexId;

    int w, h;
    std::vector<unsigned> pixels;
    pixels = LoadBMP("./data/Default-OBJ_BaseColor.bmp", &w, &h);
    Image2D E = Image2D(w,h,pixels.data());
    statueTexId = pRender->AddImage(E);

    LiteMath::float4x4 perspProj = LiteMath::perspectiveMatrix(45.f, (double)fb.width / (double)fb.height, 0.1, 90);

    float cameraCoords[3] = {0, -5, 30};
    float targetCoords[3] = {0, 0, 0}, upCoords[3] = {0, 1, 0};

    LiteMath::float3 eye(cameraCoords), center(targetCoords), up(upCoords);
    auto viewMat = LiteMath::lookAt(eye, center, up);
    LiteMath::float4x4 worldView = viewMat;

    auto objects = scn10_statue(statueTexId, LiteMath::transpose(perspProj), LiteMath::transpose(worldView));
    
    auto before  = std::chrono::high_resolution_clock::now();
    
    pRender->BeginRenderPass(fb);
    for (auto &obj: objects)
    {
      DrawInstances(obj, pRender, MODE_TEXURE_3D, shader_container, is_AA);
    }
    pRender->EndRenderPass(fb);

    float time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - before).count()/1000.f;

    std::string name = output_path + imgName + "10.bmp";
    std::string savePath = name;
    SaveBMP(savePath.c_str(), pixelData.data(), WIN_WIDTH, WIN_HEIGHT);

    return time;
}

void
test_all_scenes(bool is_AA)
{
    std::cout << "TEST ALL SCENES" << std::endl;

    for (int i = 0; i < scene_tests.size(); ++i)
    {
        std::cout << "SCENE_" << i + 1 << ": " << scene_tests[i](is_AA) << " ms" << std::endl;
    }
}

void 
test_scene(int id, bool is_AA)
{
    if (id > scene_tests.size())
    {
        std::cout << "No scene with that id is found" << std::endl;
        return;
    }

    std::cout << "TEST SCENE_" << id << ": " << scene_tests[id - 1](is_AA) << " ms" << std::endl;
}

void 
test_intersection()
{
  LiteMath::float2 pixel(2, 3);
  LiteMath::float2 P0(0, 0), P(2.5, 3.1);

  auto params = getLineParams(P0, P);

  constexpr bool (*intersection_funcs[4])(const LiteMath::float3 &, const LiteMath::float2 &, LiteMath::float2 &) = {
    getBottomIntersection, getUpIntersection, getLeftIntersection, getRightIntersection 
  };

  for (int i = 0; i < 4; ++i)
  {
    LiteMath::float2 intersection;
    bool ans = intersection_funcs[i](params, pixel, intersection);

    if (ans)
    {
      std::cout << intersection.x << " " << intersection.y << std::endl;
    }
  }
}

