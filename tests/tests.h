#pragma once

#include "../Bitmap.h"
#include "../lgapi.h"
#include "../scene.h"
#include "../shaders/shaders.h"
#include "../parse_obj/OBJparsing.h"
#include "../external/LiteMath/Image2d.h"
#include "../subBuffer/sub_buf.h"

#include <vector>

void run_test(int id);
float test_scene1(bool is_AA);
float test_scene2(bool is_AA);
float test_scene3(bool is_AA);
float test_scene4(bool is_AA);
float test_scene5(bool is_AA);
float test_scene6(bool is_AA);
float test_scene7(bool is_AA);
float test_scene8(bool is_AA);
float test_scene9(bool is_AA);
float test_scene10(bool is_AA);
void test_all_scenes(bool is_AA);
void test_scene(int id, bool is_AA);
void test_intersection();
void test_full_intersection();


static std::vector<float(*)(bool)> scene_tests = {test_scene1, test_scene2, 
                                test_scene3, test_scene4, test_scene5, 
                                test_scene6, test_scene7, test_scene8, 
                                test_scene9, test_scene10};
