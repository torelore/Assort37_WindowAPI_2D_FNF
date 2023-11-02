#include "BoyFriend.h"
#include "../../Input.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Scene/Scene_GamePlay.h"
#include "../../UI/Scene/UI_GamePlay.h"


CBoyFriend::CBoyFriend()
{
	m_NoteCount = 0;
	m_UpEndPoint = nullptr;
	m_DownEndPoint = nullptr;
	m_LeftEndPoint = nullptr;
	m_RightEndPoint = nullptr;
}

CBoyFriend::CBoyFriend(const CBoyFriend& obj) :
	CCharacter(obj)
{
	m_NoteCount = obj.m_NoteCount;
	m_UpEndPoint = obj.m_UpEndPoint;
	m_DownEndPoint = obj.m_DownEndPoint;
	m_LeftEndPoint = obj.m_LeftEndPoint;
	m_RightEndPoint = obj.m_RightEndPoint;
}

CBoyFriend::~CBoyFriend()
{
}

void CBoyFriend::Start()
{
	CCharacter::Start();

	CInput::GetInst()->SetCallback<CBoyFriend>("MoveUp", KeyState_Down, this, &CBoyFriend::MoveUp);
	CInput::GetInst()->SetCallback<CBoyFriend>("MoveDown", KeyState_Down, this, &CBoyFriend::MoveDown);
	CInput::GetInst()->SetCallback<CBoyFriend>("MoveLeft", KeyState_Down, this, &CBoyFriend::MoveLeft);
	CInput::GetInst()->SetCallback<CBoyFriend>("MoveRight", KeyState_Down, this, &CBoyFriend::MoveRight);

	CInput::GetInst()->SetCallback<CBoyFriend>("Enter", KeyState_Down, this, &CBoyFriend::EnterPressed);
}

bool CBoyFriend::Init()
{
	if (!CCharacter::Init())
		return false;

	CreateAnimation();

	AddAnimation("BF_IDLE", true, 0.8f);


	AddAnimation("BF_UP", false, 0.5f);

	AddAnimationNotify<CBoyFriend>("BF_UP", 15, this, &CBoyFriend::MoveEnd);
	SetAnimationEndNotify<CBoyFriend>("BF_UP", this, &CBoyFriend::MoveEnd);


	AddAnimation("BF_UP_MISS", false, 0.5f);

	AddAnimationNotify<CBoyFriend>("BF_UP_MISS", 24, this, &CBoyFriend::MoveEnd);
	SetAnimationEndNotify<CBoyFriend>("BF_UP_MISS", this, &CBoyFriend::MoveEnd);


	AddAnimation("BF_DOWN", false, 0.5f);

	AddAnimationNotify<CBoyFriend>("BF_DOWN", 30, this, &CBoyFriend::MoveEnd);
	SetAnimationEndNotify<CBoyFriend>("BF_DOWN", this, &CBoyFriend::MoveEnd);


	AddAnimation("BF_DOWN_MISS", false, 0.5f);

	AddAnimationNotify<CBoyFriend>("BF_DOWN_MISS", 30, this, &CBoyFriend::MoveEnd);
	SetAnimationEndNotify<CBoyFriend>("BF_DOWN_MISS", this, &CBoyFriend::MoveEnd);


	AddAnimation("BF_LEFT", false, 0.5f);

	AddAnimationNotify<CBoyFriend>("BF_LEFT", 15, this, &CBoyFriend::MoveEnd);
	SetAnimationEndNotify<CBoyFriend>("BF_LEFT", this, &CBoyFriend::MoveEnd);


	AddAnimation("BF_LEFT_MISS", false, 0.5f);

	AddAnimationNotify<CBoyFriend>("BF_LEFT_MISS", 34, this, &CBoyFriend::MoveEnd);
	SetAnimationEndNotify<CBoyFriend>("BF_LEFT_MISS", this, &CBoyFriend::MoveEnd);


	AddAnimation("BF_RIGHT", false, 0.5f);

	AddAnimationNotify<CBoyFriend>("BF_RIGHT", 62, this, &CBoyFriend::MoveEnd);
	SetAnimationEndNotify<CBoyFriend>("BF_RIGHT", this, &CBoyFriend::MoveEnd);


	AddAnimation("BF_RIGHT_MISS", false, 0.5f);

	AddAnimationNotify<CBoyFriend>("BF_RIGHT_MISS", 46, this, &CBoyFriend::MoveEnd);
	SetAnimationEndNotify<CBoyFriend>("BF_RIGHT_MISS", this, &CBoyFriend::MoveEnd);

	return true;
}

void CBoyFriend::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CBoyFriend::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CBoyFriend::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CBoyFriend::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CBoyFriend* CBoyFriend::Clone()
{
	return new CBoyFriend(*this);
}

float CBoyFriend::SetDamage(float Damage)
{
	return 0.0f;
}

void CBoyFriend::MoveUp(float DeltaTime)
{
	ChangeAnimation("BF_UP");

	m_UpEndPoint->PlayerInput(ENote_Type::Up);
}
void CBoyFriend::MoveDown(float DeltaTime)
{
	ChangeAnimation("BF_DOWN");

	m_DownEndPoint->PlayerInput(ENote_Type::Down);
}

void CBoyFriend::MoveLeft(float DeltaTime)
{
	ChangeAnimation("BF_LEFT");

	m_LeftEndPoint->PlayerInput(ENote_Type::Left);
}

void CBoyFriend::MoveRight(float DeltaTime)
{
	ChangeAnimation("BF_RIGHT");

	m_RightEndPoint->PlayerInput(ENote_Type::Right);
}

void CBoyFriend::MoveEnd()
{
	ChangeAnimation("BF_IDLE");
}

void CBoyFriend::EnterPressed(float DeltaTime)
{
	((CScene_GamePlay*)m_Scene)->EnterPressed();
}

void CBoyFriend::MoveUpWrong()
{
	ChangeAnimation("BF_UP_MISS");
}


void CBoyFriend::MoveDownWrong()
{
	ChangeAnimation("BF_DOWN_MISS");
}

void CBoyFriend::MoveLeftWrong()
{
	ChangeAnimation("BF_LEFT_MISS");
}

void CBoyFriend::MoveRightWrong()
{
	ChangeAnimation("BF_RIGHT_MISS");
}
