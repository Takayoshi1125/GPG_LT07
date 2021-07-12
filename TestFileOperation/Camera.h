#pragma once
#include "DxLib.h"

class Camera
{

public:

	// カメラの高さ
	static constexpr float HEIGHT = 300.0f;

	// 注視点からカメラまでの距離
	static constexpr float DIS_TARGET2CAMERA = 500.0f;

	// 注視点からキャラクターまでの距離
	static constexpr float DIS_TARGET2UNIT = 300.0f;

	Camera(void);
	~Camera();

	void Init(void);
	void Update(void);
	void SetBeforeDraw(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetAngles(void);
	VECTOR GetTargetPos(void);

private:

	// カメラの位置
	VECTOR mPos;

	// カメラ角度(rad)
	VECTOR mAngles;

	// 注視点
	VECTOR mTargetPos;

};

