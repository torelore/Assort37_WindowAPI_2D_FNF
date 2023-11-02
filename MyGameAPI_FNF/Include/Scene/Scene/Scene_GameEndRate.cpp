#include "Scene_GameEndRate.h"
#include "../SceneResource.h"
#include "../../UI/Scene/UI_GameEndRate.h"
#include "../../Map/ScrollMap.h"
#include "../../Object/Characters/GirlFriend_End.h"


CScene_GameEndRate::CScene_GameEndRate()
{
}

CScene_GameEndRate::~CScene_GameEndRate()
{
}

bool CScene_GameEndRate::Init()
{
    LoadAnimationSequence();


    CScrollMap* Background = CreateMap<CScrollMap>("BackGround");
    Background->SetTexture("BackGround", TEXT("Back.bmp"));
    Background->SetPos(0.f, 0.f);
    Background->SetSize(1280.f, 720.f);


    return true;
}

void CScene_GameEndRate::LoadAnimationSequence()
{
    // GF
    {
        // GF_CHEER
        GetSceneResource()->CreateAnimationSequence("GF_CHEER", "GF_CHEER", TEXT("GF_assets.bmp"));
        GetSceneResource()->SetTextureColorKey("GF_CHEER", 255, 0, 255);

        GetSceneResource()->AddAnimationFrameData("GF_CHEER", 0.f, 0.f, 699.f, 657.f);
        GetSceneResource()->AddAnimationFrameData("GF_CHEER", 709.f, 0.f, 703.f, 657.f);
        GetSceneResource()->AddAnimationFrameData("GF_CHEER", 1422.f, 0.f, 703.f, 654.f);
        GetSceneResource()->AddAnimationFrameData("GF_CHEER", 2135.f, 0.f, 699.f, 654.f);
        for(int i = 0; i < 17; i++)
            GetSceneResource()->AddAnimationFrameData("GF_CHEER", 2844.f, 0.f, 699.f, 654.f);


        // GF_SAD
        GetSceneResource()->CreateAnimationSequence("GF_SAD", "GF_SAD", TEXT("GF_assets.bmp"));
        GetSceneResource()->SetTextureColorKey("GF_SAD", 255, 0, 255);

        for (int i = 0; i < 2; i++)
            GetSceneResource()->AddAnimationFrameData("GF_SAD", 709.f, 5294.f, 699.f, 633.f);

        for (int k = 0; k < 9; k++) {
            for (int i = 1; i < 5; i++) {
                for (int j = 0; j < 2; j++)
                    GetSceneResource()->AddAnimationFrameData("GF_SAD", 709.f + i * 709.f, 5294.f, 699.f, 636.f);
            }
        }

        for (int i = 1; i < 4; i++) {
            for (int j = 0; j < 2; j++)
                GetSceneResource()->AddAnimationFrameData("GF_SAD", 709.f + i * 709.f, 5294.f, 699.f, 636.f);
        }
    }

    // BF
    {
        // BF_V
        GetSceneResource()->CreateAnimationSequence("GF_CHEER", "GF_CHEER", TEXT("GF_assets.bmp"));
        GetSceneResource()->SetTextureColorKey("GF_CHEER", 255, 0, 255);

    }
}

bool CScene_GameEndRate::SetGameRate(const GameScore& GameScore)
{
    CUI_GameEndRate* GameEndRateWindow = CreateUIWindow<CUI_GameEndRate>("GameEndRateWindow");

    GameEndRateWindow->SetGameRate(GameScore);

    CGirlFriend_End* GF = CreateObject<CGirlFriend_End>("GF_END");
    GF->SetPos(-100.f, 50.f);

    bool IsCleared = true;

    if (GameScore.Rate == EGame_Rate::Failed)
        IsCleared = false;

    GF->SetAnimationCleared(IsCleared);

    return true;
}

void CScene_GameEndRate::IsStoryMode()
{
    CUI_GameEndRate* GameEndRateWindow = CreateUIWindow<CUI_GameEndRate>("GameEndRateWindow");
    GameEndRateWindow->SetIsStroyMode();
}
