#include "sub_buf.h"


// SubPixel 
// getIntersection(const LiteMath::float3 &line_params, const LiteMath::float2 &pixel)
// {
//     SubPixel buf;
//     std::vector<float> polygon(4, 0);

    

//     return buf;
// }

/*
desc:
    vector to line params
inp:
    P0 - start point
    P - direction vector
out:
    line params
*/
LiteMath::float3 getLineParams(const LiteMath::float2 &P0, const LiteMath::float2 &P)
{
    float eps = 10e-6;
    LiteMath::float3 res(P.y + eps, -P.x + eps, -P.y * P0.x + P.x * P0.y + eps);
    return res;
}

bool 
getLeftIntersection(const LiteMath::float3 &line_params, const LiteMath::float2 &pixel, LiteMath::float2 &intersection)
{
    //Ax + By + C = 0
    //y = (-C - Ax) / B
    float x = pixel.x;
    float y = (-line_params[C] - line_params[A] * x) / line_params[B];

    if (y >= pixel.y && y <= pixel.y + 1)
    {
        intersection = {x, y};
        return true;
    }

    return false;
}

bool 
getRightIntersection(const LiteMath::float3 &line_params, const LiteMath::float2 &pixel, LiteMath::float2 &intersection)
{
    //Ax + By + C = 0
    //y = (-C - Ax) / B
    float x = pixel.x + 1;
    float y = (-line_params[C] - line_params[A] * x) / line_params[B];

    if (y >= pixel.y && y <= pixel.y + 1)
    {
        intersection = {x, y};
        return true;
    }

    return false;
}

bool 
getBottomIntersection(const LiteMath::float3 &line_params, const LiteMath::float2 &pixel, LiteMath::float2 &intersection)
{
    //Ax + By + C = 0
    //x = (-C - By) / A
    float y = pixel.y;
    float x = (-line_params[C] - line_params[B] * y) / line_params[A];

    if (x >= pixel.x && x <= pixel.x + 1)
    {
        intersection = {x, y};
        return true;
    }

    return false;
}

bool 
getUpIntersection(const LiteMath::float3 &line_params, const LiteMath::float2 &pixel, LiteMath::float2 &intersection)
{
    //Ax + By + C = 0
    //x = (-C - By) / A
    float y = pixel.y + 1;
    float x = (-line_params[C] - line_params[B] * y) / line_params[A];

    if (x >= pixel.x && x <= pixel.x + 1)
    {
        intersection = {x, y};
        return true;
    }

    return false;
}

SubPixel
calcSubPixel(const LiteMath::float2 &A, const LiteMath::float2 &B, const LiteMath::float2 &C, const LiteMath::float2 &pixel)
{
    constexpr bool (*intersection_funcs[4])(const LiteMath::float3 &, const LiteMath::float2 &, LiteMath::float2 &) = {
        getBottomIntersection, getUpIntersection, getLeftIntersection, getRightIntersection 
    };

    LiteMath::float3 AB_params = getLineParams(A, B - A), BC_params = getLineParams(B, C - B), CA_params = getLineParams(C, A - C);
    LiteMath::float3 params[3] = {AB_params, BC_params, CA_params};

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            LiteMath::float2 intersection;
            bool is_intersected = intersection_funcs[j](params[i], pixel, intersection);
        }
    }
}