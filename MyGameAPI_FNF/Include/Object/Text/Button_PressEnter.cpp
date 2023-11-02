#include "Button_PressEnter.h"
#include "../../Input.h"
#include "../../UI/Scene/UI_StartScene.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene/Scene_ModeSelect.h"

CButton_PressEnter::CButton_PressEnter()
{
}

CButton_PressEnter::CButton_PressEnter(const CButton_PressEnter& obj)
{
}

CButton_PressEnter::~CButton_PressEnter()
{
}

void CButton_PressEnter::Start()
{
	CGameObject::Start();

	CInput::GetInst()->SetCallback<CButton_PressEnter>("Enter", KeyState_Down, this, &CButton_PressEnter::EnterPressed);
}

bool CButton_PressEnter::Init()
{
	if (!CGameObject::Init())
		return false;

	SetPos(100.f, 600.f);

	CreateAnimation();
	AddAnimation("PRESS_ENTER_TO_BEGIN", true, 1.f);
	AddAnimation("PRESS_ENTERED", true, 0.3f);
}

void CButton_PressEnter::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CButton_PressEnter::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CButton_PressEnter::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CButton_PressEnter* CButton_PressEnter::Clone()
{
	return new CButton_PressEnter(*this);
}

void CButton_PressEnter::EnterPressed(float DeltaTime)
{
	ChangeAnimation("PRESS_ENTERED");

	CSceneManager::GetInst()->CreateScene<CScene_ModeSelect>();
}
