#include "Scene_FreePlay.h"
#include "../../GameManager.h"
#include "../SceneResource.h"
#include "../../Resource/ResourceManager.h"
#include "../../Map/ScrollMap.h"
#include "../../Object/Text/Button_Difficulty.h"
#include "../../UI/Scene/UI_FreePlay.h"
#include "Scene_GamePlay.h"
#include "../SceneManager.h"

CScene_FreePlay::CScene_FreePlay() : 
	m_SongDifficuly(ESong_Difficulty::Normal),
	LeftArrow(nullptr),
	RightArrow(nullptr)
{
}

CScene_FreePlay::~CScene_FreePlay()
{
}

bool CScene_FreePlay::Init()
{
	Resolution	RS = CGameManager::GetInst()->GetResolution();


	// 곡 목록 가져오기
	m_vecSongName = CResourceManager::GetInst()->GetAllSongName();

	LoadAnimationSequence();
	LoadSound();

	// 가져온 곡 목록을 Text UI로 표현 및 Score 세팅
	size_t Size = m_vecSongName.size();
	CUI_FreePlay* FreePlayWindow = CreateUIWindow<CUI_FreePlay>("FreePlayWindow");

	for (size_t i = 0; i < Size; i++) {
		FreePlayWindow->AddVecTextWidget(m_vecSongName[i]);
	}


	// 난이도 세팅
	// 우측 상단에 Easy, Normal, Hard 난이도 세팅하기.
	// 첫 번째 버튼에 좌(MoveLeft)와 우(MoveRight) Input 콜백을 통해 난이도 변경을 할 수 있게끔 세팅
	CButton_Difficulty* Difficulty = CreateObject<CButton_Difficulty>("FreePlayDifficulty");
	Difficulty->SetPos(RS.Width - 430.f, 110.f);
	Difficulty->SetSongDifficulty(m_SongDifficuly);

	RightArrow = CreateObject<CButton_Diffi_Arrow>("FreePlayDifficultyRightArrow");
	RightArrow->SetIsRight();
	RightArrow->SetPos(RS.Width - 100.f, 100.f);

	LeftArrow = CreateObject<CButton_Diffi_Arrow>("FreePlayDifficultyLeftArrow");
	LeftArrow->SetIsLeft();
	LeftArrow->SetPos(RS.Width - 500.f, 100.f);


	// Background Image Setting
	CScrollMap* Map = CreateMap<CScrollMap>("FreePlayBack");

	Map->SetSize(1536.f, 864.f);
	Map->SetTexture("FreePlayBackGround", TEXT("menuBGBlue.bmp"));
	Map->SetZOrder(0);


	return true;
}

void CScene_FreePlay::LoadAnimationSequence()
{
	// UI
	{
		// EASY
		GetSceneResource()->CreateAnimationSequence("EASY", "EASY", TEXT("campaign_menu_UI_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("EASY", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("EASY", 0.f, 0.f, 196.f, 65.f);


		// NORMAL
		GetSceneResource()->CreateAnimationSequence("NORMAL", "NORMAL", TEXT("campaign_menu_UI_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("NORMAL", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("NORMAL", 427.f, 0.f, 308.f, 67.f);


		// HARD
		GetSceneResource()->CreateAnimationSequence("HARD", "HARD", TEXT("campaign_menu_UI_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("HARD", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("HARD", 206.f, 0.f, 211.f, 67.f);


		// LEFT_ARROW
		GetSceneResource()->CreateAnimationSequence("LEFT_ARROW", "LEFT_ARROW", TEXT("campaign_menu_UI_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("LEFT_ARROW", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("LEFT_ARROW", 738.f, 374.f, 48.f, 85.f);


		// LEFT_ARROW_PUSH
		GetSceneResource()->CreateAnimationSequence("LEFT_ARROW_PUSH", "LEFT_ARROW_PUSH", TEXT("campaign_menu_UI_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("LEFT_ARROW_PUSH", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("LEFT_ARROW_PUSH", 796.f, 374.f, 42.f, 75.f);


		// RIGHT_ARROW
		GetSceneResource()->CreateAnimationSequence("RIGHT_ARROW", "RIGHT_ARROW", TEXT("campaign_menu_UI_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("RIGHT_ARROW", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("RIGHT_ARROW", 899.f, 374.f, 47.f, 85.f);


		// RIGHT_ARROW_PUSH
		GetSceneResource()->CreateAnimationSequence("RIGHT_ARROW_PUSH", "RIGHT_ARROW_PUSH", TEXT("campaign_menu_UI_assets.bmp"));
		GetSceneResource()->SetTextureColorKey("RIGHT_ARROW_PUSH", 255, 0, 255);
		GetSceneResource()->AddAnimationFrameData("RIGHT_ARROW_PUSH", 848.f, 374.f, 41.f, 74.f);
	}
}

void CScene_FreePlay::LoadSound()
{
	{
		size_t Size = m_vecSongName.size();

		for (size_t i = 0; i < Size; i++) {
			std::string FileName = m_vecSongName[i] + "_Inst.ogg";

			GetSceneResource()->LoadMusic("BGM", true, m_vecSongName[i], FileName.c_str());

			if (i == 0)
				GetSceneResource()->SoundPlay(m_vecSongName[i]);
		}
	}

	{
		GetSceneResource()->LoadSound("UI", false, "ScrollMenu", "scrollMenu.ogg");
		GetSceneResource()->LoadSound("UI", false, "ConfimMenu", "confirmMenu.ogg");
	}
}

void CScene_FreePlay::EnterPressed()
{
	size_t Size = m_vecSongName.size();
	CUI_FreePlay* FreePlayWindow = FindUIWindow<CUI_FreePlay>("FreePlayWindow");

	GetSceneResource()->SoundPlay("ConfimMenu");

	size_t NowSelected = FreePlayWindow->GetNowSelectedSongNum();
	GetSceneResource()->SoundStop(m_vecSongName[NowSelected]);

	CSceneManager::GetInst()->CreateScene<CScene_GamePlay>(m_vecSongName[NowSelected], m_SongDifficuly);
}

void CScene_FreePlay::UpPressed(float DeltaTime)
{
	size_t Size = m_vecSongName.size();
	CUI_FreePlay* FreePlayWindow = FindUIWindow<CUI_FreePlay>("FreePlayWindow");

	GetSceneResource()->SoundPlay("ScrollMenu");

	size_t NowSelected = FreePlayWindow->GetNowSelectedSongNum();
	GetSceneResource()->SoundStop(m_vecSongName[NowSelected]);


	Vector2 Pos = Vector2(FreePlayWindow->GetWhiteSpace().x + UI_FREEPLAY_SONG_MOVE_X, FreePlayWindow->GetWhiteSpace().y + UI_FREEPLAY_SONG_MOVE_Y);
	NowSelected--;

	if (FreePlayWindow->GetNowSelectedSongNum() == 0) {
		Pos.x = UI_FREEPLAY_SONG_X + (-UI_FREEPLAY_SONG_MOVE_X * (Size - 1));
		Pos.y = UI_FREEPLAY_SONG_Y + (-UI_FREEPLAY_SONG_MOVE_Y * (Size - 1));
		NowSelected = Size - 1;
	}

	GetSceneResource()->SoundPlay(m_vecSongName[NowSelected]);
	FreePlayWindow->SetWhiteSpace(Pos);
}

void CScene_FreePlay::DownPressed(float DeltaTime)
{
	size_t Size = m_vecSongName.size();
	CUI_FreePlay* FreePlayWindow = FindUIWindow<CUI_FreePlay>("FreePlayWindow");

	GetSceneResource()->SoundPlay("ScrollMenu");

	size_t NowSelected = FreePlayWindow->GetNowSelectedSongNum();
	GetSceneResource()->SoundStop(m_vecSongName[NowSelected]);

	Vector2 Pos = Vector2(FreePlayWindow->GetWhiteSpace().x - UI_FREEPLAY_SONG_MOVE_X, FreePlayWindow->GetWhiteSpace().y - UI_FREEPLAY_SONG_MOVE_Y);
	NowSelected++;

	if (FreePlayWindow->GetNowSelectedSongNum() == Size - 1) {
		Pos.x = UI_FREEPLAY_SONG_X;
		Pos.y = UI_FREEPLAY_SONG_Y;
		NowSelected = 0;
	}

	GetSceneResource()->SoundPlay(m_vecSongName[NowSelected]);
	FreePlayWindow->SetWhiteSpace(Pos);
}

void CScene_FreePlay::LeftPressed(float DeltaTime)
{
	GetSceneResource()->SoundPlay("ScrollMenu");
	LeftArrow->LeftPressed(DeltaTime);
}

void CScene_FreePlay::RightPressed(float DeltaTime)
{
	GetSceneResource()->SoundPlay("ScrollMenu");
	RightArrow->RightPressed(DeltaTime);
}
