#pragma once
#include <string>
#include "Vector2.h"

class Unit
{
public:

	Unit(void);

	// ID
	int GetId(void);
	void SetId(int id);

	// –¼‘O
	std::string GetName(void);
	void SetName(std::string name);

	// ƒŒƒxƒ‹
	int GetLevel(void);
	void SetLevel(int level);

	// HP
	int GetHp(void);
	void SetHp(int hp);

	// MP
	int GetMp(void);
	void SetMp(int mp);

	// Power
	int GetPower(void);
	void SetPower(int power);

	// Speed
	int GetSpeed(void);
	void SetSpeed(int speed);

	void Update(void);
	void Draw(void);
	void DrawStatus(void);

	Vector2 GetPos(void);

	void Save(void);
	void Load(void);

private:

	int mId;
	std::string mName;
	int mLevel;
	int mHp;
	int mMp;
	int mPower;
	int mSpeed;

	int mImage;
	Vector2 mPos;

};

