#include "UI_StartScene.h"
#include "../UIImage.h"
#include "../Button.h"
#include "../../GameManager.h"
#include "../../Scene/Scene/Scene_ModeSelect.h"
#include "../../Scene/SceneManager.h"

CUI_StartScene::CUI_StartScene()
{
}

CUI_StartScene::~CUI_StartScene()
{
}

bool CUI_StartScene::Init()
{

	return true;
}

void CUI_StartScene::EnterPressed()
{
	CSceneManager::GetInst()->CreateScene<CScene_ModeSelect>();
}
