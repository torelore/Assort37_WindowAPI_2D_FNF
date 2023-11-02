#include "TextWidget.h"
#include "UIWindow.h"

CTextWidget::CTextWidget() :
	m_Text("")
{
}

CTextWidget::CTextWidget(const CTextWidget& widget) :
	CUIImage(widget)
{
	m_Text = widget.m_Text;
}

CTextWidget::~CTextWidget()
{
}

bool CTextWidget::Init()
{
	return true;
}

void CTextWidget::Update(float DeltaTime)
{
	const char* Text = m_Text.c_str();

	size_t Size = m_Text.size();

	m_vecText.clear();

	for (size_t i = 0; i < Size; i++) {
		m_vecText.push_back((int)Text[i]);
	}
}

void CTextWidget::PostUpdate(float DeltaTime)
{
}

void CTextWidget::Collision(float DeltaTime)
{
}

void CTextWidget::Render(HDC hDC)
{
	if (m_vecText.empty())
	{
		// 비어있으면 0을 출력한다.
		m_FrameIndex = 0;
		CUIImage::Render(hDC);
	}

	else
	{
		// 비어있지 않다면 값이 있다는 것이다.
		size_t	Size = m_vecText.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_Texture->GetTextureType() == ETexture_Type::Frame)
				m_FrameIndex = m_vecText[i] - 65;
			else
				m_FrameIndex = 0;

			// 프레임마다의 사이즈가 달라 별도로 m_Size를 설정함.
			m_Size = Vector2(m_Texture->GetWidth(m_FrameIndex), m_Texture->GetHeight(m_FrameIndex));
			
			m_Offset.x = i * 45.f;

			CUIImage::Render(hDC);

		}
	}
}

void CTextWidget::Render(const Vector2& Pos, HDC hDC)
{
	if (m_vecText.empty())
	{
		// 비어있으면 0을 출력한다.
		m_FrameIndex = 0;
		CUIImage::Render(Pos, hDC);
	}
	else
	{
		// 비어있지 않다면 값이 있다는 것이다.
		size_t	Size = m_vecText.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_Texture->GetTextureType() == ETexture_Type::Frame)
				m_FrameIndex = m_vecText[i] - 65;
			else
				m_FrameIndex = 0;

			// 프레임마다의 사이즈가 달라 별도로 m_Size를 설정함.
			m_Size = Vector2(m_Texture->GetWidth(m_FrameIndex), m_Texture->GetHeight(m_FrameIndex));

			m_Offset.x = i * 45.f;
			//m_Offset.x = i * m_Size.x;

			CUIImage::Render(Pos, hDC);
		}
	}
}

CTextWidget* CTextWidget::Clone()
{
	return new CTextWidget(*this);
}
