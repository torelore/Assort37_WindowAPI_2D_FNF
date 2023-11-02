#pragma once

#include "UIImage.h"
#include "../Resource/Texture.h"

class CTextWidget :
	public CUIImage
{
public:
	CTextWidget();
	CTextWidget(const CTextWidget& widget);
	virtual ~CTextWidget();

protected:
	std::string m_Text;
	std::vector<int>	m_vecText;

public :
	void SetText(const std::string& Text) {
		m_Text = "";

		for (auto& c : Text) {
			if (c != '-')
				m_Text += toupper(c);
		}
	}

	std::string GetText() const {
		return m_Text;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual void Render(const Vector2& Pos, HDC hDC);
	virtual CTextWidget* Clone();
};
