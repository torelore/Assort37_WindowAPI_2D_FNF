#pragma once

#include "../Scene.h"

class CScene_Start :
	public CScene
{
	friend class CSceneManager;

private:
	CScene_Start();
	virtual ~CScene_Start();

public:
	virtual bool Init();

private:
	void LoadAnimationSequence();
	void LoadSound();
};

