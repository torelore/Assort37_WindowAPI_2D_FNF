#pragma once

#include "../Scene.h"

class CScene_GameEndRate :
	public CScene
{
	friend class CSceneManager;

private:
	CScene_GameEndRate();
	virtual ~CScene_GameEndRate();

public:
	virtual bool Init();

private:
	void LoadAnimationSequence();

public :
	bool SetGameRate(const GameScore& GameScore);
	void IsStoryMode();

};

