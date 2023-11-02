#include "Scene_Start.h"
#include "../SceneResource.h"
#include "../../UI/Scene/UI_StartScene.h"
#include "../../Object/Characters/GirlFriend_Title.h"
#include "../../Object/Text/LogoBumpin.h"
#include "../../Object/Text/Button_PressEnter.h"
#include "../../GameManager.h"
#include "../../Map/ScrollMap.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

bool CScene_Start::Init()
{
	LoadSound();

	LoadAnimationSequence();

	Resolution	RS = CGameManager::GetInst()->GetResolution();

	CScrollMap* Map = CreateMap<CScrollMap>("ScrollMap");

	Map->SetSize(1280.f, 720.f);
	Map->SetTexture("Back", TEXT("Back.bmp"));
	Map->SetZOrder(0);

	CButton_PressEnter* PressEnterButton = CreateObject<CButton_PressEnter>("PressEnterButton");
	CGirlFriend_Title* GirlFriend = CreateObject<CGirlFriend_Title>("GirlFriend");
	CLogoBumpin* LogoBumpin = CreateObject<CLogoBumpin>("LogoBumpin");

	CUI_StartScene* StartWindow = CreateUIWindow<CUI_StartScene>("StartWindow");

	return true;
}

void CScene_Start::LoadAnimationSequence()
{
	// GF Dance Title
	GetSceneResource()->CreateAnimationSequence("GF_DANCE_TITLE", "GF_DANCE_TITLE", TEXT("gfDanceTitle.bmp"));

	GetSceneResource()->SetTextureColorKey("GF_DANCE_TITLE", 255, 0, 255);

	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 0.f, 0.f, 717.f, 648.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 727.f, 0.f, 721.f, 648.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 1458.f, 0.f, 721.f, 646.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2189.f, 0.f, 717.f, 646.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2916.f, 0.f, 717.f, 649.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 0.f, 659.f, 717.f, 649.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 727.f, 659.f, 721.f, 650.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 1454.f, 659.f, 721.f, 661.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 1454.f, 659.f, 721.f, 661.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 1454.f, 659.f, 721.f, 661.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2181.f, 659.f, 721.f, 662.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2181.f, 659.f, 721.f, 662.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2181.f, 659.f, 721.f, 662.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2908.f, 659.f, 721.f, 661.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2908.f, 659.f, 721.f, 661.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 0.f, 1331.f, 717.f, 650.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 727.f, 1331.f, 721.f, 650.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 1458.f, 1331.f, 721.f, 650.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2189.f, 1331.f, 717.f, 650.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2916.f, 1331.f, 717.f, 651.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 0.f, 1992.f, 717.f, 651.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 727.f, 1992.f, 721.f, 652.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 1454.f, 1992.f, 721.f, 657.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 1454.f, 1992.f, 721.f, 657.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 1454.f, 1992.f, 721.f, 657.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2181.f, 1992.f, 721.f, 656.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2181.f, 1992.f, 721.f, 656.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2181.f, 1992.f, 721.f, 656.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2908.f, 1992.f, 721.f, 656.f);
	GetSceneResource()->AddAnimationFrameData("GF_DANCE_TITLE", 2908.f, 1992.f, 721.f, 656.f);


	// Press Enter to Begin
	GetSceneResource()->CreateAnimationSequence("PRESS_ENTER_TO_BEGIN", "PRESS_ENTER_TO_BEGIN", TEXT("titleEnter.bmp"));

	GetSceneResource()->SetTextureColorKey("PRESS_ENTER_TO_BEGIN", 255, 255, 255);

	for (int i = 0; i < 21; i++) {
		GetSceneResource()->AddAnimationFrameData("PRESS_ENTER_TO_BEGIN", 0.f, 89.f + (i * 106.f), 1495.f, 96.f);
	}


	// Press Enter Pressed
	GetSceneResource()->CreateAnimationSequence("PRESS_ENTERED", "PRESS_ENTERED", TEXT("titleEnter.bmp"));

	GetSceneResource()->SetTextureColorKey("PRESS_ENTERED", 255, 0, 255);

	GetSceneResource()->AddAnimationFrameData("PRESS_ENTERED", 0.f, 0.f, 1477.f, 79.f);
	GetSceneResource()->AddAnimationFrameData("PRESS_ENTERED", 1487.f, 0.f, 1477.f, 79.f);
	GetSceneResource()->AddAnimationFrameData("PRESS_ENTERED", 0.f, 0.f, 1477.f, 79.f);
	GetSceneResource()->AddAnimationFrameData("PRESS_ENTERED", 1487.f, 0.f, 1477.f, 79.f);
	GetSceneResource()->AddAnimationFrameData("PRESS_ENTERED", 0.f, 0.f, 1477.f, 79.f);
	GetSceneResource()->AddAnimationFrameData("PRESS_ENTERED", 1487.f, 0.f, 1477.f, 79.f);
	GetSceneResource()->AddAnimationFrameData("PRESS_ENTERED", 1487.f, 0.f, 1477.f, 79.f);
	GetSceneResource()->AddAnimationFrameData("PRESS_ENTERED", 0.f, 0.f, 1477.f, 79.f);
	GetSceneResource()->AddAnimationFrameData("PRESS_ENTERED", 1487.f, 0.f, 1477.f, 79.f);


	// LOGO Bumping
	GetSceneResource()->CreateAnimationSequence("LOGO_BUMFIN", "LOGO_BUMFIN", TEXT("logoBumpin.bmp"));

	GetSceneResource()->SetTextureColorKey("LOGO_BUMFIN", 255, 0, 255);

	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 0.f, 0.f, 894.f, 670.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 904.f, 0.f, 939.f, 703.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 904.f, 0.f, 939.f, 703.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 0.f, 713.f, 911.f, 683.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 0.f, 713.f, 911.f, 683.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 921.f, 713.f, 905.f, 679.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 921.f, 713.f, 905.f, 679.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 921.f, 713.f, 905.f, 679.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 921.f, 713.f, 905.f, 679.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 921.f, 713.f, 905.f, 679.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 921.f, 713.f, 905.f, 679.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 921.f, 713.f, 905.f, 679.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 921.f, 713.f, 905.f, 679.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 921.f, 713.f, 905.f, 679.f);
	GetSceneResource()->AddAnimationFrameData("LOGO_BUMFIN", 921.f, 713.f, 905.f, 679.f);
}

void CScene_Start::LoadSound()
{
	GetSceneResource()->LoadMusic("BGM", true, "StartBGM", "freakyMenu.ogg");
	GetSceneResource()->SoundPlay("StartBGM");

	GetSceneResource()->LoadSound("UI", false, "ConfimMenu", "confimMenu.ogg");
}
