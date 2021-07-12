#pragma once
#include "DxLib.h"
class SceneManager;

class Unit3D
{

public:

	static constexpr float SPEED_ANIM = 20.0f;
	static constexpr float TIME_ROT = 1.0f;

	// 5度(deg)
	static constexpr float SPEED_ROT = 5.0f;

	// 5度(rad)
	static constexpr float SPEED_ROT_RAD = SPEED_ROT * (DX_PI_F / 180.0f);

	enum class ANIM_STATE
	{
		NONE,
		IDLE,
		WALK
	};

	Unit3D(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void Save(void);
	void Load(void);

	VECTOR GetPos(void);
	VECTOR GetAngles(void);

private:

	SceneManager* mSceneManager;

	ANIM_STATE mAnimState;

	int mModel;
	int mAnimId;

	// アニメーションの総時間
	float mTimeTotalAnim;

	// アニメーション用更新ステップ
	float mStepAnim;

	VECTOR mPos;

	VECTOR mAngles;
	VECTOR mAnglesLocal;

	void ChangeAnim(ANIM_STATE state);

};
