#include "DxLib.h"
#include "SceneManager.h"
#include "StarDust.h"
#include "Sphere.h"
#include "StarDustManager.h"

StarDustManager::StarDustManager(SceneManager* manager)
{
	mSceneManager = manager;
}

void StarDustManager::Init(void)
{
}

void StarDustManager::Update(void)
{

	mStep += mSceneManager->GetDeltaTime();
	int size = mStarDusts.size();

	if (mStep > mLoopTime)
	{
		mStep = 0.0f;
		for (int i = 0; i < size; i++)
		{
			mStarDusts[i]->Random();
		}
	}

	for (int i = 0; i < size; i++)
	{
		mStarDusts[i]->Update();
	}
	
}

void StarDustManager::Draw(Sphere* sphere)
{

	int size = mStarDusts.size();
	for (int i = 0; i < size; i++)
	{

		if (sphere->InRange(mStarDusts[i]->GetPos()))
		{
			//-----------------------------------------
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			//-----------------------------------------
			mStarDusts[i]->Draw();
			//-----------------------------------------
			// �u�����h���[�h�����ɖ߂�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			//-----------------------------------------
		}
		else
		{
			mStarDusts[i]->Draw();
		}

	}

}

void StarDustManager::Release(void)
{

	int size = mStarDusts.size();
	for (int i = 0; i < size; i++)
	{
		mStarDusts[i]->Release();
		delete mStarDusts[i];
	}
	mStarDusts.clear();

}

void StarDustManager::Create(Vector2 pos, float loopTime, int num)
{

	mPos = pos;
	mLoopTime = loopTime;

	for (int i = 0; i < num; i++)
	{
		mStarDusts.push_back(new StarDust(mSceneManager, mPos));
	}

}
