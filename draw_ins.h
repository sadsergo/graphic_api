#pragma once

#include "scene.h"
#include "lgapi.h"

void DrawInstances(const SimpleScene& scn, std::shared_ptr<IRender> pRender, RENDER_MODE a_mode, ShaderContainer *shader_container, bool is_AA);
std::shared_ptr<IRender> MakeReferenceImpl(); ///< reference implementation via OpenGL
std::shared_ptr<IRender> MakeMyImpl();        ///< your implementation