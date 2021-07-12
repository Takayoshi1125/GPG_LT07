#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "DxLib.h"
#include "AsoUtility.h"

float AsoUtility::Lerp(float start, float end, float t)
{
	// 線形補間
	float ret = start;
	ret += t * (end - start);
    return ret;
}

std::vector<std::string> AsoUtility::Split(std::string& line, char delimiter)
{
    std::istringstream stream(line);
    std::string field;
    std::vector<std::string> result;

    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }

    return result;
}


float AsoUtility::Rad2Deg(float rad)
{
    return rad * (180.0f / DX_PI_F);
}

float AsoUtility::Deg2Rad(float deg)
{
    return deg * (DX_PI_F / 180.0f);
}

float AsoUtility::DegIn360(float deg)
{
    float mod = fmodf(deg, 360.0f);
    if (mod < 0.0f)
    {
        mod += 360.0f;
    }
    return mod;
}

float AsoUtility::DegInView(float deg)
{
    float ret = DegIn360(deg);
    if (ret <= 180.0f)
    {
        return ret;
    }
    return 360.0f - ret;
}

float AsoUtility::RadIn2PI(float rad)
{
    float mod = fmodf(rad, DX_TWO_PI_F);
    if (mod < 0.0f)
    {
        mod += DX_TWO_PI_F;
    }
    return mod;
}

int AsoUtility::DirNearAroundRad(float from, float to)
{

    float ret = 1.0f;

    float diff = to - from;

    if (diff >= 0.0f)
    {

        // 比較元よりも時計回りに位置する

        if (diff > DX_PI_F)
        {
            // でも、180度以上離れているので、反時計回りの方が近い
            ret = -1.0f;
        }
        else
        {
            // 時計回り
            ret = 1.0f;
        }

    }
    else
    {

        // 比較元よりも反時計回りに位置する

        if (diff < -DX_PI_F)
        {
            // でも、180度以上離れているので、時計回りの方が近い
            ret = 1.0f;
        }
        else
        {
            // 反時計回り
            ret = -1.0f;
        }

    }

    return ret;

}

int AsoUtility::DirNearAroundDeg(float from, float to)
{

    float ret = 1.0f;

    float diff = to - from;

    if (diff >= 0.0f)
    {

        // 比較元よりも時計回りに位置する

        if (diff > 180.0f)
        {
            // でも、180度以上離れているので、反時計回りの方が近い
            ret = -1.0f;
        }
        else
        {
            // 時計回り
            ret = 1.0f;
        }

    }
    else
    {

        // 比較元よりも反時計回りに位置する

        if (diff < -180.0f)
        {
            // でも、180度以上離れているので、時計回りの方が近い
            ret = 1.0f;
        }
        else
        {
            // 反時計回り
            ret = -1.0f;
        }

    }

    return ret;

}

