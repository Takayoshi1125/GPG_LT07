#include <fstream>
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Unit3D.h"

Unit3D::Unit3D(SceneManager* manager)
{
	mSceneManager = manager;
	mAnimState = ANIM_STATE::NONE;
}

void Unit3D::Init(void)
{

	mModel = MV1LoadModel("Model/Unit.mv1");
	mPos = { 0.0f, 0.0f, 0.0f };
	mAngles = { 0.0f, AsoUtility::Rad2Deg(180), 0.0f };
	mAnglesLocal = { 0.0f, AsoUtility::Deg2Rad(180.0f), 0.0f };

	MV1SetPosition(mModel, mPos);

	ChangeAnim(ANIM_STATE::IDLE);

}

void Unit3D::Update(void)
{

	// 経過時間の取得
	float deltaTime = mSceneManager->GetDeltaTime();

	bool isHitKey = false;

	// 移動量
	float movePow = 2.0f;

	// 左
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		mPos.x -= movePow;
		mAngles.y = AsoUtility::Deg2Rad(-90);
		isHitKey = true;
	}

	// 右
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		mPos.x += movePow;
		mAngles.y = AsoUtility::Deg2Rad(90);
		isHitKey = true;
	}

	// 奥
	if (CheckHitKey(KEY_INPUT_UP))
	{
		mPos.z += movePow;
		mAngles.y = AsoUtility::Deg2Rad(0);
		isHitKey = true;
	}

	// 手前
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		mPos.z -= movePow;
		mAngles.y = AsoUtility::Deg2Rad(180);
		isHitKey = true;
	}

	if (isHitKey)
	{
		ChangeAnim(ANIM_STATE::WALK);
	}
	else
	{
		ChangeAnim(ANIM_STATE::IDLE);
	}

	// 新しいアニメーション再生時間をセット
	mStepAnim += (deltaTime * SPEED_ANIM);
	if (mStepAnim > mTimeTotalAnim)
	{
		mStepAnim = 0.0f;
	}
	MV1SetAttachAnimTime(mModel, mAnimId, mStepAnim);

	// モデルの移動
	MV1SetPosition(mModel, mPos);

	// モデルの回転
	VECTOR angles = mAngles;
	angles.x += mAnglesLocal.x;
	angles.y += mAnglesLocal.y;
	angles.z += mAnglesLocal.z;
	MV1SetRotationXYZ(mModel, angles);

}

void Unit3D::Draw(void)
{
	MV1DrawModel(mModel);
}

void Unit3D::Release(void)
{
	MV1DeleteModel(mModel);
}

void Unit3D::Save(void)
{

	std::ofstream ofs = std::ofstream("Data/Data07.csv");

	if (!ofs)
	{
		return;
	}

	std::string save = "";
	// ここからコーディングしていこう
	// intからstringへ変換するにはstd::to_string関数を使用します
	// 座標は、Vector2の代わりに、VECTOR(x,y,z)を使用しています
	//------------------------------------------
	//------------------------------------------
	ofs << save << std::endl;
	ofs.close();

}

void Unit3D::Load(void)
{

	std::ifstream ifs = std::ifstream("Data/Data07.csv");
	std::string line;
	if (ifs)
	{

		// Hint:カンマ区切りは、Utility::Splitを使用
		int cnt = 0;

		int size;
		while (getline(ifs, line))
		{
			std::vector<std::string> strvec = AsoUtility::Split(line, ',');
			size = strvec.size();
			for (int i = 0; i < size; i++)
			{
				// ここからコーディングしていこう
				// stringからintへ変換するにはstoi関数を使用します
				// 座標は、Vector2の代わりに、VECTOR(x,y,z)を使用しています
				//------------------------------------------
				//------------------------------------------

			}

		}

		ifs.close();
	}

}

VECTOR Unit3D::GetPos(void)
{
	return mPos;
}

VECTOR Unit3D::GetAngles(void)
{
	return mAngles;
}

void Unit3D::ChangeAnim(ANIM_STATE state)
{

	if (mAnimState == state)
	{
		return;
	}

	MV1DetachAnim(mModel, mAnimId);

	mAnimState = state;
	switch (mAnimState)
	{
	case ANIM_STATE::IDLE:
		mAnimId = MV1AttachAnim(mModel, 0);
		break;
	case ANIM_STATE::WALK:
		mAnimId = MV1AttachAnim(mModel, 1);
		break;
	}

	// アニメーション総時間の取得
	mStepAnim = 0.0f;
	mTimeTotalAnim = MV1GetAttachAnimTotalTime(mModel, mAnimId);
	
}
