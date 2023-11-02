
#include "Note.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderSphere.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Scene/Scene_GamePlay.h"
#include "../UI/WidgetComponent.h"
#include "../UI/NumberWidget.h"
#include "../UI/UI_HealthBar.h"
#include "../UI/Scene/UI_GamePlay.h"

CNote::CNote()
{
	m_ObjType = EObject_Type::Note;
	m_Dir.x = 0.f;
	m_Dir.y = -1.f;

	m_Distance = 6000.f;
	m_MoveSpeed = 720.f;

	m_NoteType = ENote_Type::Left;
	m_IsNote = true;
	m_Owner = ENote_Owner::Player;
	m_IsCollEndPoint = false;
}

CNote::CNote(const CNote& obj) :
	CGameObject(obj)
{
	m_Dir = obj.m_Dir;
	m_Distance = obj.m_Distance;

	m_NoteType = obj.m_NoteType;;
	m_IsNote = obj.m_IsNote;;
	m_Owner = obj.m_Owner;
	m_IsCollEndPoint = obj.m_IsCollEndPoint;;
}

CNote::~CNote()
{
}

void CNote::Start()
{
	CGameObject::Start();

	CCollider* Body = FindCollider("Body");
	Body->SetCollisionBeginFunction<CNote>(this, &CNote::CollisionBegin);
	Body->SetCollisionEndFunction<CNote>(this, &CNote::CollisionEnd);
}

bool CNote::Init()
{
	if (!CGameObject::Init())
		return false;

	SetPivot(0.5f, 0.5f);

	CreateAnimation();
	AddAnimation("LEFT_NOTE");
	AddAnimation("UP_NOTE");
	AddAnimation("DOWN_NOTE");
	AddAnimation("RIGHT_NOTE");

	CColliderBox* Body = AddCollider<CColliderBox>("Body");
	Body->SetExtent(100.f, 100.f);
	Body->SetOffset(0.f, 0.f);

	return true;
}

void CNote::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (ENote_Owner::Enemy == m_Owner) {
		if (m_IsCollEndPoint && m_Pos.y <= NOTE_END_Y)
			Destroy();
	}
	else {
		if (m_IsCollEndPoint && m_Pos.y < NOTE_END_Y - m_Size.y) {
			NoteRate_Shit();
			PopThis();

			Destroy();
		}
	}


	Vector2	Dir = m_Dir;
	Dir.Normalize();

	Move(Dir);

	m_Distance -= GetMoveSpeedFrame();

	if (m_Distance <= 0.f)
		Destroy();
}

void CNote::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CNote::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CNote::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CNote* CNote::Clone()
{
	return new CNote(*this);
}

void CNote::CollisionBegin(CCollider* Src, CCollider* Dest, float DeltaTime)
{
	if (Dest->GetName() == "NoteEndBody")
		m_IsCollEndPoint = true;
}

void CNote::CollisionEnd(CCollider* Src, CCollider* Dest, float DeltaTime)
{
}

ENote_Rate CNote::GetNoteRate() const
{
	ENote_Rate NoteRate = ENote_Rate::Shit;

	if (m_IsCollEndPoint) {
		float Distance = abs(NOTE_END_Y - m_Pos.y);

		if (Distance <= 44.f)
			NoteRate = ENote_Rate::Sick;
		else
			NoteRate = ENote_Rate::Good;
	}

	return NoteRate;
}

void CNote::NoteRate_Sick()
{
	CUI_HealthBar* HealthBar = m_Scene->FindUIWindow<CUI_HealthBar>("HealthBarWindow");
	HealthBar->MoveHPBar(-10.f);

	((CScene_GamePlay*)m_Scene)->AddScore(NOTERATE_SICK);
	((CScene_GamePlay*)m_Scene)->AddCombo();
	((CScene_GamePlay*)m_Scene)->SetRate();

	((CScene_GamePlay*)m_Scene)->ComboEffect(ENote_Rate::Sick);

	PopThis();

	Destroy();
}

void CNote::NoteRate_Good()
{
	CUI_HealthBar* HealthBar = m_Scene->FindUIWindow<CUI_HealthBar>("HealthBarWindow");
	HealthBar->MoveHPBar(-5.f);

	((CScene_GamePlay*)m_Scene)->AddScore(NOTERATE_GOOD);
	((CScene_GamePlay*)m_Scene)->AddCombo();
	((CScene_GamePlay*)m_Scene)->SetRate();

	((CScene_GamePlay*)m_Scene)->ComboEffect(ENote_Rate::Good);

	PopThis();

	Destroy();
}

void CNote::NoteRate_Bad()
{
	CUI_HealthBar* HealthBar = m_Scene->FindUIWindow<CUI_HealthBar>("HealthBarWindow");
	HealthBar->MoveHPBar(-2.f);

	((CScene_GamePlay*)m_Scene)->AddScore(NOTERATE_BAD);
	((CScene_GamePlay*)m_Scene)->AddCombo();
	((CScene_GamePlay*)m_Scene)->SetRate();

	((CScene_GamePlay*)m_Scene)->ComboEffect(ENote_Rate::Bad);

	PopThis();

	Destroy();
}

void CNote::NoteRate_Shit()
{
	CUI_HealthBar* HealthBar = m_Scene->FindUIWindow<CUI_HealthBar>("HealthBarWindow");
	HealthBar->MoveHPBar(10.f);

	((CScene_GamePlay*)m_Scene)->AddNoteMissCount();
	((CScene_GamePlay*)m_Scene)->ResetCombo();
	((CScene_GamePlay*)m_Scene)->SetRate();

	((CScene_GamePlay*)m_Scene)->ComboEffect(ENote_Rate::Shit);
}

void CNote::PopThis()
{
	switch (m_NoteType)
	{
	case ENote_Type::Left:
		m_Scene->FindUIWindow<CUI_GamePlay>("GamePlayWindow")->PopLeftFirstNote();
		break;
	case ENote_Type::Down:
		m_Scene->FindUIWindow<CUI_GamePlay>("GamePlayWindow")->PopDownFirstNote();
		break;
	case ENote_Type::Up:
		m_Scene->FindUIWindow<CUI_GamePlay>("GamePlayWindow")->PopUpFirstNote();
		break;
	case ENote_Type::Right:
		m_Scene->FindUIWindow<CUI_GamePlay>("GamePlayWindow")->PopRightFirstNote();
		break;
	}
}
