#include "Scene_GamePlay.h"
#include "../SceneResource.h"
#include "../SceneManager.h"
#include "Scene_GameEndRate.h"
#include "../../UI/Scene/UI_GamePlay.h"
#include "../../UI/UI_HealthBar.h"
#include "../../Map/ScrollMap.h"
#include "../../Map/Train.h"
#include "../Camera.h"
#include "../../Object/Characters/BoyFriend.h"
#include "../../Object/Characters/GirlFriend.h"
#include "../../Object/Characters/Daddy.h"
#include "../../Object/Characters/Monster.h"
#include "../../Object/Characters/Spooky.h"
#include "../../Object/Characters/Senpai.h"
#include "../../Object/Characters/Mom.h"
#include "../../Object/Characters/MomAndDad.h"
#include "../../Object/Characters/Pico.h"
#include "../../Object/Note.h"
#include "../../Object/Note_EndPoint.h"


CScene_GamePlay::CScene_GamePlay() : 
	m_Score(0),
	m_NoteCount(0),
	m_NoteMissCount(0),
	m_Rating(0.f),
	m_Combo(0),
	m_MaxCombo(0),
	m_NoteRate(nullptr),
	m_ComboFont(nullptr),
	m_SongNameVoice(""),
	m_SongNameInst(""),
	m_IsGameStop(false),
	m_NowSongDifficulty(ESong_Difficulty::Normal),
	m_NowSongName(""),
	m_IsStoryMode(false)
{
}

CScene_GamePlay::CScene_GamePlay(const CScene_GamePlay& scene)
{
	m_Score = scene.m_Score;
	m_NoteCount = scene.m_NoteCount;
	m_NoteMissCount = scene.m_NoteMissCount;
	m_Rating = scene.m_Rating;
	m_Combo = scene.m_Combo;
	m_MaxCombo = scene.m_MaxCombo;
	m_NoteRate = scene.m_NoteRate;
	m_ComboFont = scene.m_ComboFont;
	m_SongNameVoice = scene.m_SongNameVoice;
	m_SongNameInst = scene.m_SongNameInst;
	m_IsGameStop = scene.m_IsGameStop;
	m_NowSongDifficulty = scene.m_NowSongDifficulty;
	m_NowSongName = scene.m_NowSongName;
	m_IsStoryMode = scene.m_IsStoryMode;
}

CScene_GamePlay::~CScene_GamePlay()
{
}

bool CScene_GamePlay::Init()
{
	LoadSound();
	LoadAnimationSequence();

	GetCamera()->SetWorldResolution(3000.f, 2000.f);

	// Player Setting
	CBoyFriend* BF = CreateObject<CBoyFriend>("BF");
	BF->SetPos(800.f, 350.f);
	//BF->SetPos(1400.f, 600.f);

	SetPlayer(BF);
	
	/*GetCamera()->SetTarget(BF);
	GetCamera()->SetTargetPivot(0.6f, 0.4f);*/

	// Player NoteEndPoint Setting
	{
		CNote_EndPoint* NoteEndPoint = CreateObject<CNote_EndPoint>("NoteEndPoint_Left");
		NoteEndPoint->SetInfo(ENote_Owner::Player, ENote_Type::Left);

		NoteEndPoint->SetCharacter(BF);
		BF->SetLeftEndPoint(NoteEndPoint);


		NoteEndPoint = CreateObject<CNote_EndPoint>("NoteEndPoint_Down");
		NoteEndPoint->SetInfo(ENote_Owner::Player, ENote_Type::Down);

		NoteEndPoint->SetCharacter(BF);
		BF->SetDownEndPoint(NoteEndPoint);


		NoteEndPoint = CreateObject<CNote_EndPoint>("NoteEndPoint_Up");
		NoteEndPoint->SetInfo(ENote_Owner::Player, ENote_Type::Up);

		NoteEndPoint->SetCharacter(BF);
		BF->SetUpEndPoint(NoteEndPoint);


		NoteEndPoint = CreateObject<CNote_EndPoint>("NoteEndPoint_Right");
		NoteEndPoint->SetInfo(ENote_Owner::Player, ENote_Type::Right);

		NoteEndPoint->SetCharacter(BF);
		BF->SetRightEndPoint(NoteEndPoint);
	}

	// GF 추가
	CGirlFriend* GF = CreateObject<CGirlFriend>("GF");
	GF->SetPos(350.f, 60.f);
	//GF->SetPos(900.f, 300.f);


	// Notes Prototype 추가
	CNote* PlayerNote = CreatePrototype<CNote>("PlayerNote");
	CNote* EnenyNote = CreatePrototype<CNote>("EnenyNote");

	return true;
}

void CScene_GamePlay::LoadAnimationSequence()
{
	// Notes
	{
		// UP_NOTE
		GetSceneResource()->CreateAnimationSequence("UP_NOTE", "UP_NOTE", TEXT("Notes/UpNote.bmp"));
		GetSceneResource()->SetTextureColorKey("UP_NOTE", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("UP_NOTE", 0.f, 0.f, 110.f, 108.f);


		// UP_BACK
		GetSceneResource()->CreateAnimationSequence("UP_BACK", "UP_BACK", TEXT("Notes/Up.bmp"));
		GetSceneResource()->SetTextureColorKey("UP_BACK", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("UP_BACK", 0.f, 0.f, 110.f, 107.f);


		// UP_PRESS
		GetSceneResource()->CreateAnimationSequence("UP_PRESS", "UP_PRESS", TEXT("Notes/UpPress.bmp"));
		GetSceneResource()->SetTextureColorKey("UP_PRESS", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("UP_PRESS", 0.f, 0.f, 110.f, 107.f);


		// UP_CONFIRM
		GetSceneResource()->CreateAnimationSequence("UP_CONFIRM", "UP_CONFIRM", TEXT("Notes/UpConfirm.bmp"));
		GetSceneResource()->SetTextureColorKey("UP_CONFIRM", 255, 0, 255);

		for (int i = 0; i < 3; i++)
			GetSceneResource()->AddAnimationFrameData("UP_CONFIRM", i * 166.f, 0.f, 166.f, 163.f);


		// DOWN_NOTE
		GetSceneResource()->CreateAnimationSequence("DOWN_NOTE", "DOWN_NOTE", TEXT("Notes/DownNote.bmp"));
		GetSceneResource()->SetTextureColorKey("DOWN_NOTE", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("DOWN_NOTE", 0.f, 0.f, 110.f, 108.f);


		// DOWN_BACK
		GetSceneResource()->CreateAnimationSequence("DOWN_BACK", "DOWN_BACK", TEXT("Notes/Down.bmp"));
		GetSceneResource()->SetTextureColorKey("DOWN_BACK", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("DOWN_BACK", 0.f, 0.f, 110.f, 107.f);


		// DOWN_PRESS
		GetSceneResource()->CreateAnimationSequence("DOWN_PRESS", "DOWN_PRESS", TEXT("Notes/DownPress.bmp"));
		GetSceneResource()->SetTextureColorKey("DOWN_PRESS", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("DOWN_PRESS", 0.f, 0.f, 110.f, 108.f);


		// DOWN_CONFIRM
		GetSceneResource()->CreateAnimationSequence("DOWN_CONFIRM", "DOWN_CONFIRM", TEXT("Notes/DownConfirm.bmp"));
		GetSceneResource()->SetTextureColorKey("DOWN_CONFIRM", 255, 0, 255);

		for (int i = 0; i < 3; i++) 
			GetSceneResource()->AddAnimationFrameData("DOWN_CONFIRM", i * 167.f, 0.f, 167.f, 165.f);


		// LEFT_NOTE
		GetSceneResource()->CreateAnimationSequence("LEFT_NOTE", "LEFT_NOTE", TEXT("Notes/LeftNote.bmp"));
		GetSceneResource()->SetTextureColorKey("LEFT_NOTE", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("LEFT_NOTE", 0.f, 0.f, 110.f, 112.f);


		// LEFT_BACK
		GetSceneResource()->CreateAnimationSequence("LEFT_BACK", "LEFT_BACK", TEXT("Notes/Left.bmp"));
		GetSceneResource()->SetTextureColorKey("LEFT_BACK", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("LEFT_BACK", 0.f, 0.f, 110.f, 113.f);


		// LEFT_PRESS
		GetSceneResource()->CreateAnimationSequence("LEFT_PRESS", "LEFT_PRESS", TEXT("Notes/LeftPress.bmp"));
		GetSceneResource()->SetTextureColorKey("LEFT_PRESS", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("LEFT_PRESS", 0.f, 0.f, 110.f, 109.f);


		// LEFT_CONFIRM
		GetSceneResource()->CreateAnimationSequence("LEFT_CONFIRM", "LEFT_CONFIRM", TEXT("Notes/LeftConfirm.bmp"));
		GetSceneResource()->SetTextureColorKey("LEFT_CONFIRM", 255, 0, 255);

		for (int i = 0; i < 3; i++)
			GetSceneResource()->AddAnimationFrameData("LEFT_CONFIRM", i * 160.f, 0.f, 160.f, 162.f);


		// RIGHT_NOTE
		GetSceneResource()->CreateAnimationSequence("RIGHT_NOTE", "RIGHT_NOTE", TEXT("Notes/RightNote.bmp"));
		GetSceneResource()->SetTextureColorKey("RIGHT_NOTE", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("RIGHT_NOTE", 0.f, 0.f, 110.f, 112.f);


		// RIGHT_BACK
		GetSceneResource()->CreateAnimationSequence("RIGHT_BACK", "RIGHT_BACK", TEXT("Notes/Right.bmp"));
		GetSceneResource()->SetTextureColorKey("RIGHT_BACK", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("RIGHT_BACK", 0.f, 0.f, 110.f, 113.f);


		// RIGHT_PRESS
		GetSceneResource()->CreateAnimationSequence("RIGHT_PRESS", "RIGHT_PRESS", TEXT("Notes/RightPress.bmp"));
		GetSceneResource()->SetTextureColorKey("RIGHT_PRESS", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("RIGHT_PRESS", 0.f, 0.f, 110.f, 112.f);


		// RIGHT_CONFIRM
		GetSceneResource()->CreateAnimationSequence("RIGHT_CONFIRM", "RIGHT_CONFIRM", TEXT("Notes/RightConfirm.bmp"));
		GetSceneResource()->SetTextureColorKey("RIGHT_CONFIRM", 255, 0, 255);

		for (int i = 0; i < 3; i++)
			GetSceneResource()->AddAnimationFrameData("RIGHT_CONFIRM", i * 157.f, 0.f, 157.f, 159.f);
	}


	// Rate
	{
		// SICK
		GetSceneResource()->CreateAnimationSequence("SICK", "SICK", TEXT("sick.bmp"));
		GetSceneResource()->SetTextureColorKey("SICK", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("SICK", 0.f, 0.f, 403.f, 152.f);


		// GOOD
		GetSceneResource()->CreateAnimationSequence("GOOD", "GOOD", TEXT("good.bmp"));
		GetSceneResource()->SetTextureColorKey("GOOD", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("GOOD", 0.f, 0.f, 317.f, 126.f);


		// BAD
		GetSceneResource()->CreateAnimationSequence("BAD", "BAD", TEXT("bad.bmp"));
		GetSceneResource()->SetTextureColorKey("BAD", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("BAD", 0.f, 0.f, 261.f, 131.f);


		// SHIT
		GetSceneResource()->CreateAnimationSequence("SHIT", "SHIT", TEXT("shit.bmp"));
		GetSceneResource()->SetTextureColorKey("SHIT", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("SHIT", 0.f, 0.f, 285.f, 163.f);
	}


	// CountDown
	{
		// READY
		GetSceneResource()->CreateAnimationSequence("READY", "READY", TEXT("ready.bmp"));
		GetSceneResource()->SetTextureColorKey("READY", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("READY", 0.f, 0.f, 757.f, 364.f);


		// SET
		GetSceneResource()->CreateAnimationSequence("SET", "SET", TEXT("set.bmp"));
		GetSceneResource()->SetTextureColorKey("SET", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("SET", 0.f, 0.f, 702.f, 322.f);


		// GO
		GetSceneResource()->CreateAnimationSequence("GO", "GO", TEXT("go.bmp"));
		GetSceneResource()->SetTextureColorKey("GO", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("GO", 0.f, 0.f, 558.f, 430.f);
	}


	// BF Animation
	{
	// BF_IDLE
		GetSceneResource()->CreateAnimationSequence("BF_IDLE", "BF_IDLE", TEXT("BOYFRIEND.bmp"));

		GetSceneResource()->SetTextureColorKey("BF_IDLE", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 0.f, 2344.f, 406.f, 392.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 0.f, 2344.f, 406.f, 392.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 416.f, 2344.f, 408.f, 393.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 416.f, 2344.f, 408.f, 393.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 834.f, 2344.f, 405.f, 398.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 834.f, 2344.f, 405.f, 398.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 1249.f, 2344.f, 410.f, 411.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 1249.f, 2344.f, 410.f, 411.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 1669.f, 2344.f, 408.f, 412.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 1669.f, 2344.f, 408.f, 412.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 1669.f, 2344.f, 408.f, 412.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 1669.f, 2344.f, 408.f, 412.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 1669.f, 2344.f, 408.f, 412.f);
		GetSceneResource()->AddAnimationFrameData("BF_IDLE", 1669.f, 2344.f, 408.f, 412.f);


		// BF_UP
		GetSceneResource()->CreateAnimationSequence("BF_UP", "BF_UP", TEXT("BOYFRIEND.bmp"));
		GetSceneResource()->SetTextureColorKey("BF_UP", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("BF_UP", 3580.f, 988.f, 369.f, 446.f);
		for (int i = 0; i < 13; i++)
			GetSceneResource()->AddAnimationFrameData("BF_UP", 3959.f, 988.f, 376.f, 441.f);


		// BF_UP_MISS
		GetSceneResource()->CreateAnimationSequence("BF_UP_MISS", "BF_UP_MISS", TEXT("BOYFRIEND.bmp"));
		GetSceneResource()->SetTextureColorKey("BF_UP_MISS", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("BF_UP_MISS", 3580.f, 988.f, 369.f, 446.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("BF_UP_MISS", 4345.f, 988.f, 360.f, 427.f);
		for (int i = 0; i < 21; i++)
			GetSceneResource()->AddAnimationFrameData("BF_UP_MISS", 4715.f, 988.f, 357.f, 430.f);


		// BF_DOWN
		GetSceneResource()->CreateAnimationSequence("BF_DOWN", "BF_DOWN", TEXT("BOYFRIEND.bmp"));
		GetSceneResource()->SetTextureColorKey("BF_DOWN", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("BF_DOWN", 6640.f, 509.f, 374.f, 357.f);
		for (int i = 0; i < 27; i++)
			GetSceneResource()->AddAnimationFrameData("BF_DOWN", 7024.f, 509.f, 373.f, 362.f);


		// BF_DOWN_MISS
		GetSceneResource()->CreateAnimationSequence("BF_DOWN_MISS", "BF_DOWN_MISS", TEXT("BOYFRIEND.bmp"));
		GetSceneResource()->SetTextureColorKey("BF_DOWN_MISS", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("BF_DOWN_MISS", 6640.f, 509.f, 374.f, 357.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("BF_DOWN_MISS", 7407.f, 509.f, 376.f, 392.f);
		for (int i = 0; i < 27; i++)
			GetSceneResource()->AddAnimationFrameData("BF_DOWN_MISS", 7793.f, 509.f, 378.f, 388.f);


		// BF_LEFT
		GetSceneResource()->CreateAnimationSequence("BF_LEFT", "BF_LEFT", TEXT("BOYFRIEND.bmp"));
		GetSceneResource()->SetTextureColorKey("BF_LEFT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("BF_LEFT", 0.f, 988.f, 383.f, 406.f);
		for (int i = 0; i < 12; i++)
			GetSceneResource()->AddAnimationFrameData("BF_LEFT", 393.f, 988.f, 374.f, 404.f);


		// BF_LEFT_MISS 
		GetSceneResource()->CreateAnimationSequence("BF_LEFT_MISS", "BF_LEFT_MISS", TEXT("BOYFRIEND.bmp"));
		GetSceneResource()->SetTextureColorKey("BF_LEFT_MISS", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("BF_LEFT_MISS", 777.f, 988.f, 383.f, 406.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("BF_LEFT_MISS", 1170.f, 988.f, 369.f, 430.f);
		for (int i = 0; i < 31; i++)
			GetSceneResource()->AddAnimationFrameData("BF_LEFT_MISS", 1549.f, 988.f, 370.f, 430.f);


		// BF_RIGHT
		GetSceneResource()->CreateAnimationSequence("BF_RIGHT", "BF_RIGHT", TEXT("BOYFRIEND.bmp"));
		GetSceneResource()->SetTextureColorKey("BF_RIGHT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("BF_RIGHT", 1929.f, 988.f, 408.f, 405.f);
		for (int i = 0; i < 59; i++)
			GetSceneResource()->AddAnimationFrameData("BF_RIGHT", 2347.f, 988.f, 408.f, 407.f);


		// BF_RIGHT_MISS 
		GetSceneResource()->CreateAnimationSequence("BF_RIGHT_MISS", "BF_RIGHT_MISS", TEXT("BOYFRIEND.bmp"));
		GetSceneResource()->SetTextureColorKey("BF_RIGHT_MISS", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("BF_RIGHT_MISS", 1929.f, 988.f, 408.f, 405.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("BF_RIGHT_MISS", 2765.f, 988.f, 395.f, 432.f);
		for (int i = 0; i < 43; i++)
			GetSceneResource()->AddAnimationFrameData("BF_RIGHT_MISS", 3170.f, 988.f, 378.f, 432.f);
	}



	// GF Animation
	{
		// GF_DANCING
		GetSceneResource()->CreateAnimationSequence("GF_DANCING", "GF_DANCING", TEXT("GF_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("GF_DANCING", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 3553.f, 0.f, 699.f, 634.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 4262.f, 0.f, 703.f, 634.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 4975.f, 0.f, 703.f, 632.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 5688.f, 0.f, 699.f, 632.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 6397.f, 0.f, 699.f, 635.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 7106.f, 0.f, 699.f, 635.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 0.f, 667.f, 699.f, 637.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 709.f, 667.f, 699.f, 648.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 709.f, 667.f, 699.f, 648.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 709.f, 667.f, 699.f, 648.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 1418.f, 667.f, 699.f, 648.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 1418.f, 667.f, 699.f, 648.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 1418.f, 667.f, 699.f, 648.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 2127.f, 667.f, 699.f, 648.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 2127.f, 667.f, 699.f, 648.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 2836.f, 667.f, 699.f, 636.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 3545.f, 667.f, 703.f, 636.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 4258.f, 667.f, 703.f, 636.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 4971.f, 667.f, 699.f, 636.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 5680.f, 667.f, 699.f, 637.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 6389.f, 667.f, 699.f, 637.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 7098.f, 667.f, 699.f, 638.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 0.f, 1325.f, 699.f, 643.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 0.f, 1325.f, 699.f, 643.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 0.f, 1325.f, 699.f, 643.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 709.f, 1325.f, 699.f, 642.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 709.f, 1325.f, 699.f, 642.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 709.f, 1325.f, 699.f, 642.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 1418.f, 1325.f, 699.f, 642.f);
		GetSceneResource()->AddAnimationFrameData("GF_DANCING", 1418.f, 1325.f, 699.f, 642.f);

		// GF_FEAR
		GetSceneResource()->CreateAnimationSequence("GF_FEAR", "GF_FEAR", TEXT("GF_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("GF_FEAR", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("GF_FEAR", 6406.f, 3295.f, 699.f, 640.f);
		GetSceneResource()->AddAnimationFrameData("GF_FEAR", 7115.f, 3295.f, 699.f, 640.f);
		GetSceneResource()->AddAnimationFrameData("GF_FEAR", 0.f, 3952.f, 699.f, 638.f);
		GetSceneResource()->AddAnimationFrameData("GF_FEAR", 709.f, 3952.f, 699.f, 640.f);


		// GF_UP
		GetSceneResource()->CreateAnimationSequence("GF_UP", "GF_UP", TEXT("GF_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("GF_UP", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("GF_UP", 7098.f, 3952.f, 699.f, 661.f);
		GetSceneResource()->AddAnimationFrameData("GF_UP", 0.f, 4623.f, 703.f, 661.f);
		GetSceneResource()->AddAnimationFrameData("GF_UP", 713.f, 4623.f, 703.f, 661.f);
		GetSceneResource()->AddAnimationFrameData("GF_UP", 1426.f, 4623.f, 699.f, 661.f);

		for (int i = 0; i < 3; i++)
			GetSceneResource()->AddAnimationFrameData("GF_UP", 2135.f, 4623.f, 699.f, 661.f);


		// GF_DOWN
		GetSceneResource()->CreateAnimationSequence("GF_DOWN", "GF_DOWN", TEXT("GF_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("GF_DOWN", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("GF_DOWN", 2853.f, 3295.f, 699.f, 631.f);
		GetSceneResource()->AddAnimationFrameData("GF_DOWN", 3562.f, 3295.f, 703.f, 631.f);
		GetSceneResource()->AddAnimationFrameData("GF_DOWN", 4275.f, 3295.f, 703.f, 636.f);
		GetSceneResource()->AddAnimationFrameData("GF_DOWN", 4988.f, 3295.f, 699.f, 636.f);

		for (int i = 0; i < 16; i++)
			GetSceneResource()->AddAnimationFrameData("GF_DOWN", 5697.f, 3295.f, 699.f, 637.f);


		// GF_LEFT
		GetSceneResource()->CreateAnimationSequence("GF_LEFT", "GF_LEFT", TEXT("GF_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("GF_LEFT", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("GF_LEFT", 2844.f, 4623.f, 699.f, 633.f);
		GetSceneResource()->AddAnimationFrameData("GF_LEFT", 3553.f, 4623.f, 703.f, 631.f);
		GetSceneResource()->AddAnimationFrameData("GF_LEFT", 4266.f, 4623.f, 703.f, 638.f);
		GetSceneResource()->AddAnimationFrameData("GF_LEFT", 4979.f, 4623.f, 699.f, 638.f);
		GetSceneResource()->AddAnimationFrameData("GF_LEFT", 5688.f, 4623.f, 699.f, 638.f);
		GetSceneResource()->AddAnimationFrameData("GF_LEFT", 6397.f, 4623.f, 699.f, 638.f);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("GF_LEFT", 7106.f, 4623.f, 699.f, 638.f);

		for (int i = 0; i < 7; i++)
		GetSceneResource()->AddAnimationFrameData("GF_LEFT", 0.f, 5294.f, 699.f, 637.f);


		// GF_RIGHT
		GetSceneResource()->CreateAnimationSequence("GF_RIGHT", "GF_RIGHT", TEXT("GF_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("GF_RIGHT", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("GF_RIGHT", 1418.f, 3952.f, 699.f, 632.f);
		GetSceneResource()->AddAnimationFrameData("GF_RIGHT", 2127.f, 3952.f, 703.f, 632.f);
		GetSceneResource()->AddAnimationFrameData("GF_RIGHT", 2840.f, 3952.f, 703.f, 637.f);
		GetSceneResource()->AddAnimationFrameData("GF_RIGHT", 3553.f, 3952.f, 699.f, 637.f);
		GetSceneResource()->AddAnimationFrameData("GF_RIGHT", 4262.f, 3952.f, 699.f, 637.f);
		GetSceneResource()->AddAnimationFrameData("GF_RIGHT", 4971.f, 3952.f, 699.f, 637.f);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("GF_RIGHT", 5680.f, 3952.f, 699.f, 637.f);

		for(int i = 0; i < 7; i++)
			GetSceneResource()->AddAnimationFrameData("GF_RIGHT", 6389, 3952.f, 699.f, 637.f);


	}

}

void CScene_GamePlay::LoadAnimationSequence_Daddy()
{
	// Daddy Animation
	{
		// DADDY_IDLE
		GetSceneResource()->CreateAnimationSequence("DADDY_IDLE", "DADDY_IDLE", TEXT("DADDY_DEAREST.bmp"));

		GetSceneResource()->SetTextureColorKey("DADDY_IDLE", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 1369.f, 730.f, 419.f, 767.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 1369.f, 730.f, 419.f, 767.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 3525.f, 0.f, 429.f, 759.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 3525.f, 0.f, 429.f, 759.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 0.f, 792.f, 424.f, 757.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 0.f, 792.f, 424.f, 757.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 3525.f, 759.f, 423.f, 759.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 3525.f, 759.f, 423.f, 759.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 424.f, 793.f, 419.f, 766.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 424.f, 793.f, 419.f, 766.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 1788.f, 735.f, 419.f, 767.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 1788.f, 735.f, 419.f, 767.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_IDLE", 1369.f, 730.f, 419.f, 767.f);


		// DADDY_UP
		GetSceneResource()->CreateAnimationSequence("DADDY_UP", "DADDY_UP", TEXT("DADDY_DEAREST.bmp"));

		GetSceneResource()->SetTextureColorKey("DADDY_UP", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("DADDY_UP", 2301.f, 0.f, 408.f, 818.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_UP", 2301.f, 0.f, 408.f, 818.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_UP", 2709.f, 0.f, 408.f, 810.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_UP", 2709.f, 0.f, 408.f, 810.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_UP", 3117.f, 0.f, 408.f, 810.f);


		// DADDY_DOWN
		GetSceneResource()->CreateAnimationSequence("DADDY_DOWN", "DADDY_DOWN", TEXT("DADDY_DEAREST.bmp"));

		GetSceneResource()->SetTextureColorKey("DADDY_DOWN", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("DADDY_DOWN", 1369.f, 0.f, 470.f, 730.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_DOWN", 1369.f, 0.f, 470.f, 730.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_DOWN", 1839.f, 0.f, 462.f, 735.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_DOWN", 1839.f, 0.f, 462.f, 735.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_DOWN", 1839.f, 0.f, 462.f, 735.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_DOWN", 1839.f, 0.f, 462.f, 735.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_DOWN", 1839.f, 0.f, 462.f, 735.f);


		// DADDY_LEFT
		GetSceneResource()->CreateAnimationSequence("DADDY_LEFT", "DADDY_LEFT", TEXT("DADDY_DEAREST.bmp"));

		GetSceneResource()->SetTextureColorKey("DADDY_LEFT", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("DADDY_LEFT", 843.f, 793.f, 370.f, 777.f);


		// DADDY_RIGHT
		GetSceneResource()->CreateAnimationSequence("DADDY_RIGHT", "DADDY_RIGHT", TEXT("DADDY_DEAREST.bmp"));

		GetSceneResource()->SetTextureColorKey("DADDY_RIGHT", 255, 0, 255);

		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 0.f, 0.f, 465.f, 792.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 0.f, 0.f, 465.f, 792.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 465.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 465.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 917.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 917.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 465.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 465.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 917.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 917.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 465.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 465.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 917.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 917.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 465.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 465.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 917.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 917.f, 0.f, 452.f, 793.f);
		GetSceneResource()->AddAnimationFrameData("DADDY_RIGHT", 465.f, 0.f, 452.f, 793.f);
	}
}

void CScene_GamePlay::LoadAnimationSequence_Mom()
{
	// Mom Animation
	{
		// MOM_IDLE
		GetSceneResource()->CreateAnimationSequence("MOM_IDLE", "MOM_IDLE", TEXT("Mom_Assets.bmp"));
		GetSceneResource()->SetTextureColorKey("MOM_IDLE", 255, 0, 255);

		for(int i = 0 ; i < 2; i ++)
			GetSceneResource()->AddAnimationFrameData("MOM_IDLE", 2072.f, 0.f, 386.f, 826.f);
		for(int i = 0 ; i < 2; i ++)
			GetSceneResource()->AddAnimationFrameData("MOM_IDLE", 2468.f, 0.f, 386.f, 815.f);
		for(int i = 0 ; i < 2; i ++)
			GetSceneResource()->AddAnimationFrameData("MOM_IDLE", 2864.f, 0.f, 386.f, 822.f);
		for(int i = 0 ; i < 2; i ++)
			GetSceneResource()->AddAnimationFrameData("MOM_IDLE", 3260.f, 0.f, 386.f, 824.f);
		for(int i = 0 ; i < 2; i ++)
			GetSceneResource()->AddAnimationFrameData("MOM_IDLE", 3656.f, 0.f, 386.f, 828.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_IDLE", 0.f, 838.f, 386.f, 829.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_IDLE", 396.f, 838.f, 386.f, 829.f);


		// MOM_UP
		GetSceneResource()->CreateAnimationSequence("MOM_UP", "MOM_UP", TEXT("Mom_Assets.bmp"));
		GetSceneResource()->SetTextureColorKey("MOM_UP", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_UP", 1722.f, 1677.f, 392.f, 846.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_UP", 2124.f, 1677.f, 388.f, 862.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_UP", 2522.f, 1677.f, 388.f, 861.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_UP", 2920.f, 1677.f, 388.f, 861.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_UP", 2522.f, 1677.f, 388.f, 861.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_UP", 2920.f, 1677.f, 388.f, 861.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_UP", 2522.f, 1677.f, 388.f, 861.f);

		GetSceneResource()->AddAnimationFrameData("MOM_UP", 2920.f, 1677.f, 388.f, 861.f);


		// MOM_DOWN
		GetSceneResource()->CreateAnimationSequence("MOM_DOWN", "MOM_DOWN", TEXT("Mom_Assets.bmp"));
		GetSceneResource()->SetTextureColorKey("MOM_DOWN", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_DOWN", 0.f, 0.f, 410.f, 613.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_DOWN", 420.f, 0.f, 403.f, 597.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_DOWN", 833.f, 0.f, 403.f, 600.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_DOWN", 1246.f, 0.f, 403.f, 600.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_DOWN", 833.f, 0.f, 403.f, 600.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_DOWN", 1246.f, 0.f, 403.f, 600.f);

		GetSceneResource()->AddAnimationFrameData("MOM_DOWN", 833.f, 0.f, 403.f, 600.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_DOWN", 1659.f, 0.f, 403.f, 600.f);


		// MOM_LEFT
		GetSceneResource()->CreateAnimationSequence("MOM_LEFT", "MOM_LEFT", TEXT("Mom_Assets.bmp"));
		GetSceneResource()->SetTextureColorKey("MOM_LEFT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_LEFT", 792.f, 838.f, 602.f, 818.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_LEFT", 1404.f, 838.f, 596.f, 803.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_LEFT", 2010.f, 838.f, 596.f, 807.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_LEFT", 2616.f, 838.f, 596.f, 807.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_LEFT", 2010.f, 838.f, 596.f, 807.f);


		// MOM_RIGHT
		GetSceneResource()->CreateAnimationSequence("MOM_RIGHT", "MOM_RIGHT", TEXT("Mom_Assets.bmp"));
		GetSceneResource()->SetTextureColorKey("MOM_RIGHT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_RIGHT", 3222.f, 838.f, 578.f, 771.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_RIGHT", 0.f, 1677.f, 564.f, 762.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_RIGHT", 574.f, 1677.f, 564.f, 764.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_RIGHT", 1148.f, 1677.f, 564.f, 764.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MOM_RIGHT", 574.f, 1677.f, 564.f, 764.f);
	}
}

void CScene_GamePlay::LoadAnimationSequence_Monster()
{
	// Monster Animation
	{
		// MONSTER_IDLE
		GetSceneResource()->CreateAnimationSequence("MONSTER_IDLE", "MONSTER_IDLE", TEXT("Monster_Assets.bmp"));
		GetSceneResource()->SetTextureColorKey("MONSTER_IDLE", 255, 0, 255);

		for (int i = 0; i < 2; i++) 
			GetSceneResource()->AddAnimationFrameData("MONSTER_IDLE", 1776.f, 1362.f, 424.f, 604.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_IDLE", 2210.f, 1362.f, 422.f, 605.f);

		GetSceneResource()->AddAnimationFrameData("MONSTER_IDLE", 2642.f, 1362.f, 439.f, 610.f);
		GetSceneResource()->AddAnimationFrameData("MONSTER_IDLE", 3091.f, 1362.f, 439.f, 630.f);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_IDLE", 3540.f, 1362.f, 481.f, 661.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_IDLE", 0.f, 2033.f, 484.f, 670.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_IDLE", 494.f, 2033.f, 484.f, 670.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_IDLE", 988.f, 2033.f, 484.f, 670.f);

		GetSceneResource()->AddAnimationFrameData("MONSTER_IDLE", 1482.f, 2033.f, 484.f, 670.f);


		// MONSTER_UP
		GetSceneResource()->CreateAnimationSequence("MONSTER_UP", "MONSTER_UP", TEXT("Monster_Assets.bmp"));
		GetSceneResource()->SetTextureColorKey("MONSTER_UP", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 1976.f, 2033.f, 410.f, 714.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 2396.f, 2033.f, 418.f, 711.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 2824.f, 2033.f, 418.f, 711.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 3252.f, 2033.f, 418.f, 711.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 0.f, 2757.f, 418.f, 711.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 428.f, 2757.f, 418.f, 711.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 856.f, 2757.f, 418.f, 711.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 2396.f, 2033.f, 418.f, 711.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 2824.f, 2033.f, 418.f, 711.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 3252.f, 2033.f, 418.f, 711.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 0.f, 2757.f, 418.f, 711.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_UP", 428.f, 2757.f, 418.f, 711.f);


		// MONSTER_DOWN
		GetSceneResource()->CreateAnimationSequence("MONSTER_DOWN", "MONSTER_DOWN", TEXT("Monster_Assets.bmp"));
		GetSceneResource()->SetTextureColorKey("MONSTER_DOWN", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", 2405.f, 684.f, 428.f, 599.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", 2843.f, 684.f, 434.f, 633.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", 3287.f, 684.f, 434.f, 633.f);
		for (int i = 0; i < 4; i++) {
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", i * 444.f, 1362.f, 434.f, 633.f);
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", i * 444.f, 1362.f, 434.f, 633.f);
		}
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", 2843.f, 684.f, 434.f, 633.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", 3287.f, 684.f, 434.f, 633.f);
		for (int i = 0; i < 4; i++) {
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", i * 444.f, 1362.f, 434.f, 633.f);
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", i * 444.f, 1362.f, 434.f, 633.f);
		}
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", 2843.f, 684.f, 434.f, 633.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_DOWN", 3287.f, 684.f, 434.f, 633.f);


		// MONSTER_LEFT
		GetSceneResource()->CreateAnimationSequence("MONSTER_LEFT", "MONSTER_LEFT", TEXT("Monster_Assets.bmp"));
		GetSceneResource()->SetTextureColorKey("MONSTER_LEFT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 2731.f, 0.f, 460.f, 671.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 3201.f, 0.f, 471.f, 668.f);
		for (int i = 0; i < 5; i++) {
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", i * 481.f, 684.f, 471.f, 668.f);
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", i * 481.f, 684.f, 471.f, 668.f);
		}
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 3201.f, 0.f, 471.f, 668.f);
		for (int i = 0; i < 2; i++) {
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", i * 481.f, 684.f, 471.f, 668.f);
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", i * 481.f, 684.f, 471.f, 668.f);
		}


		// MONSTER_RIGHT
		GetSceneResource()->CreateAnimationSequence("MONSTER_RIGHT", "MONSTER_RIGHT", TEXT("Monster_Assets.bmp"));
		GetSceneResource()->SetTextureColorKey("MONSTER_RIGHT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 0.f, 0.f, 375.f, 674.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 385.f, 0.f, 381.f, 671.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 776.f, 0.f, 381.f, 671.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 1167.f, 0.f, 381.f, 671.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 1558.f, 0.f, 381.f, 671.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 1949.f, 0.f, 381.f, 671.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 2340.f, 0.f, 381.f, 671.f);

		GetSceneResource()->AddAnimationFrameData("MONSTER_LEFT", 385.f, 0.f, 381.f, 671.f);
	}
}

void CScene_GamePlay::LoadAnimationSequence_Pico()
{
	// Pico Animation
	{
		// PICO_IDLE
		GetSceneResource()->CreateAnimationSequence("PICO_IDLE", "PICO_IDLE", TEXT("Pico_FNF_assetss.bmp"));
		GetSceneResource()->SetTextureColorKey("PICO_IDLE", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_IDLE", 2768.f, 0.f, 435.f, 461.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_IDLE", 3213.f, 0.f, 442.f, 468.f);
		
		GetSceneResource()->AddAnimationFrameData("PICO_IDLE", 0.f, 478.f, 448.f, 469.f);
		GetSceneResource()->AddAnimationFrameData("PICO_IDLE", 458.f, 478.f, 444.f, 469.f);
		GetSceneResource()->AddAnimationFrameData("PICO_IDLE", 912.f, 478.f, 444.f, 474.f);
		GetSceneResource()->AddAnimationFrameData("PICO_IDLE", 1366.f, 478.f, 442.f, 474.f);
		for (int i = 0; i < 6; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_IDLE", 1818.f, 478.f, 443.f, 475.f);


		// PICO_UP
		GetSceneResource()->CreateAnimationSequence("PICO_UP", "PICO_UP", TEXT("Pico_FNF_assetss.bmp"));
		GetSceneResource()->SetTextureColorKey("PICO_UP", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_UP", 455.f, 1495.f, 432.f, 495.f);
		for (int i = 0; i < 12; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_UP", 897.f, 1495.f, 432.f, 490.f);


		// PICO_DOWN
		GetSceneResource()->CreateAnimationSequence("PICO_DOWN", "PICO_DOWN", TEXT("Pico_FNF_assetss.bmp"));
		GetSceneResource()->SetTextureColorKey("PICO_DOWN", 255, 0, 255);

		for(int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_DOWN", 0.f, 0.f, 723.f, 382.f);
		for(int i = 0; i < 9; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_DOWN", 733.f, 0.f, 502.f, 392.f);


		// PICO_LEFT
		GetSceneResource()->CreateAnimationSequence("PICO_LEFT", "PICO_LEFT", TEXT("Pico_FNF_assetss.bmp"));
		GetSceneResource()->SetTextureColorKey("PICO_LEFT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_LEFT", 2271.f, 478.f, 449.f, 462.f);
		for (int i = 0; i < 15; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_LEFT", 2730.f, 478.f, 455.f, 464.f);


		// PICO_RIGHT
		GetSceneResource()->CreateAnimationSequence("PICO_RIGHT", "PICO_RIGHT", TEXT("Pico_FNF_assetss.bmp"));
		GetSceneResource()->SetTextureColorKey("PICO_RIGHT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_RIGHT", 1409.f, 963.f, 458.f, 476.f);
		for (int i = 0; i < 15; i++)
			GetSceneResource()->AddAnimationFrameData("PICO_RIGHT", 1877.f, 963.f, 442.f, 473.f);
	}
}

void CScene_GamePlay::LoadAnimationSequence_Spooky()
{
	// Spooky Animation
	{
		// SPOOKY_IDLE
		GetSceneResource()->CreateAnimationSequence("SPOOKY_IDLE", "SPOOKY_IDLE", TEXT("spooky_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SPOOKY_IDLE", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_IDLE", 2891.f, 0.f, 381.f, 549.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_IDLE", 3282.f, 0.f, 379.f, 541.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_IDLE", 3671.f, 0.f, 357.f, 484.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_IDLE", 0.f, 581.f, 354.f, 494.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_IDLE", 364.f, 581.f, 492.f, 532.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_IDLE", 866.f, 581.f, 481.f, 524.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_IDLE", 3671.f, 0.f, 357.f, 484.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_IDLE", 0.f, 581.f, 354.f, 494.f);


		// SPOOKY_UP
		GetSceneResource()->CreateAnimationSequence("SPOOKY_UP", "SPOOKY_UP", TEXT("spooky_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SPOOKY_UP", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_UP", 2066.f, 0.f, 399.f, 571.f);
		for (int i = 0; i < 3; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_UP", 2475.f, 0.f, 406.f, 566.f);


		// SPOOKY_DOWN
		GetSceneResource()->CreateAnimationSequence("SPOOKY_DOWN", "SPOOKY_DOWN", TEXT("spooky_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SPOOKY_DOWN", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_DOWN", 1135.f, 0.f, 463.f, 408.f);
		for (int i = 0; i < 23; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_DOWN", 1608.f, 0.f, 448.f, 409.f);


		// SPOOKY_LEFT
		GetSceneResource()->CreateAnimationSequence("SPOOKY_LEFT", "SPOOKY_LEFT", TEXT("spooky_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SPOOKY_LEFT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_LEFT", 0.f, 0.f, 556.f, 527.f);
		for (int i = 0; i < 13; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_LEFT", 566.f, 0.f, 559.f, 531.f);


		// SPOOKY_RIGHT
		GetSceneResource()->CreateAnimationSequence("SPOOKY_RIGHT", "SPOOKY_RIGHT", TEXT("spooky_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SPOOKY_RIGHT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_RIGHT", 1357.f, 581.f, 442.f, 524.f);
		for (int i = 0; i < 23; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_RIGHT", 1809.f, 581.f, 437.f, 533.f);
	}
}

void CScene_GamePlay::LoadAnimationSequence_Senpai()
{
	// Senpai Animation
	{
		// SENPAI_IDLE
		GetSceneResource()->CreateAnimationSequence("SENPAI_IDLE", "SENPAI_IDLE", TEXT("weeb/senpai.bmp"));
		GetSceneResource()->SetTextureColorKey("SENPAI_IDLE", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 810.f, 174.f, 124.f, 163.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 944.f, 174.f, 124.f, 163.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1078.f, 174.f, 124.f, 163.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1212.f, 174.f, 124.f, 163.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1346.f, 174.f, 124.f, 163.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1480.f, 174.f, 124.f, 163.f);
		
		GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1614.f, 174.f, 124.f, 163.f);
		GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1748.f, 174.f, 124.f, 163.f);
		GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1882.f, 174.f, 124.f, 163.f);

		for(int i = 0; i < 8; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 0.f + i * 134.f, 347.f, 124.f, 163.f);
		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1480.f, 174.f, 124.f, 163.f);

		GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1614.f, 174.f, 124.f, 163.f);
		GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1072.f, 347.f, 124.f, 163.f);
		GetSceneResource()->AddAnimationFrameData("SENPAI_IDLE", 1206.f, 347.f, 124.f, 163.f);


		// SENPAI_UP
		GetSceneResource()->CreateAnimationSequence("SENPAI_UP", "SENPAI_UP", TEXT("weeb/senpai.bmp"));
		GetSceneResource()->SetTextureColorKey("SENPAI_UP", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_UP", 540.f, 174.f, 125.f, 163.f);
		for (int i = 0; i < 12; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_UP", 675.f, 174.f, 125.f, 163.f);


		// SENPAI_DOWN
		GetSceneResource()->CreateAnimationSequence("SENPAI_DOWN", "SENPAI_DOWN", TEXT("weeb/senpai.bmp"));
		GetSceneResource()->SetTextureColorKey("SENPAI_DOWN", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_DOWN", 1755.f, 0.f, 125.f, 163.f);
		for (int i = 0; i < 12; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_DOWN", 1890.f, 0.f, 125.f, 163.f);


		// SENPAI_LEFT
		GetSceneResource()->CreateAnimationSequence("SENPAI_LEFT", "SENPAI_LEFT", TEXT("weeb/senpai.bmp"));
		GetSceneResource()->SetTextureColorKey("SENPAI_LEFT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_LEFT", 0.f, 174.f, 125.f, 163.f);
		for (int i = 0; i < 12; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_LEFT", 135.f, 174.f, 125.f, 163.f);


		// SENPAI_RIGHT
		GetSceneResource()->CreateAnimationSequence("SENPAI_RIGHT", "SENPAI_RIGHT", TEXT("SENPAI_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SENPAI_RIGHT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_RIGHT", 270.f, 174.f, 125.f, 163.f);
		for (int i = 0; i < 12; i++)
			GetSceneResource()->AddAnimationFrameData("SENPAI_RIGHT", 405.f, 174.f, 125.f, 163.f);
	}
}

void CScene_GamePlay::LoadAnimationSequence_Parents()
{
	// Spooky Animation
	{
		// SPOOKY_IDLE
		GetSceneResource()->CreateAnimationSequence("SPOOKY_IDLE", "SPOOKY_IDLE", TEXT("spooky_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SPOOKY_IDLE", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_IDLE", 2072.f, 0.f, 386.f, 826.f);


		// SPOOKY_UP
		GetSceneResource()->CreateAnimationSequence("SPOOKY_UP", "SPOOKY_UP", TEXT("spooky_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SPOOKY_UP", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_UP", 1722.f, 1677.f, 392.f, 846.f);


		// SPOOKY_DOWN
		GetSceneResource()->CreateAnimationSequence("SPOOKY_DOWN", "SPOOKY_DOWN", TEXT("spooky_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SPOOKY_DOWN", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_DOWN", 1135.f, 0.f, 463.f, 408.f);
		for (int i = 0; i < 23; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_DOWN", 1608.f, 0.f, 448.f, 409.f);


		// SPOOKY_LEFT
		GetSceneResource()->CreateAnimationSequence("SPOOKY_LEFT", "SPOOKY_LEFT", TEXT("spooky_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SPOOKY_LEFT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_LEFT", 0.f, 0.f, 556.f, 527.f);
		for (int i = 0; i < 13; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_LEFT", 566.f, 0.f, 559.f, 531.f);


		// SPOOKY_RIGHT
		GetSceneResource()->CreateAnimationSequence("SPOOKY_RIGHT", "SPOOKY_RIGHT", TEXT("spooky_kids_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("SPOOKY_RIGHT", 255, 0, 255);

		for (int i = 0; i < 2; i++)
			GetSceneResource()->AddAnimationFrameData("SPOOKY_RIGHT", 3222.f, 838.f, 578.f, 771.f);
	}
}

void CScene_GamePlay::LoadSound()
{
}

void CScene_GamePlay::LoadSong(const std::string Name)
{
	m_SongNameVoice = Name + "_Voice";
	m_SongNameInst = Name + "_Inst"; 
	std::string SongPathVoice = Name + "_Voices.ogg";
	std::string SongPathInst = Name + "_Inst.ogg";

	GetSceneResource()->LoadMusic("BGM", false, m_SongNameInst, SongPathInst.c_str());
	GetSceneResource()->LoadMusic("VOICE", false, m_SongNameVoice, SongPathVoice.c_str());

	GetSceneResource()->SetVolume("VOICE", 100);

	GetSceneResource()->LoadSound("UI", false, "intro3", "intro3.ogg");
	GetSceneResource()->LoadSound("UI", false, "intro2", "intro2.ogg");
	GetSceneResource()->LoadSound("UI", false, "intro1", "intro1.ogg");
	GetSceneResource()->LoadSound("UI", false, "introGo", "introGo.ogg");
}

void CScene_GamePlay::PlaySong()
{
	GetSceneResource()->SoundPlay(m_SongNameInst);
	GetSceneResource()->SoundPlay(m_SongNameVoice);
}

void CScene_GamePlay::ResumeSong()
{
	GetSceneResource()->SoundResume(m_SongNameInst);
	GetSceneResource()->SoundResume(m_SongNameVoice);
}

void CScene_GamePlay::PauseSong()
{
	GetSceneResource()->SoundPause(m_SongNameInst);
	GetSceneResource()->SoundPause(m_SongNameVoice);
}

void CScene_GamePlay::StopSong()
{
	GetSceneResource()->SoundStop(m_SongNameInst);
	GetSceneResource()->SoundStop(m_SongNameVoice);
}


bool CScene_GamePlay::SetSongInfo(const std::string& SongName, const ESong_Difficulty& Difficulty, bool IsStoryMode)
{
	m_NowSongName = SongName;
	m_NowSongDifficulty = Difficulty;
	m_IsStoryMode = IsStoryMode;

	SongInfo* Info = GetSceneResource()->FindSongData(m_NowSongName);

	if (Info == nullptr)
		return false;

	// Music Loading
	LoadSong(Info->SongName);


	// GamePlayWindow -> Notes Loading
	CUI_GamePlay* GamePlayWindow = CreateUIWindow<CUI_GamePlay>("GamePlayWindow");
	GamePlayWindow->SetSongInfo(*Info, m_NowSongDifficulty);

	std::list<NoteInfo> NotesList = Info->NotesList.find(m_NowSongDifficulty)->second;


	// Background Image Setting
	float	ScrollWidth = 1024.f - GetCamera()->GetResolution().x;
	float	ScrollHeight = 1024.f - GetCamera()->GetResolution().y;

	float	TileMapWidth = 2560.f - GetCamera()->GetResolution().x;
	float	TileMapHeight = 1440.f - GetCamera()->GetResolution().y;

	CScrollMap* Map = CreateMap<CScrollMap>("ScrollMap");
	Map->SetSize(2560.f, 1400.f);
	Map->SetZOrder(0);


	// Enemy Loading
	CCharacter* Character = nullptr;

	if (m_NowSongName == "Tutorial") {
		Info->EnemyName = "GF";
		Character = (CCharacter*)FindObject("GF");
		Character->SetPos(0.f, 150.f);

		Map->SetTexture("StageBack", TEXT("stageback3.bmp"));
		Map->SetSize(2560.f, 1400.f);
	} 
	else if (m_NowSongName == "Dadbattle" || m_NowSongName == "Bopeebo" || m_NowSongName == "Fresh") {
		Info->EnemyName = "Daddy";
		LoadAnimationSequence_Daddy();

		Character = CreateObject<CDaddy>(Info->EnemyName);
		Character->SetPos(30.f, 50.f);
		//Character->SetPos(630.f, 250.f);
		Character->SetNotes(NotesList);


		Map->SetTexture("StageBack", TEXT("stageback3.bmp"));
		Map->SetSize(2560.f, 1400.f);
	}
	else if (m_NowSongName == "Spookeez" || m_NowSongName == "South") {
		Info->EnemyName = "Spooky";
		LoadAnimationSequence_Spooky();

		Character = CreateObject<CSpooky>(Info->EnemyName);
		Character->SetPos(50.f, 250.f);
		//Character->SetPos(630.f, 250.f);
		Character->SetNotes(NotesList);

		Map->SetTexture("StageBack", TEXT("stageback3.bmp"));
		Map->SetSize(2560.f, 1400.f);
	}
	else if (m_NowSongName == "Pico" || m_NowSongName == "Philly" || m_NowSongName == "Blammed") {
		Info->EnemyName = "Pico";
		LoadAnimationSequence_Pico();

		Character = CreateObject<CPico>(Info->EnemyName);
		Character->SetPos(50.f, 350.f);
		//Character->SetPos(630.f, 250.f);
		Character->SetNotes(NotesList);


		Map->SetTexture("StageBack", TEXT("philly/City2.bmp"));
		Map->SetPos(-224.5f, -88.5f);
		Map->SetSize(1729.f, 955.f);

		Map = CreateMap<CScrollMap>("StageFront");
		Map->SetTexture("StageFront", TEXT("philly/street.bmp"));
		Map->SetTextureColorKey(255, 0, 255);
		Map->SetPos(-224.5f, -88.5f);
		Map->SetSize(1729.f, 955.f);
		Map->SetZOrder(5);

		CTrain* TrainMap = CreateMap<CTrain>("StageTrain");
		TrainMap->SetTexture("StageTrain", TEXT("philly/train.bmp"));
		TrainMap->SetTextureColorKey(255, 0, 255);
		TrainMap->SetPos(0.f, 221.f);
		TrainMap->SetSize(1089.f, 511.f);
		TrainMap->SetZOrder(2);
	}
	else if (m_NowSongName == "Satin-Panties" || m_NowSongName == "High" || m_NowSongName == "Milf") {
		Info->EnemyName = "Mom";
		LoadAnimationSequence_Mom();

		Character = CreateObject<CMom>(Info->EnemyName);
		Character->SetPos(30.f, 50.f);
		//Character->SetPos(630.f, 250.f);
		Character->SetNotes(NotesList);

		Map->SetTexture("StageBack", TEXT("limo/limoSunset.bmp"));
		Map->SetPos(-344.f, -88.5f);
		Map->SetSize(1968.f, 1313.f);

		Map = CreateMap<CScrollMap>("Back_Car");
		Map->SetTexture("Back_Car", TEXT("limo/Back_Car.bmp"));
		Map->SetTextureColorKey(255, 0, 255);
		Map->SetPos(-344.f, 300.f);
		Map->SetSize(2199.f, 379.f);
		Map->SetZOrder(3);

		Map = CreateMap<CScrollMap>("Front_Car");
		Map->SetTexture("Front_Car", TEXT("limo/Front_Car.bmp"));
		Map->SetTextureColorKey(255, 0, 255);
		Map->SetPos(-344.f, 300.f);
		Map->SetSize(2048.f, 646.f);
		Map->SetZOrder(5);
	}
	else if (m_NowSongName == "Cocoa" || m_NowSongName == "Eggnog" || m_NowSongName == "Winter-horrorland") {
		Info->EnemyName = "MomAndDad";
		LoadAnimationSequence_Parents();

		Character = CreateObject<CMomAndDad>(Info->EnemyName);
		Character->SetPos(30.f, 50.f);
		//Character->SetPos(630.f, 250.f);
		Character->SetNotes(NotesList);

		Map->SetTexture("StageBack", TEXT("christmas/Background.bmp"));
		Map->SetPos(-897.5f, -1000.f);
		Map->SetSize(3255.f, 1749.f);
	}
	else if (m_NowSongName == "Senpai" || m_NowSongName == "Roses" || m_NowSongName == "Thorns") {
		Info->EnemyName = "Senpai";
		LoadAnimationSequence_Senpai();

		Character = CreateObject<CSenpai>(Info->EnemyName);
		Character->SetPos(30.f, 50.f);
		//Character->SetPos(630.f, 250.f);
		Character->SetNotes(NotesList);
	}
	else {
		Info->EnemyName = "Monster";
		LoadAnimationSequence_Monster();

		Character = CreateObject<CMonster>(Info->EnemyName);
		Character->SetPos(30.f, 50.f);
		//Character->SetPos(630.f, 250.f);
		Character->SetNotes(NotesList);

		Map->SetTexture("StageBack", TEXT("christmas/EvilBackground.bmp"));
		Map->SetPos(-672.5f, -850.f);
		Map->SetSize(2625.f, 1613.f);
	}


	// Health Bar DataLoading
	CUI_HealthBar* HealthBarWindow = CreateUIWindow<CUI_HealthBar>("HealthBarWindow");
	HealthBarWindow->SetEnemy(Info->EnemyName);


	// Note End Point Setting
	CNote_EndPoint* NoteEndPoint = CreateObject<CNote_EndPoint>("NoteEndPoint_EnemyLeft");
	NoteEndPoint->SetInfo(ENote_Owner::Enemy, ENote_Type::Left);
	NoteEndPoint->SetCharacter(Character);
	NoteEndPoint = CreateObject<CNote_EndPoint>("NoteEndPoint_EnemyDown");
	NoteEndPoint->SetInfo(ENote_Owner::Enemy, ENote_Type::Down);
	NoteEndPoint->SetCharacter(Character);
	NoteEndPoint = CreateObject<CNote_EndPoint>("NoteEndPoint_EnemyUp");
	NoteEndPoint->SetInfo(ENote_Owner::Enemy, ENote_Type::Up);
	NoteEndPoint->SetCharacter(Character);
	NoteEndPoint = CreateObject<CNote_EndPoint>("NoteEndPoint_EnemyRight");
	NoteEndPoint->SetInfo(ENote_Owner::Enemy, ENote_Type::Right);
	NoteEndPoint->SetCharacter(Character);

	return true;
}

void CScene_GamePlay::ComboEffect(const ENote_Rate& Rate)
{
	float DirX = rand() % 2 == 0 ? 1.f : -1.f;
	float SpeedX = (float)(rand() % 301);

	if (m_NoteRate)
		m_NoteRate->Destroy();
	if (m_ComboFont)
		m_ComboFont->Destroy();

	m_NoteRate = CreateObject<CEffectTiming>("NoteRate", Vector2(1000.f, 350.f));
	m_NoteRate->SetNoteRate(Rate);
	m_NoteRate->SetDirX(DirX);
	m_NoteRate->SetSpeedX(SpeedX);

	if (Rate != ENote_Rate::Shit) {

		m_ComboFont = CreateObject<CComboFont>("Combofont", Vector2(1000.f, 400.f));
		m_ComboFont->SetComboNumber((int)m_Combo);
		m_ComboFont->SetDirX(DirX);
		m_ComboFont->SetSpeedX(SpeedX);;
	}
}

GameScore CScene_GamePlay::GameOver()
{
	StopSong();

	GameScore GC = GameScore(m_NowSongName, m_NowSongDifficulty, m_Score, m_NoteMissCount, m_MaxCombo);

	return GC;
}

GameScore CScene_GamePlay::GameEnd()
{
	StopSong();

	EGame_Rate Rate = EGame_Rate::Meh;

	if (m_Rating >= 95.f)
		Rate = EGame_Rate::Great;
	else if (m_Rating >= 90.f)
		Rate = EGame_Rate::Sick;
	else if (m_Rating >= 70.f)
		Rate = EGame_Rate::Good;

	GameScore GC = GameScore(m_NowSongName, m_NowSongDifficulty, m_Score, m_NoteMissCount, m_MaxCombo, Rate);
	
	return GC;
}

void CScene_GamePlay::EnterPressed()
{
	m_IsGameStop = !m_IsGameStop;

	if (m_IsGameStop)
	{
		PauseSong();
		FindUIWindow<CUI_GamePlay>("GamePlayWindow")->SetPause();
	}
	else {
		ResumeSong();
		FindUIWindow<CUI_GamePlay>("GamePlayWindow")->SetResume();
	}
}