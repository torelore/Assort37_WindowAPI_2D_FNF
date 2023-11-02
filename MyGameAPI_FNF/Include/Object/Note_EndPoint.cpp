#include "Note_EndPoint.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/Scene/Scene_GamePlay.h"
#include "../UI/Scene/UI_GamePlay.h"
#include "Note.h"
#include "../UI/UI_HealthBar.h"
#include "Characters/BoyFriend.h"

CNote_EndPoint::CNote_EndPoint() : 
	m_Owner(ENote_Owner::Player),
	m_Type(ENote_Type::Left),
	m_OwnerCharacter(nullptr)
{
	m_ObjType = EObject_Type::NoteBack;

	m_IsNote = true;
}

CNote_EndPoint::CNote_EndPoint(const CNote_EndPoint& obj)
{
	m_Owner = obj.m_Owner;
	m_Type = obj.m_Type;
	m_OwnerCharacter = obj.m_OwnerCharacter;
	m_ObjType = EObject_Type::NoteBack;
	m_IsNote = true;
}

CNote_EndPoint::~CNote_EndPoint()
{
}

void CNote_EndPoint::SetInfo(const ENote_Owner& Owner, const ENote_Type& Type)
{
	m_Owner = Owner;
	m_Type = Type;

	float PosX = 0.f;
	float PosY = NOTE_END_Y;

	PosX = (bool)m_Owner ? NOTE_MY_X : NOTE_ENEMY_X;

	switch (m_Type)
	{
	case ENote_Type::Up :
		AddAnimation("UP_BACK");

		AddAnimation("UP_CONFIRM", false, 0.2f);
		
		AddAnimationNotify<CNote_EndPoint>("UP_CONFIRM", 3, this, &CNote_EndPoint::NoteEnd);
		SetAnimationEndNotify<CNote_EndPoint>("UP_CONFIRM", this, &CNote_EndPoint::NoteEnd);

		AddAnimation("UP_PRESS", true, 0.2f);

		AddAnimationNotify<CNote_EndPoint>("UP_PRESS", 1, this, &CNote_EndPoint::NoteEnd);
		SetAnimationEndNotify<CNote_EndPoint>("UP_PRESS", this, &CNote_EndPoint::NoteEnd);
		
		PosX += 240.f;
		break;
	case ENote_Type::Down:
		AddAnimation("DOWN_BACK");

		AddAnimation("DOWN_CONFIRM", true, 0.1f);

		AddAnimationNotify<CNote_EndPoint>("DOWN_CONFIRM", 3, this, &CNote_EndPoint::NoteEnd);
		SetAnimationEndNotify<CNote_EndPoint>("DOWN_CONFIRM", this, &CNote_EndPoint::NoteEnd);

		AddAnimation("DOWN_PRESS", true, 0.2f);

		AddAnimationNotify<CNote_EndPoint>("DOWN_PRESS", 1, this, &CNote_EndPoint::NoteEnd);
		SetAnimationEndNotify<CNote_EndPoint>("DOWN_PRESS", this, &CNote_EndPoint::NoteEnd);

		PosX += 120.f;
		break;
	case ENote_Type::Left:
		AddAnimation("LEFT_BACK");

		AddAnimation("LEFT_CONFIRM", true, 0.1f);

		AddAnimationNotify<CNote_EndPoint>("LEFT_CONFIRM", 3, this, &CNote_EndPoint::NoteEnd);
		SetAnimationEndNotify<CNote_EndPoint>("LEFT_CONFIRM", this, &CNote_EndPoint::NoteEnd);

		AddAnimation("LEFT_PRESS", true, 0.2f);

		AddAnimationNotify<CNote_EndPoint>("LEFT_PRESS", 1, this, &CNote_EndPoint::NoteEnd);
		SetAnimationEndNotify<CNote_EndPoint>("LEFT_PRESS", this, &CNote_EndPoint::NoteEnd);

		break;
	case ENote_Type::Right:
		AddAnimation("RIGHT_BACK");

		AddAnimation("RIGHT_CONFIRM", true, 0.1f);

		AddAnimationNotify<CNote_EndPoint>("RIGHT_CONFIRM", 3, this, &CNote_EndPoint::NoteEnd);
		SetAnimationEndNotify<CNote_EndPoint>("RIGHT_CONFIRM", this, &CNote_EndPoint::NoteEnd);

		AddAnimation("RIGHT_PRESS", true, 0.2f);

		AddAnimationNotify<CNote_EndPoint>("RIGHT_PRESS", 1, this, &CNote_EndPoint::NoteEnd);
		SetAnimationEndNotify<CNote_EndPoint>("RIGHT_PRESS", this, &CNote_EndPoint::NoteEnd);

		PosX += 360.f;
		break;
	}

	SetPos(PosX, PosY);
}

void CNote_EndPoint::Start()
{
	CGameObject::Start();

	CCollider* Body = FindCollider("NoteEndBody");
	Body->SetCollisionBeginFunction<CNote_EndPoint>(this, &CNote_EndPoint::CollisionBegin);
}

bool CNote_EndPoint::Init()
{
	if (!CGameObject::Init())
		return false;

	SetPivot(0.5f, 0.5f);

	CreateAnimation();


	CColliderBox* Body = AddCollider<CColliderBox>("NoteEndBody");
	Body->SetExtent(100.f, 100.f);
	Body->SetOffset(0.f, 0.f);

	return true;
}

void CNote_EndPoint::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CNote_EndPoint::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CNote_EndPoint::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CNote_EndPoint::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CNote_EndPoint* CNote_EndPoint::Clone()
{
	return new CNote_EndPoint(*this);
}

void CNote_EndPoint::CollisionBegin(CCollider* Src, CCollider* Dest, float DeltaTime)
{
	if (m_Owner != ENote_Owner::Enemy)
		return;
	else {
		switch (m_Type)
		{
		case ENote_Type::Up:
			m_OwnerCharacter->MoveUp(DeltaTime);
			break;
		case ENote_Type::Down:
			m_OwnerCharacter->MoveDown(DeltaTime);
			break;
		case ENote_Type::Left:
			m_OwnerCharacter->MoveLeft(DeltaTime);
			break;
		case ENote_Type::Right:
			m_OwnerCharacter->MoveRight(DeltaTime);
			break;
		}
	}
}

void CNote_EndPoint::NoteEnd()
{
	switch (m_Type)
	{
	case ENote_Type::Up:
		ChangeAnimation("UP_BACK");
		break;
	case ENote_Type::Down:
		ChangeAnimation("DOWN_BACK");
		break;
	case ENote_Type::Left:
		ChangeAnimation("LEFT_BACK");
		break;
	case ENote_Type::Right:
		ChangeAnimation("RIGHT_BACK");
		break;
	}
}

bool CNote_EndPoint::PlayerInput(const ENote_Type& Type)
{
	if (ENote_Owner::Player == m_Owner) {

		// Input 후, 현재 입력된 Type에 따라 해당 타입 노트 중 가장 위의 노트를 가져옴
		CNote* Note = m_Scene->FindUIWindow<CUI_GamePlay>("GamePlayWindow")->GetUpFirstNote();

		switch (Type)
		{
		case ENote_Type::Down:
			Note = m_Scene->FindUIWindow<CUI_GamePlay>("GamePlayWindow")->GetDownFirstNote();
			break;
		case ENote_Type::Left:
			Note = m_Scene->FindUIWindow<CUI_GamePlay>("GamePlayWindow")->GetLeftFirstNote();
			break;
		case ENote_Type::Right:
			Note = m_Scene->FindUIWindow<CUI_GamePlay>("GamePlayWindow")->GetRightFirstNote();
			break;
		}

		// 노트가 없다면(생성되지 않았다면) 반환.
		if (Note == nullptr) {
			switch (Type)
			{
			case ENote_Type::Up:
				ChangeAnimation("UP_PRESS");
				((CBoyFriend*)m_OwnerCharacter)->MoveUpWrong();
				break;
			case ENote_Type::Down:
				ChangeAnimation("DOWN_PRESS");
				((CBoyFriend*)m_OwnerCharacter)->MoveDownWrong();
				break;
			case ENote_Type::Left:
				ChangeAnimation("LEFT_PRESS");
				((CBoyFriend*)m_OwnerCharacter)->MoveLeftWrong();
				break;
			case ENote_Type::Right:
				ChangeAnimation("RIGHT_PRESS");
				((CBoyFriend*)m_OwnerCharacter)->MoveRightWrong();
				break;
			}

			CUI_HealthBar* HealthBar = m_Scene->FindUIWindow<CUI_HealthBar>("HealthBarWindow");
			HealthBar->MoveHPBar(10.f);

			((CScene_GamePlay*)m_Scene)->AddNoteMissCount();
			((CScene_GamePlay*)m_Scene)->ResetCombo();
			((CScene_GamePlay*)m_Scene)->SetRate();

			((CScene_GamePlay*)m_Scene)->ComboEffect(ENote_Rate::Shit);

			return false;
		}


		// 노트 판정
		ENote_Rate NoteRate = Note->GetNoteRate();

		bool IsShit = false;

		// 노트가 있다면 판정 값을 받아와 처리
		switch (NoteRate)
		{
		case ENote_Rate::Sick:
			Note->NoteRate_Sick();
			break;
		case ENote_Rate::Good:
			Note->NoteRate_Good();
			break;
		case ENote_Rate::Bad:
			Note->NoteRate_Bad();
			break;
		case ENote_Rate::Shit:
			Note->NoteRate_Shit();
			IsShit = true;
			break;
		}

		switch (Type)
		{
		case ENote_Type::Up:
			if (IsShit) {
				ChangeAnimation("UP_PRESS");
				((CBoyFriend*)m_OwnerCharacter)->MoveUpWrong();
			}
			else {
				ChangeAnimation("UP_CONFIRM");
			}
			break;
		case ENote_Type::Down:
			if (IsShit) {
				ChangeAnimation("DOWN_PRESS");
				((CBoyFriend*)m_OwnerCharacter)->MoveDownWrong();
			}
			else {
				ChangeAnimation("DOWN_CONFIRM");
			}
			break;
		case ENote_Type::Left:
			if (IsShit) {
				ChangeAnimation("LEFT_PRESS");
				((CBoyFriend*)m_OwnerCharacter)->MoveLeftWrong();
			}
			else {
				ChangeAnimation("LEFT_CONFIRM");
			}
			break;
		case ENote_Type::Right:
			if (IsShit) {
				ChangeAnimation("RIGHT_PRESS");
				((CBoyFriend*)m_OwnerCharacter)->MoveRightWrong();
			}
			else {
				ChangeAnimation("RIGHT_CONFIRM");
			}
			break;
		}
		
		return true;
	}
	return false;
}
