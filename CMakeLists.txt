cmake_minimum_required (VERSION 3.8)
project (gapi)

message("Building project")

option(USE_OPENGL "Use reference OpenGL implementation" OFF)

# get rid of annoying MSVC warnings.
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
set (CMAKE_CXX_STANDARD 11)

if(USE_OPENGL)
  add_definitions(-DUSE_OPENGL)
endif()

include_directories(./ external/LiteMath)

if(WIN32)
  link_directories(${ADDITIONAL_LIBRARY_DIRS})
endif()

find_package(OpenMP)

#uncomment this to detect broken memory problems via gcc sanitizers
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds-strict")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

add_executable(app main.cpp 
                       Bitmap.cpp
                       lgapi.cpp
                       scene.cpp
                       shaders/shaders.cpp
                       parse_obj/OBJparsing.cpp
                       tests/tests.cpp
                       draw_ins.cpp
                       subBuffer/sub_buf.cpp
                       external/LiteMath/Image2d.cpp)

set_target_properties(app PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(app LINK_PUBLIC OpenMP::OpenMP_CXX)                 # for your implementation
