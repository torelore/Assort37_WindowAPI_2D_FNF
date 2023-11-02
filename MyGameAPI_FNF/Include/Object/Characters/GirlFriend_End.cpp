#include "GirlFriend_End.h"
#include "../../Input.h"
#include "../../Scene/Scene.h"
#include "../../UI/Scene/UI_GameEndRate.h"

CGirlFriend_End::CGirlFriend_End()
{
}

CGirlFriend_End::CGirlFriend_End(const CGirlFriend_End& obj)
{
}

CGirlFriend_End::~CGirlFriend_End()
{
}

void CGirlFriend_End::Start()
{
	CCharacter::Start();

	CInput::GetInst()->SetCallback<CGirlFriend_End>("MoveLeft", KeyState_Down, this, &CGirlFriend_End::MoveLeft);
	CInput::GetInst()->SetCallback<CGirlFriend_End>("MoveRight", KeyState_Down, this, &CGirlFriend_End::MoveRight);
	CInput::GetInst()->SetCallback<CGirlFriend_End>("Enter", KeyState_Down, this, &CGirlFriend_End::EnterPressed);
}

bool CGirlFriend_End::Init()
{
	if (!CCharacter::Init())
		return false;

	SetPos(525.f, 50.f);

	CreateAnimation();

	return true;
}

void CGirlFriend_End::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CGirlFriend_End::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CGirlFriend_End::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CGirlFriend_End* CGirlFriend_End::Clone()
{
	return new CGirlFriend_End(*this);
}

void CGirlFriend_End::SetAnimationCleared(bool IsCleared)
{
	if (IsCleared) {
		AddAnimation("GF_CHEER", true, 1.f);
		ChangeAnimation("GF_CHEER");
	}
	else {
		AddAnimation("GF_SAD", true, 1.f);
		ChangeAnimation("GF_SAD");
	}
}

void CGirlFriend_End::MoveLeft(float DeltaTime)
{
	CUI_GameEndRate* UIWindow = m_Scene->FindUIWindow<CUI_GameEndRate>("GameEndRateWindow");

	if (UIWindow->GetIsLeftSelected())
		UIWindow->SetIsRightSelect();
	else
		UIWindow->SetIsLeftSelect();
}

void CGirlFriend_End::MoveRight(float DeltaTime)
{
	CUI_GameEndRate* UIWindow = m_Scene->FindUIWindow<CUI_GameEndRate>("GameEndRateWindow");

	if (!UIWindow->GetIsLeftSelected())
		UIWindow->SetIsLeftSelect();
	else
		UIWindow->SetIsRightSelect();
}

void CGirlFriend_End::EnterPressed(float DeltaTime)
{
	CUI_GameEndRate* UIWindow = m_Scene->FindUIWindow<CUI_GameEndRate>("GameEndRateWindow");

	if (UIWindow->GetIsLeftSelected()) {
		if (UIWindow->GetIsStoryMode()) 
			UIWindow->GameNext();
		else 
			UIWindow->GameRetry();
	}
	else {
		UIWindow->GameExit();
	}
}
