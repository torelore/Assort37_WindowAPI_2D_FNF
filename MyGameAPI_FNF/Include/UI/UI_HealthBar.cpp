
#include "UI_HealthBar.h"
#include "../GameManager.h"
#include "../Scene/Scene/Scene_GamePlay.h"
#include "../Scene/SceneManager.h"

CUI_HealthBar::CUI_HealthBar()
{
	EnemyIcon = nullptr;
	PlayerIcon = nullptr;
	Enemy = "";
}

CUI_HealthBar::~CUI_HealthBar()
{
}

void CUI_HealthBar::SetEnemy(std::string Name)
{
	Enemy = Name;

	std::string IconName = Name + "Icon";
	std::string IconBadName = Name + "BadIcon";
	std::string IconBadText = Name + "_Bad";

	// Enemy Char Icon
	EnemyIcon = CreateWidget<CUIImage>(IconName);

	EnemyIcon->SetTexture(IconBadName, NameToPath(IconBadText));
	EnemyIcon->SetTexture(IconName, NameToPath(Name));
	EnemyIcon->SetTextureColorKey(255, 0, 255);
	EnemyIcon->SetPos(520.f, 580.f);
	EnemyIcon->SetZOrder(19);
}

void CUI_HealthBar::MoveHPBar(float dist)
{
	if (dist >= 0) {
		PlayerIcon->SetTexture("BFBadIcon");
		PlayerIcon->SetTextureColorKey(255, 0, 255);

		EnemyIcon->SetTexture(Enemy + "Icon");
		EnemyIcon->SetTextureColorKey(255, 0, 255);
	}
	else {
		PlayerIcon->SetTexture("BFIcon");
		PlayerIcon->SetTextureColorKey(255, 0, 255);

		EnemyIcon->SetTexture(Enemy + "BadIcon");
		EnemyIcon->SetTextureColorKey(255, 0, 255);
	}


	Vector2 EnemyVec = EnemyIcon->GetPos();
	Vector2 PlayerVec = PlayerIcon->GetPos();

	float Center = (PlayerVec.x + EnemyVec.x) / 2.f + dist;

	if (Center < 380)
		return;
	else if (Center > 900) {
		GameScore GC = ((CScene_GamePlay*)m_Scene)->GameOver();

		CSceneManager::GetInst()->CreateScene<CScene_GameEndRate>(GC);

		return;
	}

	EnemyIcon->SetPos(EnemyVec.x + dist, EnemyVec.y);
	PlayerIcon->SetPos(PlayerVec.x + dist, PlayerVec.y);

	float CenterPercent = (Center - 360.f) / 520.f;

	m_HPBar->SetPercent(CenterPercent + 0.05f);
}

bool CUI_HealthBar::Init()
{
	Resolution	RS = CGameManager::GetInst()->GetResolution();

	// BarBack
	CUIImage* Back = CreateWidget<CUIImage>("healthBar");

	Back->SetTexture("healthBar", TEXT("healthBar.bmp"));
	Back->SetTextureColorKey(255, 0, 255);
	Back->SetPos(340.f, 650.f);
	Back->SetZOrder(10);


	// BF Char Icon
	PlayerIcon = CreateWidget<CUIImage>("BFIcon");
	PlayerIcon->SetTexture("BFBadIcon", TEXT("Icon/BF_Bad_Icon.bmp"));
	PlayerIcon->SetTexture("BFIcon", TEXT("Icon/BF_Icon.bmp"));
	PlayerIcon->SetTextureColorKey(255, 0, 255);
	PlayerIcon->SetPos(620.f, 580.f);
	PlayerIcon->SetZOrder(20);


	// Bar
	m_HPBar = CreateWidget<CProgressBar>("HPBar");
	m_HPBar->SetTexture("HPBar", TEXT("healthBar_Red.bmp"));
	m_HPBar->SetPos(346.f, 655.f);
	m_HPBar->SetZOrder(15);

	m_HPBar->SetPercent((PlayerIcon->GetPos().x - 360.f)/520.f);

	return true;
}

void CUI_HealthBar::Update(float DeltaTime)
{

}
