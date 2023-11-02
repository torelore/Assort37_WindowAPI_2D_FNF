#pragma once

#include "UIWindow.h"
#include "ProgressBar.h"
#include "Button.h"
#include "UIImage.h"

class CUI_HealthBar :
	public CUIWindow
{
	friend class CScene;

private:
	CUI_HealthBar();
	virtual ~CUI_HealthBar();

private:
	CSharedPtr<CProgressBar> m_HPBar;
	CUIImage* EnemyIcon;
	CUIImage* PlayerIcon;

	std::string Enemy;

public:
	void SetEnemy(std::string Name);
	void MoveHPBar(float dist);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private :
	const TCHAR* NameToPath(std::string& Name) {

		Name = "Icon/" + Name + "_Icon.bmp";
		
		// 기존 string 사이즈
		size_t Size = strlen(Name.c_str()) + 1;
		size_t ConvertSize = 0;

		wchar_t* tString = new wchar_t[Size];

		mbstowcs_s(&ConvertSize, tString, Size, Name.c_str(), _TRUNCATE);

		return (TCHAR*)tString;
	}
};

