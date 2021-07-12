#include <vector>
#include <fstream>
#include "DxLib.h"
#include "GameCommon.h"
#include "AsoUtility.h"
#include "Unit.h"

Unit::Unit(void)
{
	mImage = LoadGraph("Image/Human.png");
	mPos = { SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 };
}

int Unit::GetId(void)
{
	return mId;
}

void Unit::SetId(int id)
{
	mId = id;
}

std::string Unit::GetName(void)
{
	return mName;
}

void Unit::SetName(std::string name)
{
	mName = name;
}

int Unit::GetLevel(void)
{
	return mLevel;
}

void Unit::SetLevel(int level)
{
	mLevel = level;
}

int Unit::GetHp(void)
{
	return mHp;
}

void Unit::SetHp(int hp)
{
	mHp = hp;
}

int Unit::GetMp(void)
{
	return mMp;
}

void Unit::SetMp(int mp)
{
	mMp = mp;
}

int Unit::GetPower(void)
{
	return mPower;
}

void Unit::SetPower(int power)
{
	mPower = power;
}

int Unit::GetSpeed(void)
{
	return mSpeed;
}

void Unit::SetSpeed(int speed)
{
	mSpeed = speed;
}

void Unit::Update(void)
{

	// 移動量
	float movePow = 2.0f;

	// 左
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		mPos.x -= movePow;
	}

	// 右
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		mPos.x += movePow;
	}

	// 上
	if (CheckHitKey(KEY_INPUT_UP))
	{
		mPos.y -= movePow;
	}

	// 下
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		mPos.y += movePow;
	}

}

void Unit::Draw(void)
{
	DrawRotaGraph(mPos.x, mPos.y, 0.5f, 0.0f, mImage, true);
}

void Unit::DrawStatus(void)
{

	int cy = (SCREEN_SIZE_Y / 2) - 150;
	int width = 170;
	int h = 30;
	int hWidth = width / 2;

	int margin = 5;

	int cntRow = 0;

	int x = ((width + 30) * (mId - 1)) + 30;
	int y = cy + margin;
	DrawBox(x, cy, x + width, cy + (h * 6), 0x000000, true);


	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "名前　　：%s", mName.c_str());
	cntRow++;
	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "レベル　：%d", mLevel);
	cntRow++;
	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "ＨＰ　　：%d", mHp);
	cntRow++;
	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "ＭＰ　　：%d", mMp);
	cntRow++;
	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "パワー　：%d", mPower);
	cntRow++;
	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "スピード：%d", mSpeed);

}

Vector2 Unit::GetPos(void)
{
	return mPos;
}

void Unit::Save(void)
{

	std::ofstream ofs = std::ofstream("Data/Data06.csv");

	if (!ofs)
	{
		return;
	}
	
	std::string save = "";
	// ここからコーディングしていこう
	// intからstringへ変換するにはstd::to_string関数を使用します
	//------------------------------------------
	//------------------------------------------
	ofs << save << std::endl;
	ofs.close();

}

void Unit::Load(void)
{

	std::ifstream ifs = std::ifstream("Data/Data06.csv");
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
				//------------------------------------------
				//------------------------------------------

			}
			
		}

		ifs.close();
	}

}
