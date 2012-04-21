#include "PlayState.h"
#include "StateManager.h"
#include "TextControl.h"
#include <assert.h>
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

	m_pScoreControl = new CTextControl(m_pFont,TRectanglei(0, 45, 20, 300));
	m_pScoreControl->SetAlignement(CTextControl::TALeft);
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
	srand(GetTickCount());
	m_curLevel = 1;
	m_curScore = 0;
	m_curLevelBlownCircleCount = 0;

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
	double radius = (0.05 + double(rand()) / RAND_MAX / 12.0) * sizeMult;

	if (radius > 0.5)
		radius = 0.5;
	if (radius > m_circleSet.GetFieldHeight() / 2)
		radius = m_circleSet.GetFieldHeight() / 2;
	newCircle.radius = radius;
	newCircle.y = m_circleSet.GetFieldHeight() - radius;
	newCircle.x = double(rand()) / RAND_MAX * (1 - radius * 2) + radius;
	newCircle.color = RGB(rand() * 100 / RAND_MAX + 100,  
		                    rand() * 155 / RAND_MAX + 100,
												rand() * 128 / RAND_MAX + 128);
	// TODO: сделать превалирование цветов радуги или что-нибудь в этом духе
	newCircle.speedY = -0.005 / radius * speedMult;  
	  // ѕо умолчанию кружок диаметром 1/10 игрового пол€ пройдЄт его за 9 секунд
	  // (не за 10 потому что центр кружка проходит меньше, чем всЄ поле)
	m_circleSet.Add(newCircle);
	// TODO: провер€ть коллизии
	// TODO? было бы прикольно, если бы коллизии провер€лись и по ходу игры,
	// но это надо мен€ть игровую механику - в задании написано "двигаютс€ без ускорени€"
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

	double probabilityMult = m_curLevel;

	if (m_circleSet.GetCurCircles().size() < 3)
		probabilityMult *= sqrt(double(4 - m_circleSet.GetCurCircles().size()));

	  // ¬еро€тность такова, что на первом уровне сложности должен по€вл€тьс€
	  // примерно один круг в секунду
	if (rand() < RAND_MAX * dt * probabilityMult)
		AddRandomCircle();
}

void CPlayState::Draw()  
{ 
	// –исуем игровое поле. ѕроецируем на имеющеес€ окно пр€моугольник
	// (0, 0) - (1, m_circleSet.GetFieldHeight())
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslated(-1, -1, 0);
	glScaled(2, 2.0 / m_circleSet.GetFieldHeight(), 1);
//	DrawField();    // ѕроверочный метод
	DrawCircles();

	// ѕечатаем информацию. –аботаем в координатах (0, 0) - (windowWidth, windowHeight)
	glLoadIdentity();
	glOrtho(0, m_windowWidth, 0, m_windowHeight, -1.0, 1.0);
	stringstream ssScore;
	ssScore << "Your score:  " << m_curScore;
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
		double r = circle.radius;

		glBegin(GL_TRIANGLE_FAN);
		switch (circle.state)
		{
			case TCircle::csFalling:
				glColor3ub(GetRValue(circle.color), GetGValue(circle.color), GetBValue(circle.color));
				break;

			case TCircle::csBlowing:
				{
					double mult = (1 + pow(circle.curStateTime / TCircle::c_blowTime, 4) * 2) / 255;

					r += 0.2 * pow(1.0 + circle.curStateTime / TCircle::c_blowTime, 2) / 8;
					glColor3d(GetRValue(circle.color) * mult, 
						        GetGValue(circle.color) * mult, 
										GetBValue(circle.color) * mult);
				}
				break;

			case TCircle::csDisappearing:
				{
					double alpha = 255.0 / (1 + pow(circle.curStateTime / TCircle::c_disappearTime, 2));

					glColor4ub(GetRValue(circle.color), GetGValue(circle.color), GetBValue(circle.color),
										 GLubyte(alpha));
				}
				break;

			default:
				assert(0);
		}

		int faceCount = int(m_windowWidth * r) / 8 * 4;

		if (faceCount < 20)
			faceCount = 20;

		double angleStep = 2 * M_PI / faceCount;

		glVertex2d(circle.x, circle.y);
		for (double angle = 0; angle <= 2 * M_PI + 0.0001; angle += angleStep)
		{
			double x = circle.x + r * cos(angle);
			double y = circle.y + r * sin(angle);

			glVertex2d(x, y);
		}
		glEnd();
	}
	
}

void CPlayState::OnMouseLButtonDown(int x, int y)
{
	double dx = double(x) / m_windowWidth;
	double dy = double(m_windowHeight - y) / m_windowWidth;
	TCircle blownCircle;

	if (m_circleSet.BlowCircleAtPoint(blownCircle, dx, dy))
	{
		m_curScore += int(0.1 / pow(blownCircle.radius, 1.5) * (1 + m_curLevel * 0.3) + 0.5);
		if (m_curLevelBlownCircleCount <= m_curLevel * 2)
			m_curLevelBlownCircleCount++;
		else
		{
			m_curLevel++;
			m_curLevelBlownCircleCount = 0;
		}
	}
}