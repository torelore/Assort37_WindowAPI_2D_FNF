#include "Button_Difficulty.h"
#include "../../Input.h"
#include "../../Scene/Scene/Scene_FreePlay.h"

CButton_Difficulty::CButton_Difficulty()
{
	m_Difficulty = ESong_Difficulty::Normal;
}

CButton_Difficulty::CButton_Difficulty(const CButton_Difficulty& obj)
{
	m_Difficulty = obj.m_Difficulty;
}

CButton_Difficulty::~CButton_Difficulty()
{
}

void CButton_Difficulty::Start()
{
	CGameObject::Start();


	CInput::GetInst()->SetCallback<CButton_Difficulty>("Enter", KeyState_Down, this, &CButton_Difficulty::EnterPressed);

	CInput::GetInst()->SetCallback<CButton_Difficulty>("MoveLeft", KeyState_Down, this, &CButton_Difficulty::LeftPressed);
	CInput::GetInst()->SetCallback<CButton_Difficulty>("MoveRight", KeyState_Down, this, &CButton_Difficulty::RightPressed);

	CInput::GetInst()->SetCallback<CButton_Difficulty>("MoveUp", KeyState_Down, this, &CButton_Difficulty::UpPressed);
	CInput::GetInst()->SetCallback<CButton_Difficulty>("MoveDown", KeyState_Down, this, &CButton_Difficulty::DownPressed);
}

bool CButton_Difficulty::Init()
{
	CreateAnimation();

	AddAnimation("NORMAL");
	AddAnimation("EASY");
	AddAnimation("HARD");

	return true;
}

void CButton_Difficulty::Update(float DeltaTime)
{
	switch (m_Difficulty)
	{
	case ESong_Difficulty::Easy:
		SetPos(900.f, GetPos().y);
		ChangeAnimation("EASY");
		break;
	case ESong_Difficulty::Normal:
		SetPos(850.f, GetPos().y);
		ChangeAnimation("NORMAL");
		break;
	case ESong_Difficulty::Hard:
		SetPos(900.f, GetPos().y);
		ChangeAnimation("HARD");
		break;
	}

	CGameObject::Update(DeltaTime);
}

void CButton_Difficulty::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CButton_Difficulty::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CButton_Difficulty* CButton_Difficulty::Clone()
{
	return new CButton_Difficulty(*this);
}

bool CButton_Difficulty::ButtonScene(float InputTime)
{
	return false;
}

void CButton_Difficulty::EnterPressed(float DeltaTime)
{
	((CScene_FreePlay*)m_Scene)->EnterPressed();
}

void CButton_Difficulty::UpPressed(float DeltaTime)
{
	((CScene_FreePlay*)m_Scene)->UpPressed(DeltaTime);
}

void CButton_Difficulty::DownPressed(float DeltaTime)
{
	((CScene_FreePlay*)m_Scene)->DownPressed(DeltaTime);
}

void CButton_Difficulty::LeftPressed(float DeltaTime)
{
	switch (m_Difficulty)
	{
	case ESong_Difficulty::Easy:
		m_Difficulty = ESong_Difficulty::Hard;
		break;
	case ESong_Difficulty::Normal:
		m_Difficulty = ESong_Difficulty::Easy;
		break;
	case ESong_Difficulty::Hard:
		m_Difficulty = ESong_Difficulty::Normal;
		break;
	}

	((CScene_FreePlay*)m_Scene)->LeftPressed(DeltaTime);
	((CScene_FreePlay*)m_Scene)->SetSongDifficulty(m_Difficulty);
}

void CButton_Difficulty::RightPressed(float DeltaTime)
{
	switch (m_Difficulty)
	{
	case ESong_Difficulty::Easy:
		m_Difficulty = ESong_Difficulty::Normal;
		break;
	case ESong_Difficulty::Normal:
		m_Difficulty = ESong_Difficulty::Hard;
		break;
	case ESong_Difficulty::Hard:
		m_Difficulty = ESong_Difficulty::Easy;
		break;
	}

	((CScene_FreePlay*)m_Scene)->RightPressed(DeltaTime);
	((CScene_FreePlay*)m_Scene)->SetSongDifficulty(m_Difficulty);
}
