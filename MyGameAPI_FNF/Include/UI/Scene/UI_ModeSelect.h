#pragma once
#include "../UIWindow.h"

class CUI_ModeSelect :
	public CUIWindow
{
	friend class CScene;

private:
	CUI_ModeSelect();
	virtual ~CUI_ModeSelect();

private:
	class CUIText* m_Text;
	float	m_TextTime;

	int		m_OutputText;
	int		m_OutputIndex;

	class CNumberWidget* m_NumberWidget;
	class CNumberWidget* m_Number1Widget;
	class CNumberWidget* m_MinuteWidget;
	float	m_Time;
	int		m_Minute;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

