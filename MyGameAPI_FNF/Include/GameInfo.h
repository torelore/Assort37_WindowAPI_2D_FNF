#pragma once

/*
stl : standard template library�̴�.
�迭, ����ũ�帮��Ʈ �� �ڷᱸ������ �̸� �����س��� ���̺귯���̴�.
*/

#include <Windows.h>
#include <list>		// ����ũ�帮��Ʈ ���ø� �ڷᱸ��
#include <vector>	// �����迭 ���ø� �ڷᱸ��
#include <stack>
#include <string>
#include <unordered_map>
#include <crtdbg.h>
#include <functional>
#include <fstream>
#include <iostream>
#include <io.h>
#include "resource.h"

#include "SharedPtr.h"
#include "Math.h"
#include "Flag.h"
#include "lib/fmod/fmod.hpp"
#include "Resource/JsonCpp/json/json.h"

#pragma comment(lib, "msimg32.lib")

#pragma comment(lib, "fmod64_vc.lib")

#define	GRAVITY	9.8f

#define	NOTE_ENEMY_X	100.f
#define	NOTE_MY_X		800.f
#define	NOTE_START_Y	800.f
#define	NOTE_END_Y		100.f

#define	UI_FREEPLAY_SONG_X		80.f
#define	UI_FREEPLAY_SONG_MOVE_X	15.f
#define	UI_FREEPLAY_SONG_Y		360.f
#define	UI_FREEPLAY_SONG_MOVE_Y	160.f

#define NOTERATE_SICK	1000
#define NOTERATE_GOOD	500
#define NOTERATE_BAD	250

#define	KEYCOUNT_MAX	256

#define	ROOT_PATH		"RootPath"
#define	TEXTURE_PATH	"TexturePath"
#define	SOUND_PATH		"SoundPath"
#define	MUSIC_PATH		"MusicPath"
#define	FONT_PATH		"FontPath"
#define	MAP_PATH		"MapPath"
#define	JSON_PATH		"JsonPath"


#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }

struct Resolution
{
	int	Width;
	int	Height;
};

struct RectInfo
{
	float	Left;
	float	Top;
	float	Right;
	float	Bottom;

	RectInfo() :
		Left(0.f),
		Top(0.f),
		Right(0.f),
		Bottom(0.f)
	{
	}
};

struct SphereInfo
{
	Vector2	Center;
	float	Radius;
};

struct AnimationFrameData
{
	Vector2	StartPos;
	Vector2	Size;
};

struct CharacterInfo
{
	int	Attack;
	int	Armor;
	int	HP;
	int	HPMax;
	int	MP;
	int	MPMax;
	int	Level;
	int	Exp;
	int	Gold;
	float	AttackSpeed;
	float	AttackDistance;
};

struct CollisionProfile
{
	std::string			Name;
	ECollision_Channel	Channel;
	bool				CollisionEnable;

	// Channel ����ŭ�� �����Ѵ�. ���� �� ���������� �ٸ� �������ϰ� �浹�ؾ� ����
	// ������ ���Ҷ� �ش� ���������� ����ϴ� ä�ΰ� Ignore���� Collision������
	// �Ǵ��Ҷ� ����Ѵ�.
	std::vector<ECollision_State>	vecState;
};

struct NoteInfo {
	ENote_Type	NoteType;
	ENote_Owner	NoteOwner;
	float		NoteTime;
	float		LongNoteTime;
	int			NoteBpm;

	NoteInfo(ENote_Type Type, float Time, ENote_Owner Owner = ENote_Owner::Player, int Bpm = 60, float LongTime = 0.f) :
		NoteType(Type),
		NoteOwner(Owner),
		NoteTime(Time),
		NoteBpm(Bpm),
		LongNoteTime(LongTime)
	{
	}
};

struct BackgroundInfo {
	std::string BackgroundName;
	std::string BackgroundImg;
	std::string BackgroundComponent;
};

struct SongInfo {
	std::string		SongName;
	std::unordered_map<ESong_Difficulty, std::list<NoteInfo>> NotesList;
	std::string		EnemyName;
	std::string		BackgroundName;
};

struct GameScore {
	std::string		SongName;
	ESong_Difficulty Difficulty;
	int Score;
	int MissCount;
	int MaxCombo;
	EGame_Rate Rate;

	GameScore(std::string SongName, ESong_Difficulty Difficulty, int Score, int MissCount, int MaxCombo, EGame_Rate Rate = EGame_Rate::Failed) {
		this->SongName = SongName;
		this->Difficulty = Difficulty;
		this->Score = Score;
		this->MissCount = MissCount;
		this->MaxCombo = MaxCombo;
		this->Rate = Rate;
	}
};