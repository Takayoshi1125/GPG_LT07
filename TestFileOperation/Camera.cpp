#include <math.h>
#include "DxLib.h"
#include "AsoUtility.h"
#include "Unit.h"
#include "Camera.h"

Camera::Camera()
{

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	// �o�b�N�J�����O��L���ɂ���
	SetUseBackCulling(true);

	// �N���b�v������ݒ肷��
	SetCameraNearFar(0.0f, 1500.0f);

	// ���C�g�̐ݒ�
	SetUseLighting(false);

	// �w�i�F�ݒ�
	SetBackgroundColor(0, 139, 139);

}

Camera::~Camera()
{
}

void Camera::Init()
{

	// �J�����̏����ݒ�
	mPos = VGet(0.0f, HEIGHT, -DIS_TARGET2CAMERA);

	mAngles = VGet(0.0f, 0.0f, 0.0f);
	mAngles.x = AsoUtility::Deg2Rad(30.0f);

}

void Camera::Update()
{
}

void Camera::SetBeforeDraw(void)
{

	// �J�����Z�b�g
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

	// XYZ��{��(�O���b�h)
	for (int i = 0; i < 21; i++)
	{

		// X��(��)
		DrawLine3D(
			VGet(-LEN_LINE, 0.0f, -LEN_LINE + i * 100),
			VGet(LEN_LINE, 0.0f, -LEN_LINE + i * 100),
			0xff0000);

		// Z��(��)
		DrawLine3D(
			VGet(-LEN_LINE + i * 100, 0.0f, LEN_LINE),
			VGet(-LEN_LINE + i * 100, 0.0f, -LEN_LINE),
			0x0000ff);

	}

	// Y��(��)
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
