#pragma once
#include "../Scene.h"

class CScene_ModeSelect :
	public CScene
{
	friend class CSceneManager;

private:
	CScene_ModeSelect();
	virtual ~CScene_ModeSelect();

private :
	std::vector<CGameObject*> m_vecMenuButton;

public:
	virtual bool Init();

private:
	void LoadAnimationSequence();
	void LoadSound();

public :
	void EnterPressed();
	void UpPressed();
	void DownPressed();
};

