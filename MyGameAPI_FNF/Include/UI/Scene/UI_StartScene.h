#pragma once
#include "../UIWindow.h"

class CUI_StartScene :
	public CUIWindow
{
	friend class CScene;

private:
	CUI_StartScene();
	virtual ~CUI_StartScene();

public:
	virtual bool Init();

public:
	void EnterPressed();
};

