#include "Train.h"

CTrain::CTrain()
{
}

CTrain::~CTrain()
{
}

void CTrain::Start()
{
    CScrollMap::Start();
}

bool CTrain::Init()
{
    CScrollMap::Init();

    return true;
}

void CTrain::Update(float DeltaTime)
{
    m_Pos.x -= 5.f;

    if (m_Pos.x <= -1500.f) {
        m_Pos.x = 1280.f;
    }

    CScrollMap::Update(DeltaTime);
}

void CTrain::PostUpdate(float DeltaTime)
{
    CScrollMap::PostUpdate(DeltaTime);
}

void CTrain::PrevRender()
{
    CScrollMap::PrevRender();
}

void CTrain::Render(HDC hDC)
{
    CScrollMap::Render(hDC);
}

void CTrain::Save(FILE* pFile)
{
}

void CTrain::Load(FILE* pFile)
{
}
