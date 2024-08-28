#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <algorithm>

#include "../scene.h"
#include "../external/LiteMath/Image2d.h"

GeomStorage ObjParse(std::string file_path);