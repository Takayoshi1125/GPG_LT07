#include <math.h>
#include "DxLib.h"
#include "AsoUtility.h"
#include "Unit.h"
#include "Camera.h"

Camera::Camera()
{

	// Zバッファを有効にする
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// クリップ距離を設定する
	SetCameraNearFar(0.0f, 1500.0f);

	// ライトの設定
	SetUseLighting(false);

	// 背景色設定
	SetBackgroundColor(0, 139, 139);

}

Camera::~Camera()
{
}

void Camera::Init()
{

	// カメラの初期設定
	mPos = VGet(0.0f, HEIGHT, -DIS_TARGET2CAMERA);

	mAngles = VGet(0.0f, 0.0f, 0.0f);
	mAngles.x = AsoUtility::Deg2Rad(30.0f);

}

void Camera::Update()
{
}

void Camera::SetBeforeDraw(void)
{

	// カメラセット
	SetCameraPositionAndAngle(
		mPos,
		mAngles.x,
		mAngles.y,
		0.0f
	);
	
}

void Camera::Draw()
{

	int LEN_LINE = 1000.0f;

	// XYZ基本軸(グリッド)
	for (int i = 0; i < 21; i++)
	{

		// X軸(赤)
		DrawLine3D(
			VGet(-LEN_LINE, 0.0f, -LEN_LINE + i * 100),
			VGet(LEN_LINE, 0.0f, -LEN_LINE + i * 100),
			0xff0000);

		// Z軸(青)
		DrawLine3D(
			VGet(-LEN_LINE + i * 100, 0.0f, LEN_LINE),
			VGet(-LEN_LINE + i * 100, 0.0f, -LEN_LINE),
			0x0000ff);

	}

	// Y軸(緑)
	DrawLine3D(
		VGet(0.0f, LEN_LINE, 0.0f),
		VGet(0.0f, -LEN_LINE, 0.0f),
		0x00ff00);

	DrawSphere3D({ 0, 0, 0 }, 10, 100, 0x555555, 0x222222, true);

}

void Camera::Release(void)
{
}

VECTOR Camera::GetPos(void)
{
	return mPos;
}

VECTOR Camera::GetAngles(void)
{
	return mAngles;
}

VECTOR Camera::GetTargetPos(void)
{
	return mTargetPos;
}
