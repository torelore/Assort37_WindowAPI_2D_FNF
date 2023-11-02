
#include "NumberWidget.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "UIWindow.h"

CNumberWidget::CNumberWidget() :
	m_Number(0)
{
	m_IsScore = true;
}

CNumberWidget::CNumberWidget(const CNumberWidget& widget) :
	CUIImage(widget)
{
	m_Number = widget.m_Number;
	m_IsScore = widget.m_IsScore;
}

CNumberWidget::~CNumberWidget()
{
}

bool CNumberWidget::Init()
{
	return true;
}

void CNumberWidget::Update(float DeltaTime)
{
	int	Number = m_Number;

	std::stack<int>	NumberStack;

	// 1234 % 10 = 4    1234 / 10 = 123
	while (Number > 0)
	{
		NumberStack.push(Number % 10);
		Number /= 10;
	}

	m_vecNumber.clear();

	while (!NumberStack.empty())
	{
		m_vecNumber.push_back(NumberStack.top());
		NumberStack.pop();
	}
}

void CNumberWidget::PostUpdate(float DeltaTime)
{
}

void CNumberWidget::Collision(float DeltaTime)
{
}

void CNumberWidget::Render(HDC hDC)
{
	size_t ZeroSpace = 0;

	if(m_IsScore)
		ZeroSpace = 6 - m_vecNumber.size();

	for (size_t i = 0; i < ZeroSpace; i++) {
		m_FrameIndex = 0;

		m_Size = Vector2(m_Texture->GetWidth(m_FrameIndex), m_Texture->GetHeight(m_FrameIndex));

		m_Offset.x = i * 40.f;

		CUIImage::Render(hDC);
	}

	{
		// 비어있지 않다면 값이 있다는 것이다.
		size_t	Size = m_vecNumber.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_Texture->GetTextureType() == ETexture_Type::Frame)
				m_FrameIndex = m_vecNumber[i];

			else
				m_FrameIndex = 0;

			m_Size = Vector2(m_Texture->GetWidth(m_FrameIndex), m_Texture->GetHeight(m_FrameIndex));
			m_Offset.x = (i + ZeroSpace) * 40.f;

			CUIImage::Render(hDC);
		}
	}
}

void CNumberWidget::Render(const Vector2& Pos, HDC hDC)
{
	size_t ZeroSpace = 0;

	if (m_IsScore)
		ZeroSpace = 6 - m_vecNumber.size();

	for (size_t i = 0; i < ZeroSpace; i++) {
		m_FrameIndex = 0;

		m_Size = Vector2(m_Texture->GetWidth(m_FrameIndex), m_Texture->GetHeight(m_FrameIndex));
		m_Offset.x = i * 40.f;

		CUIImage::Render(hDC);
	}

	{
		// 비어있지 않다면 값이 있다는 것이다.
		size_t	Size = m_vecNumber.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_Texture->GetTextureType() == ETexture_Type::Frame)
				m_FrameIndex = m_vecNumber[i];
			else
				m_FrameIndex = 0;

			m_Size = Vector2(m_Texture->GetWidth(m_FrameIndex), m_Texture->GetHeight(m_FrameIndex));
			m_Offset.x = (i + ZeroSpace) * 40.f;

			CUIImage::Render(Pos, hDC);
		}
	}
}

CNumberWidget* CNumberWidget::Clone()
{
	return new CNumberWidget(*this);
}
