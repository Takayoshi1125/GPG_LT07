#include <fstream>
#include "DxLib.h"
#include "AsoUtility.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "GameCommon.h"
#include "Star.h"
#include "Sphere.h"
#include "Unit.h"
#include "Unit3D.h"
#include "StarDustManager.h"
#include "Camera.h"
#include "TestScene.h"

TestScene::TestScene(SceneManager* manager) : SceneBase(manager)
{
	mWidth = SCREEN_SIZE_X / SPLIT_X;
	mHeight = SCREEN_SIZE_Y / SPLIT_Y;

	mCamera = new Camera();
	mCamera->Init();

	mUnit3D = new Unit3D(manager);
	mUnit3D->Init();

	mUnit = new Unit();

}

void TestScene::Init(void)
{

	mPage = 1;
	mIsPageInit = true;

	mImgBackGround = LoadGraph("Image/BackGround.png");

	// ブロック画像の読み込み
	LoadDivGraph(
		"Image/Blocks.png",
		IMG_NUM_ALL,
		IMG_NUM_X, IMG_NUM_Y,
		BLOCK_IMG_SIZE_X, BLOCK_IMG_SIZE_Y,
		&mImages[0],
		true);

	// 配列の初期化
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			mData[y][x] = 0;
		}
	}

	// ブロック描画に使用する
	mImgBlockGreen	= mImages[0];
	mImgBlockBlue	= mImages[104];
	mImgPlanePurple = mImages[528];
	mImgPlaneRed	= mImages[425];
	mImgPlaneGreen	= mImages[8];
	mImgPlaneWhite	= mImages[739];

	// ■ポインタ用変数
	mPower = 120;
	mSpeedPtr = &mSpeed;
	*mSpeedPtr = 881;
	mData[1][3] = 777;

	mStar = new Star();
	mStar->Init();
	mStar->SetSizeRate(0.5f);

	for (int i = 0; i < 3; i++)
	{
		mStarChildren[i] = new Star();
		mStarChildren[i]->Init();
		mStarChildren[i]->SetSizeRate(0.2f);
	}

	mSphere = new Sphere();
	mSphere->Init();

	mMoveStep = 0.0f;

	// ■検索用

	// ■色
	mStep = 0.0f;
	mEnemy.Init();
	mJumpMan.Init();
	int img = LoadGraph("Image/Smoke.png");

	int cx = SCREEN_SIZE_X / 4;
	int cy = SCREEN_SIZE_Y / 2;
	int max = 200;
	int r = 0;
	int x = 0;
	int y = 0;
	for (int i = 0; i < 20; i++)
	{
		x = cx + (max / 2) - GetRand(max);
		y = cy + (max / 2) - GetRand(max);
		mSmokesVecL.push_back(Smoke(img, { x, y }));
	}
	for (int i = 0; i < 20; i++)
	{
		x = (cx * 3) + (max / 2) - GetRand(max);
		y = cy + (max / 2) - GetRand(max);
		mSmokesVecR.push_back(Smoke(img, { x, y }));
	}

	mStarDustManager = new StarDustManager(mSceneManager);
	mStarDustManager->Init();

}

void TestScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mStep = 0.0f;
		mMoveStep = 0.0f;
		mPage += 1;
		if (mPage > MAX_PAGES)
		{
			mPage = 1;
		}
		switch (mPage)
		{
		case 5:
			mStarDustManager->Create(
				{ SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 }, 2.0f, 25);
			break;
		}

		mIsPageInit = true;

	}

	switch (mPage)
	{
	case 1:
		// 演習①
		UpdateTest01(1);
		break;
	case 2:
		// 演習②
		UpdateTest02(1);
		break;
	case 3:
		// 演習③
		UpdateTest03(1);
		break;
	case 4:
		// 演習④
		UpdateTest04(1);
		break;
	case 5:
		// 演習⑤
		UpdateTest05(1);
		break;
	case 6:
		// 演習⑥
		UpdateTest06(1);
		break;
	case 7:
		// 演習⑦
		UpdateTest07(1);
		break;
	default:
		break;
	}

}

void TestScene::Draw(void)
{

	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// 背景の描画
	DrawBackGround();

	switch (mPage)
	{
	case 1:
		// 演習①
		DrawTest01(1);
		break;
	case 2:
		// 演習②
		DrawTest02(1);
		break;
	case 3:
		// 演習③
		DrawTest03(1);
		break;
	case 4:
		// 演習④
		DrawTest04(1);
		break;
	case 5:
		// 演習⑤
		DrawTest05(1);
		break;
	case 6:
		// 演習⑥
		DrawTest06(1);
		break;
	case 7:
		// 演習⑦
		DrawTest07(1);
		break;
	default:
		break;
	}

	// タイトルの表示
	DrawFormatString(
		0, 0,
		0x000000,
		"ファイル操作");

	mIsPageInit = false;

}

void TestScene::DrawBackGround(void)
{

	// 白
	DrawBox(
		0, 0, 
		SCREEN_SIZE_X, SCREEN_SIZE_Y, 
		0xb0c4de, true
	);
	//DrawGraph(0, 0, mImgBackGround, false);

	for (int x = 0; x < SPLIT_X; x++)
	{
		for (int y = 0; y < SPLIT_Y; y++)
		{

			DrawBox(
				DRAW_AREA_X + (x * mWidth), DRAW_AREA_Y + (y * mHeight),
				DRAW_AREA_X + ((x + 1) * mWidth), DRAW_AREA_Y + ((y + 1) * mHeight),
				0x000000, false
			);

		}
	}

}

void TestScene::Release(void)
{

	// 画像の解放
	for (int i = 0; i < (IMG_NUM_X * IMG_NUM_Y); i++)
	{
		DeleteGraph(mImages[i]);
	}

	mStar->Release();
	delete mStar;

}

int TestScene::GetPage(void)
{
	return mPage;
}

void TestScene::DrawTest01(int no)
{

	DrawTitle(no, "演習①画像(Image/Human.png)を読み込んで、画面中央に表示させましょう。");


	if (mIsPageInit)
	{
		// ページ初期処理(ページ遷移時に１回しか処理されない)

		// 画像の読み込み
		//------------------------------------------
		mImage = LoadGraph("Image/Human.png");
		//------------------------------------------
	}

	// 画像の描画
	//------------------------------------------
	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.0f, 0.0f, mImage, true);
	//------------------------------------------

}

void TestScene::DrawTest02(int no)
{

	DrawTitle(no, "演習②テキストファイル(Data/Data02.txt)にある１文を読み込んで、画面中央に表示させましょう。");

	if (mIsPageInit)
	{
		// ページ初期処理(ページ遷移時に１回しか処理されない)

		// 画像の読み込み
		//------------------------------------------
		mMessage = "ファイルを読み込めていません。";
		std::ifstream ifs = std::ifstream("Data/Data02.txt");
		std::string line;
		if (ifs)
		{
			// ここからコーディングしていこう
			//------------------------------------------
			while (getline(ifs, line))
			{
				mMessage = line;
			}
			
			//------------------------------------------

			ifs.close();
		}
		//------------------------------------------
	}

	// 文字の描画
	//------------------------------------------
	int len = (int)strlen(mMessage.c_str());
	int width = GetDrawStringWidth(mMessage.c_str(), len);
	DrawFormatString((SCREEN_SIZE_X / 2) - (width / 2), SCREEN_SIZE_Y / 2, 0x000000, "%s", mMessage.c_str());
	//------------------------------------------

}

void TestScene::DrawTest03(int no)
{

	DrawTitle(no, "演習③CSVファイル(Data/Data03.csv)を読み込んで、それぞれの値を行を分けて画面に表示させましょう。");

	if (mIsPageInit)
	{
		// ページ初期処理(ページ遷移時に１回しか処理されない)

		// 画像の読み込み
		//------------------------------------------
		std::ifstream ifs = std::ifstream("Data/Data03.csv");
		std::string line;
		if (ifs)
		{
			while (getline(ifs, line))
			{
				mMessages.clear();

				// ここからコーディングしていこう
				//------------------------------------------

				// Hint:カンマ区切りは、Utility::Splitを使用
				std::vector<std::string>strvec =
					AsoUtility::Split(line,',');

				
				int size = strvec.size();
				/*for (int i = 0; i < size; i++)
				{
					mMessages[i] = stoi(strvec[i]);
				}*/

				//------------------------------------------
			}
			ifs.close();
		}
		//------------------------------------------
	}

	// 文字の描画
	//------------------------------------------
	int len;
	int width;
	int h = 30;
	int y = SCREEN_SIZE_Y / 2;
	int size = mMessages.size();
	y -= (h * (size / 2));
	const char* cmsg;
	for (int i = 0;i < size;i++)
	{
		cmsg = mMessages[i].c_str();
		len = (int)strlen(cmsg);
		width = GetDrawStringWidth(cmsg, len);
		DrawFormatString((SCREEN_SIZE_X / 2) - (width / 2), y + (i * h), 0x000000, "%s", cmsg);
	}
	//------------------------------------------

}

void TestScene::DrawTest04(int no)
{

	DrawTitle(no, "演習④CSVファイル(Data/Data04.csv)には、ゲーム内で使用されるメッセージの一覧が格納されている。");
	DrawAnsString(no, 0, "%s", "　　　動的配列mapにIDとメッセージを設定し、画面に表示させましょう。");

	// 動的配列mapの使い方
	// 値を取り出すためのKeyとValue(値)の２つ要素を使って動的に配列を確保する
	// 要素の追加の仕方は、std::map<int, std::string>の場合、
	// map.emplace(1, "ああああ");
	// 上記のようにする。

	if (mIsPageInit)
	{
		// ページ初期処理(ページ遷移時に１回しか処理されない)

		// 画像の読み込み
		//------------------------------------------
		std::ifstream ifs = std::ifstream("Data/Data04.csv");
		std::string line;
		if (ifs)
		{

			mMsgMap.clear();

			// ここからコーディングしていこう
			//------------------------------------------
			while (getline(ifs, line))
			{
				// Hint:カンマ区切りは、Utility::Splitを使用
				std::vector<std::string>strvec =
					AsoUtility::Split(line, ',');

				int mID = stoi(strvec[0]);
				std::string mMes = strvec[1];

				mMsgMap.emplace(mID, mMes);

				//------------------------------------------
			}
			ifs.close();
		}
		//------------------------------------------
	}

	// 文字の描画
	//------------------------------------------
	int h = 30;
	int y = SCREEN_SIZE_Y / 2;
	int key;
	int keys[2] = {2, 6};

	for (int i = 0; i < 2; i++)
	{
		key = keys[i];
		if (mMsgMap.count(key) > 0)
		{
			DrawFormatString((SCREEN_SIZE_X / 2) - 100, y + (h * i), 0x000000, "%s", mMsgMap[key].c_str());
		}
		else
		{
			DrawFormatString((SCREEN_SIZE_X / 2) - 100, y + (h * i), 0x000000,
				"メッセージID : %d が正しく読み込まれていません。", key);
		}
	}
	//------------------------------------------

}

void TestScene::DrawTest05(int no)
{

	DrawTitle(no, "演習⑤CSVファイル(Data/Data05.csv)には、ユニット5体分のステータスが格納されている。");
	DrawAnsString(no, 0, "%s", "　　　Unitクラスに各ステータスを設定し、それぞれのステータスを画面に表示させましょう。");

	if (mIsPageInit)
	{
		// ページ初期処理(ページ遷移時に１回しか処理されない)

		// 画像の読み込み
		//------------------------------------------
		std::ifstream ifs = std::ifstream("Data/Data05.csv");
		std::string line;
		if (ifs)
		{
			// ここからコーディングしていこう
			//------------------------------------------

			// Hint:カンマ区切りは、Utility::Splitを使用

			//------------------------------------------

			ifs.close();
		}
		//------------------------------------------
	}

	// ユニットステータスの描画
	//------------------------------------------
	int size = mUnits.size();
	for (int i = 0; i < size; i++)
	{
		mUnits[i]->DrawStatus();
	}
	//------------------------------------------

}

void TestScene::DrawTest06(int no)
{

	if (mIsPageInit)
	{
		mUnit->Load();
	}

	DrawTitle(no, "演習⑥CSVファイル(Data/Data06.csv)を使用して、ユニットの座標をロード＆セーブできるようにしましょう。");
	DrawAnsString(no, 0, "%s", "　　　UnitクラスのLoad、Save関数に、それぞれ実装していきましょう。");
	DrawAnsString(no, 1, "%s", "　　　(Ｌキー：ロード実行　Ｓキー：ロード実行)");

	// ロード
	if (CheckHitKey(KEY_INPUT_L))
	{
		mUnit->Load();
	}

	// セーブ
	if (CheckHitKey(KEY_INPUT_S))
	{
		mUnit->Save();
	}

	mUnit->Draw();

}

void TestScene::DrawTest07(int no)
{

	if (mIsPageInit)
	{
		mUnit3D->Load();
	}

	DrawTitle(no, "演習⑦CSVファイル(Data/Data06.csv)を使用して、ユニットの座標をロード＆セーブできるようにしましょう。");
	DrawAnsString(no, 0, "%s", "　　　Unit3DクラスのLoad、Save関数に、それぞれ実装していきましょう。");
	DrawAnsString(no, 1, "%s", "　　　(Ｌキー：ロード実行　Ｓキー：ロード実行)");

	// ロード
	if (CheckHitKey(KEY_INPUT_L))
	{
		mUnit3D->Load();
	}

	// セーブ
	if (CheckHitKey(KEY_INPUT_S))
	{
		mUnit3D->Save();
	}

	mCamera->SetBeforeDraw();
	mCamera->Draw();

	mUnit3D->Draw();

}


void TestScene::DrawTitle(int no, const char* title)
{

	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;
	
	int x = DRAW_AREA_X + (mWidth * tmpX) + TITLE_MARGIN;
	int y = DRAW_AREA_Y + (mHeight * tmpY) + TITLE_MARGIN;

	DrawFormatString(x, y, 0x000000, title);

}

void TestScene::DrawTestGround(int no, int meshSize)
{

	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;

	int x1 = DRAW_AREA_X + (mWidth * tmpX) + GROUND_MARGIN;
	int y1 = DRAW_AREA_Y + (mHeight * tmpY) + GROUND_MARGIN;
	int w = MAP_SIZE_X * BLOCK_IMG_SIZE_X;
	int h = MAP_SIZE_Y * BLOCK_IMG_SIZE_Y;
	int x2 = x1 + w;
	int y2 = y1 + h;
	DrawBox(
		x1, y1,
		x2, y2,
		0x696969, true);

	if (meshSize == 0)
	{
		return;
	}

	int cntY = h / meshSize;
	for (int y = 1; y < cntY; y++)
	{
		DrawLine(
			x1, y1 + (y * meshSize), 
			x2, y1 + (y * meshSize), 0x66cdaa, true);
	}

	int cntX = w / meshSize;
	for (int x = 1; x < cntX; x++)
	{
		DrawLine(
			x1 + (x * meshSize), y1,
			x1 + (x * meshSize), y2, 0x66cdaa, true);
	}

}

void TestScene::DrawData(int no, int imgHandle)
{

	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;

	int marginX = (mWidth * tmpX) + GROUND_MARGIN;
	int marginY = (mHeight * tmpY) + GROUND_MARGIN;
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			if (mData[y][x] == 1)
			{
				DrawGraph(
					DRAW_AREA_X + marginX + (x * BLOCK_IMG_SIZE_X),
					DRAW_AREA_Y + marginY + (y * BLOCK_IMG_SIZE_Y),
					imgHandle, true);
			}
		}
	}

}

Vector2 TestScene::GetDrawAnsPos(int no, int lineY)
{
	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;

	int x = DRAW_AREA_X + (mWidth * tmpX) + TITLE_MARGIN;
	int y = DRAW_AREA_Y + (mHeight * tmpY) + TITLE_MARGIN;

	y += TestScene::CHR_HEIGHT;
	y += (lineY * TestScene::CHR_HEIGHT);

	return Vector2(x, y);
}

void TestScene::DrawAnsString(int no, int lineY, const char* fmt, int value)
{
	Vector2 v = GetDrawAnsPos(no, lineY);
	DrawFormatString(v.x, v.y, 0x000000, fmt, value);
}

void TestScene::DrawAnsString(int no, int lineY, const char* fmt, int* value)
{
	Vector2 v = GetDrawAnsPos(no, lineY);
	DrawFormatString(v.x, v.y, 0x000000, fmt, value);
}

void TestScene::DrawAnsString(int no, int lineY, const char* fmt, const char* value)
{
	Vector2 v = GetDrawAnsPos(no, lineY);
	DrawFormatString(v.x, v.y, 0x000000, fmt, value);
}

void TestScene::UpdateTest01(int no)
{
}

void TestScene::UpdateTest02(int no)
{
}

void TestScene::UpdateTest03(int no)
{
}

void TestScene::UpdateTest04(int no)
{
}

void TestScene::UpdateTest05(int no)
{
}

void TestScene::UpdateTest06(int no)
{
	mUnit->Update();
}

void TestScene::UpdateTest07(int no)
{
	mUnit3D->Update();
}
