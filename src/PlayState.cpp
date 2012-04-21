#include "PlayState.h"
#include "StateManager.h"
#include "TextControl.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include <windows.h>

using namespace std;

CPlayState::CPlayState(CStateManager* pManager)
 : CGameStateBase(pManager), 
   m_windowWidth(-1),
	 m_windowHeight(-1),
   m_pFont(NULL), 
   m_pScoreControl(NULL)
{
	AddFontResource("01 Digitall.ttf");
	m_pFont = new CGameFont;
	m_pFont->CreateFont("01 Digitall", 20, FW_NORMAL);

	m_pScoreControl = new CTextControl(m_pFont,TRectanglei(0, 100, 0, 200));
	m_pScoreControl->SetAlignement(CTextControl::TACenter);
	m_pScoreControl->SetTextColor(1.0f,0.588f,0.039f);
}

CPlayState::~CPlayState()
{
	if (m_pFont)
	{
		delete m_pFont;
		m_pFont = NULL;
	}
	RemoveFontResource("01 Digitall.ttf");
}

CPlayState* CPlayState::GetInstance(CStateManager* pManager)
{
	static CPlayState Instance(pManager);
	return &Instance;
}

void CPlayState::OnSize(int width, int height) 
{
	bool initFinished = (m_windowWidth < 0 && width > 0);

	m_windowWidth = width;
	m_windowHeight = height;
	m_circleSet.SetFieldHeight(double(height) / width);
	if (initFinished)
		InitNewGame();
}

void CPlayState::InitNewGame()
{
	// TODO srand(GetTickCount());
	m_curLevel = 1;
	m_curScore = 0;

	for (int i = 0; i < 3; i++)
		AddRandomCircle();
}

void CPlayState::Reset()
{
}

void CPlayState::AddRandomCircle()
{
  TCircle newCircle;
	double sizeMult = 1.0 / (1 + (m_curLevel - 1) / 10.0);
	double speedMult = 1 + (m_curLevel - 1) / 5.0;
	double radius = (0.1 + double(rand()) / RAND_MAX / 6.0) * sizeMult;

	if (radius > 1)
		radius = 1;
	newCircle.radius = radius;
	newCircle.y = m_circleSet.GetFieldHeight() - radius;
	newCircle.x = double(rand()) / RAND_MAX * (1 - radius);
	newCircle.color = ((rand() * 128 / RAND_MAX + 128) << 16) +  // TODO: сделать превалирование цветов радуги или что-нибудь в этом духе
		                ((rand() * 128 / RAND_MAX + 128) << 8) +
										(rand() * 128 / RAND_MAX + 128);
	newCircle.speedY = 0.1 / radius * speedMult;  
	  // По умолчанию кружок радиусом 1/10 игрового поля пройдёт его за 9 секунд
	m_circleSet.Add(newCircle);
	// TODO: проверять коллизии
	// TODO? было бы прикольно, если бы коллизии проверялись и по ходу игры,
	// но это надо менять игровую механику - в задании написано "двигаются без ускорения"

	//newCircle.x = 0.01;  //d_
	//newCircle.y = 0.99;
	//newCircle.radius = 0.1;
	//m_circleSet.Add(newCircle);
}

void CPlayState::OnKeyDown(WPARAM wKey)
{
	switch (wKey)
	{
	case VK_ESCAPE:
		PostQuitMessage(0);
		break;
	}
}

void CPlayState::Update(double dt)
{
	m_circleSet.MoveAll(dt);

	m_curScore++; //d_
}

void CPlayState::Draw()  
{ 
	// Рисуем игровое поле. Проекцируем на имеющееся окно прямоугольник
	// (0, 0) - (1, m_circleSet.GetFieldHeight())
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslated(-1, -1, 0);
	glScaled(2, 2.0 / m_circleSet.GetFieldHeight(), 1);
//	glOrtho(0, 1, 1.0 - double(m_windowHeight) / m_windowWidth, 1, -1.0, 1.0);
	DrawField();    // Проверочный метод
	DrawCircles();

	// Печатаем информацию. Работаем в координатах (0, 0) - (windowWidth, windowHeight)
	glLoadIdentity();
	glOrtho(0, m_windowWidth, 0, m_windowHeight, -1.0, 1.0);
	stringstream ssScore;
	ssScore << m_curScore;
	m_pScoreControl->SetText(ssScore.str());
	m_pScoreControl->Draw();
}

void CPlayState::DrawField()
{
	const double d = 0.005;

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_FAN);
	glColor3b(30, 80, 30);
	glVertex2d(d, d);
	glVertex2d(d, m_circleSet.GetFieldHeight() - d);
	glVertex2d(1 - d, m_circleSet.GetFieldHeight() - d);
	glVertex2d(1 - d, d);
	glEnd();
}

void CPlayState::DrawCircles()
{
	const CCircleSet::TCircleList& circles = m_circleSet.GetCurCircles();

	glDisable(GL_TEXTURE_2D);
	for (CCircleSet::TCircleList::const_iterator it = circles.begin(); it != circles.end(); it++)
	{
		const TCircle& circle = *it;

		glBegin(GL_TRIANGLE_FAN);
		glColor3b(circle.color, 100, 100);
		glVertex2d(circle.x, circle.y);
		for (int deg = 0; deg <= 360; deg += 30)
		{
			double x = circle.x + circle.radius * cos(double(deg) / 180 * M_PI);
			double y = circle.y + circle.radius * sin(double(deg) / 180 * M_PI);

			glVertex2d(x, y);
		}
		glEnd();
	}
	
}

//void CPlayState::OnStartRemoveLines()
//{
//	m_pComboControl->Pause();
//}
//
//void CPlayState::OnLinesRemoved(int iLinesCount)
//{
//	m_iTotalLines += iLinesCount;
//	int comboMultiplier = m_pComboControl->GetMultiplier();
//	switch (iLinesCount)
//	{
//	case 1:
//		m_ulCurrentScore += (m_iCurrentLevel+1) * 40 * comboMultiplier;
//		break;
//	case 2:
//		m_ulCurrentScore += (m_iCurrentLevel+1) * 100 * comboMultiplier;
//		break;
//	case 3:
//		m_ulCurrentScore += (m_iCurrentLevel+1) * 300 * comboMultiplier;
//		break;
//	case 4:
//		m_ulCurrentScore += (m_iCurrentLevel+1) * 1200 * comboMultiplier;
//		break;
//	}
//
//	if (m_iTotalLines/10 > m_iCurrentLevel)
//	{
//		m_iCurrentLevel++;
//		int iNewUpdateRate = (int)(m_pMatrix->GetTetradUpdate() * 0.8);
//		m_pMatrix->SetTetradUpdate(iNewUpdateRate);
//	}
//	m_pComboControl->IncreaseMultiplier();
//	m_pComboControl->Unpause();
//}
//
//void CPlayState::OnMatrixFull()
//{
//	m_bGameOver = true;
//	m_pComboControl->Pause();
//}
