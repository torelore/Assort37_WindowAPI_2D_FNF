
#include "Scene_ModeSelect.h"
#include "../Camera.h"
#include "../SceneResource.h"
#include "../../UI/Scene/UI_ModeSelect.h"
#include "../../Object/Text/Button_StoryMode.h"
#include "../../Object/Text/Button_FreePlay.h"
#include "../../Object/Text/Button_Option.h"
#include "../../GameManager.h"
#include "../../Map/ScrollMap.h"

CScene_ModeSelect::CScene_ModeSelect()
{
}

CScene_ModeSelect::~CScene_ModeSelect()
{

}

bool CScene_ModeSelect::Init()
{
	LoadSound();

	LoadAnimationSequence();

	float WhiteSpace = 50.f;

	// Button Setting
	CButton_StoryMode* StoryModeButton = CreateObject<CButton_StoryMode>("StoryModeButton");

	StoryModeButton->SetPos(320.f - StoryModeButton->GetBottom() / 2.f, WhiteSpace);
	StoryModeButton->SetIsSelected(true);

	m_vecMenuButton.push_back(StoryModeButton);


	CButton_FreePlay* FreePlayButton = CreateObject<CButton_FreePlay>("FreePlayButton");

	FreePlayButton->SetPos(320.f - FreePlayButton->GetBottom() / 2.f, WhiteSpace * 2 + 150.f);

	m_vecMenuButton.push_back(FreePlayButton);


	//CButton_Option* OptionButton = CreateObject<CButton_Option>("OptionButton");

	//OptionButton->SetPos(320.f - OptionButton->GetBottom() / 2.f, WhiteSpace * 3 + 300.f);

	//m_vecMenuButton.push_back(OptionButton);


	// Background Image Setting
	CScrollMap* Map = CreateMap<CScrollMap>("ModeSelectBack");

	Map->SetSize(1536.f, 864.f);
	Map->SetTexture("ModeSelectBackGround", TEXT("menuBG.bmp"));
	Map->SetZOrder(0);

	return true;
}

void CScene_ModeSelect::LoadAnimationSequence()
{
	// Story Mode(Black) Button
	GetSceneResource()->CreateAnimationSequence("STORY_MODE_BASIC", "STORY_MODE_BASIC", TEXT("FNF_main_menu_assets.bmp"));

	GetSceneResource()->SetTextureColorKey("STORY_MODE_BASIC", 255, 0, 255);

	GetSceneResource()->AddAnimationFrameData("STORY_MODE_BASIC", 1237.f, 859.f, 615.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("STORY_MODE_BASIC", 1237.f, 859.f, 615.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("STORY_MODE_BASIC", 1237.f, 859.f, 615.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("STORY_MODE_BASIC", 0.f, 1032.f, 615.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("STORY_MODE_BASIC", 0.f, 1032.f, 615.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("STORY_MODE_BASIC", 0.f, 1032.f, 615.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("STORY_MODE_BASIC", 625.f, 1032.f, 615.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("STORY_MODE_BASIC", 625.f, 1032.f, 615.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("STORY_MODE_BASIC", 625.f, 1032.f, 615.f, 122.f);


	// Story Mode(White) Button
	GetSceneResource()->CreateAnimationSequence("STORY_MODE_WHITE", "STORY_MODE_WHITE", TEXT("FNF_main_menu_assets.bmp"));

	GetSceneResource()->SetTextureColorKey("STORY_MODE_WHITE", 255, 0, 255);

	GetSceneResource()->AddAnimationFrameData("STORY_MODE_WHITE", 1250.f, 1032.f, 796.f, 173.f);
	GetSceneResource()->AddAnimationFrameData("STORY_MODE_WHITE", 0.f, 1215.f, 794.f, 174.f);
	GetSceneResource()->AddAnimationFrameData("STORY_MODE_WHITE", 804.f, 1215.f, 794.f, 181.f);


	// Free Play(Black) Button
	GetSceneResource()->CreateAnimationSequence("FREE_PLAY_BASIC", "FREE_PLAY_BASIC", TEXT("FNF_main_menu_assets.bmp"));

	GetSceneResource()->SetTextureColorKey("FREE_PLAY_BASIC", 255, 0, 255);

	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_BASIC", 1192.f, 167.f, 484.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_BASIC", 1192.f, 167.f, 484.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_BASIC", 1192.f, 167.f, 484.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_BASIC", 0.f, 332.f, 484.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_BASIC", 0.f, 332.f, 484.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_BASIC", 0.f, 332.f, 484.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_BASIC", 494.f, 332.f, 484.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_BASIC", 494.f, 332.f, 484.f, 122.f);
	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_BASIC", 494.f, 332.f, 484.f, 122.f);


	// Free Play(White) Button
	GetSceneResource()->CreateAnimationSequence("FREE_PLAY_WHITE", "FREE_PLAY_WHITE", TEXT("FNF_main_menu_assets.bmp"));

	GetSceneResource()->SetTextureColorKey("FREE_PLAY_WHITE", 255, 0, 255);

	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_WHITE", 988.f, 332.f, 627.f, 169.f);
	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_WHITE", 0.f, 511.f, 632.f, 170.f);
	GetSceneResource()->AddAnimationFrameData("FREE_PLAY_WHITE", 642.f, 511.f, 629.f, 173.f);


	// Option(Black) Button
	GetSceneResource()->CreateAnimationSequence("OPTION_BASIC", "OPTION_BASIC", TEXT("FNF_main_menu_assets.bmp"));

	GetSceneResource()->SetTextureColorKey("OPTION_BASIC", 255, 0, 255);

	GetSceneResource()->AddAnimationFrameData("OPTION_BASIC", 1281.f, 511.f, 487.f, 111.f);
	GetSceneResource()->AddAnimationFrameData("OPTION_BASIC", 1281.f, 511.f, 487.f, 111.f);
	GetSceneResource()->AddAnimationFrameData("OPTION_BASIC", 1281.f, 511.f, 487.f, 111.f);
	GetSceneResource()->AddAnimationFrameData("OPTION_BASIC", 0.f, 694.f, 487.f, 111.f);
	GetSceneResource()->AddAnimationFrameData("OPTION_BASIC", 0.f, 694.f, 487.f, 111.f);
	GetSceneResource()->AddAnimationFrameData("OPTION_BASIC", 0.f, 694.f, 487.f, 111.f);
	GetSceneResource()->AddAnimationFrameData("OPTION_BASIC", 497.f, 694.f, 487.f, 111.f);


	// Option(White) Button
	GetSceneResource()->CreateAnimationSequence("OPTION_WHITE", "OPTION_WHITE", TEXT("FNF_main_menu_assets.bmp"));

	GetSceneResource()->SetTextureColorKey("OPTION_WHITE", 255, 0, 255);

	GetSceneResource()->AddAnimationFrameData("OPTION_WHITE", 994.f, 694.f, 606.f, 155.f);
	GetSceneResource()->AddAnimationFrameData("OPTION_WHITE", 0.f, 859.f, 607.f, 158.f);
	GetSceneResource()->AddAnimationFrameData("OPTION_WHITE", 617.f, 859.f, 610.f, 163.f);
}

void CScene_ModeSelect::LoadSound()
{
	GetSceneResource()->LoadMusic("BGM", true, "StartBGM", "freakyMenu.ogg");

	GetSceneResource()->LoadSound("UI", false, "ConfimMenu", "confirmMenu.ogg");
	GetSceneResource()->LoadSound("UI", false, "ScrollMenu", "scrollMenu.ogg");
}

void CScene_ModeSelect::EnterPressed()
{
	float Time = m_vecMenuButton[0]->GetLastChangeTime();

	if (Time < 0.5f)
		return;

	size_t Size = m_vecMenuButton.size();

	for (int i = 0; i < Size; i++) {
		if (m_vecMenuButton[i]->IsSelected()) {
			GetSceneResource()->SoundStop("StartBGM");
			GetSceneResource()->SoundPlay("ConfimMenu");

			m_vecMenuButton[i]->ButtonScene(Time);

			break;
		}
	}
}

void CScene_ModeSelect::UpPressed()
{
	GetSceneResource()->SoundPlay("ScrollMenu");

	size_t Size = m_vecMenuButton.size();

	int SelectedNum = 0;

	for (int i = 0; i < Size; i++) {
		if (m_vecMenuButton[i]->IsSelected()) {
			SelectedNum = i;
			break;
		}
	}

	if (SelectedNum == 0)
		SelectedNum = (int)Size - 1;
	else
		SelectedNum--;

	for (int i = 0; i < Size; i++) {
		if (SelectedNum == i)
			m_vecMenuButton[i]->SetIsSelected(true);
		else 
			m_vecMenuButton[i]->SetIsSelected(false);
	}
}

void CScene_ModeSelect::DownPressed()
{
	GetSceneResource()->SoundPlay("ScrollMenu");

	size_t Size = m_vecMenuButton.size();

	int SelectedNum = 0;

	for (int i = 0; i < Size; i++) {
		if (m_vecMenuButton[i]->IsSelected()) {
			SelectedNum = i;
			break;
		}
	}

	if (SelectedNum == Size - 1)
		SelectedNum = 0;
	else
		SelectedNum++;

	for (int i = 0; i < Size; i++) {
		if (SelectedNum == i)
			m_vecMenuButton[i]->SetIsSelected(true);
		else
			m_vecMenuButton[i]->SetIsSelected(false);
	}
}


