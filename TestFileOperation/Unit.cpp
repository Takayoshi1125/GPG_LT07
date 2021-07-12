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

	// �ړ���
	float movePow = 2.0f;

	// ��
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		mPos.x -= movePow;
	}

	// �E
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		mPos.x += movePow;
	}

	// ��
	if (CheckHitKey(KEY_INPUT_UP))
	{
		mPos.y -= movePow;
	}

	// ��
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


	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "���O�@�@�F%s", mName.c_str());
	cntRow++;
	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "���x���@�F%d", mLevel);
	cntRow++;
	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "�g�o�@�@�F%d", mHp);
	cntRow++;
	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "�l�o�@�@�F%d", mMp);
	cntRow++;
	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "�p���[�@�F%d", mPower);
	cntRow++;
	DrawFormatString(x + margin, y + (h * cntRow), 0xffffff, "�X�s�[�h�F%d", mSpeed);

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
	// ��������R�[�f�B���O���Ă�����
	// int����string�֕ϊ�����ɂ�std::to_string�֐����g�p���܂�
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

		// Hint:�J���}��؂�́AUtility::Split���g�p
		int cnt = 0;

		int size;
		while (getline(ifs, line))
		{
			std::vector<std::string> strvec = AsoUtility::Split(line, ',');
			size = strvec.size();
			for (int i = 0; i < size; i++)
			{
				// ��������R�[�f�B���O���Ă�����
				// string����int�֕ϊ�����ɂ�stoi�֐����g�p���܂�
				//------------------------------------------
				//------------------------------------------

			}
			
		}

		ifs.close();
	}

}
