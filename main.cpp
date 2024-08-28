#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstring>
#include <cstdint>
#include <chrono>
#include<sys/wait.h>
#include <ctime>

// #include <X11/Xlib.h>
// #include <X11/Xutil.h>
// #include <X11/Xos.h>

#include "Bitmap.h"
#include "lgapi.h"
#include "scene.h"
#include "./shaders/shaders.h"
#include "./parse_obj/OBJparsing.h"
#include "tests/tests.h"

#include <LiteMath.h>

int main(int argc, const char** argv)
{
  // test_all_scenes(false);
  // test_scene(8, false);

  test_intersection();

  return 0;
}
