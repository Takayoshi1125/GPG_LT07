#pragma once
#include <string>
#include <vector>
class AsoUtility
{

public:

	// ���`���
	static float Lerp(float start, float end, float t);

	// ������؂�
	static std::vector <std::string> Split(std::string& line, char delimiter);

	// ���W�A��(rad)����x(deg)
	static float Rad2Deg(float rad);

	// �x(deg)���烉�W�A��(rad)
	static float Deg2Rad(float deg);

	// 0�`360�x�͈̔͂ɂ����߂�
	static float DegIn360(float deg);

	// 0�`180�x�͈̔͂ɂ����߂�
	static float DegInView(float deg);

	// 0�`2PI�͈̔͂ɂ����߂�
	static float RadIn2PI(float rad);

	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	static int DirNearAroundRad(float from, float to);

	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	static int DirNearAroundDeg(float from, float to);

};

