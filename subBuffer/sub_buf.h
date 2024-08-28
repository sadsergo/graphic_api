#pragma once

#include <iostream>
#include <vector>
#include "../external/LiteMath/Image2d.h"

/*
    enum for line equasion Ax + By + C = 0
*/
enum line_params
{
    A = 0,
    B = 1,
    C = 2,
};

/*
    buffer for each pixel, that can be splited by triangle edge
    color_i - color one of triangles
    square_i - pixel's part that belongs to one of triangles
    z_i - depth of one of triangles 
*/
struct SubPixel
{
private:
    uint32_t color1, color2;
    float square1, square2;
    float z1, z2;
public:
    SubPixel() : color1(0), color2(0), square1(0), square2(0), z1(0), z2(0) {}
};

LiteMath::float3 getLineParams(const LiteMath::float2 &P0, const LiteMath::float2 &P);
bool getLeftIntersection(const LiteMath::float3 &line_params, const LiteMath::float2 &pixel, LiteMath::float2 &intersection);
bool getRightIntersection(const LiteMath::float3 &line_params, const LiteMath::float2 &pixel, LiteMath::float2 &intersection);
bool getBottomIntersection(const LiteMath::float3 &line_params, const LiteMath::float2 &pixel, LiteMath::float2 &intersection);
bool getUpIntersection(const LiteMath::float3 &line_params, const LiteMath::float2 &pixel, LiteMath::float2 &intersection);
SubPixel calcSubPixel(const LiteMath::float2 &A, const LiteMath::float2 &B, const LiteMath::float2 &C, const LiteMath::float2 &pixel);