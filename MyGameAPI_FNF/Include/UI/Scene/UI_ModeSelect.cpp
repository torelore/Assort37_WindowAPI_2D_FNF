#include "UI_ModeSelect.h"
#include "../UIImage.h"
#include "../../GameManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/SceneResource.h"
#include "../Button.h"
#include "../../Object/Text/Button_StoryMode.h"
#include "../../Object/Text/Button_FreePlay.h"
#include "../../Object/Text/Button_Option.h"

CUI_ModeSelect::CUI_ModeSelect()
{
}

CUI_ModeSelect::~CUI_ModeSelect()
{
}

bool CUI_ModeSelect::Init()
{

	return true;
}

void CUI_ModeSelect::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);
}