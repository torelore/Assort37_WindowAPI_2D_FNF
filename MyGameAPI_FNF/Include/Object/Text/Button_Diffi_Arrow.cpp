#include "Button_Diffi_Arrow.h"
#include "../../Input.h"


CButton_Diffi_Arrow::CButton_Diffi_Arrow() :
	m_IsLeft(true)
{
}

CButton_Diffi_Arrow::CButton_Diffi_Arrow(const CButton_Diffi_Arrow& obj)
{
	m_IsLeft = obj.m_IsLeft;
}

CButton_Diffi_Arrow::~CButton_Diffi_Arrow()
{
}

void CButton_Diffi_Arrow::Start()
{
	CGameObject::Start();
}

bool CButton_Diffi_Arrow::Init()
{
	CreateAnimation();

	AddAnimation("RIGHT_ARROW");
	AddAnimation("RIGHT_ARROW_PUSH", false, 0.3f);

	AddAnimationNotify<CButton_Diffi_Arrow>("RIGHT_ARROW_PUSH", 1, this, &CButton_Diffi_Arrow::PushEnd);
	SetAnimationEndNotify<CButton_Diffi_Arrow>("RIGHT_ARROW_PUSH", this, &CButton_Diffi_Arrow::PushEnd);

	AddAnimation("LEFT_ARROW");
	AddAnimation("LEFT_ARROW_PUSH", false, 0.3f);

	AddAnimationNotify<CButton_Diffi_Arrow>("LEFT_ARROW_PUSH", 1, this, &CButton_Diffi_Arrow::PushEnd);
	SetAnimationEndNotify<CButton_Diffi_Arrow>("LEFT_ARROW_PUSH", this, &CButton_Diffi_Arrow::PushEnd);

	return true;
}

void CButton_Diffi_Arrow::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CButton_Diffi_Arrow::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CButton_Diffi_Arrow::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CButton_Diffi_Arrow* CButton_Diffi_Arrow::Clone()
{
	return new CButton_Diffi_Arrow(*this);
}

bool CButton_Diffi_Arrow::ButtonScene(float InputTime)
{
    return false;
}

void CButton_Diffi_Arrow::LeftPressed(float DeltaTime)
{
	if (m_IsLeft)
		ChangeAnimation("LEFT_ARROW_PUSH");
}

void CButton_Diffi_Arrow::RightPressed(float DeltaTime)
{
	if (!m_IsLeft)
		ChangeAnimation("RIGHT_ARROW_PUSH");
}

void CButton_Diffi_Arrow::PushEnd()
{
	if (m_IsLeft)
		ChangeAnimation("LEFT_ARROW");
	else
		ChangeAnimation("RIGHT_ARROW");

}
