#pragma once

#include "../GameObject.h"
#include "../../Resource/Sound.h"

class CButton_StoryMode :
	public CGameObject
{
	friend class CScene;

public:
	CButton_StoryMode();
	CButton_StoryMode(const CButton_StoryMode& obj);
	virtual ~CButton_StoryMode();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CButton_StoryMode* Clone();
	virtual bool ButtonScene(float InputTime);

private:
	void EnterPressed(float DeltaTime);
	void UpPressed(float DeltaTime);
	void DownPressed(float DeltaTime);

};

