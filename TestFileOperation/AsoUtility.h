#pragma once
#include <string>
#include <vector>
class AsoUtility
{

public:

	// 線形補間
	static float Lerp(float start, float end, float t);

	// 文字区切り
	static std::vector <std::string> Split(std::string& line, char delimiter);

	// ラジアン(rad)から度(deg)
	static float Rad2Deg(float rad);

	// 度(deg)からラジアン(rad)
	static float Deg2Rad(float deg);

	// 0～360度の範囲におさめる
	static float DegIn360(float deg);

	// 0～180度の範囲におさめる
	static float DegInView(float deg);

	// 0～2PIの範囲におさめる
	static float RadIn2PI(float rad);

	// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
	static int DirNearAroundRad(float from, float to);

	// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
	static int DirNearAroundDeg(float from, float to);

};

