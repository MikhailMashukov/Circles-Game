#include "PlayState.h"
#include "StateManager.h"
#include "MenuState.h"
#include "HighScoreState.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include <windows.h>

using namespace std;

CPlayState::CPlayState(CStateManager* pManager)
 : CGameStateBase(pManager), m_pMatrix(NULL), m_pFont(NULL), 
   m_pComboControl(NULL), m_pScoreControl(NULL), 
   m_pLevelControl(NULL), m_pLinesControl(NULL)
{
	Reset();

	AddFontResource("01 Digitall.ttf");
	m_pMatrix = new CBlocksMatrix(NULL,280,34);
	m_pFont = new CGameFont;
	m_pFont->CreateFont("01 Digitall", 20, FW_NORMAL);

	m_pComboControl = new CComboControl(TRectanglei(330,450,50,235),m_pFont);
	m_pScoreControl = new CTextControl(m_pFont,TRectanglei(145,210,620,730));
	m_pScoreControl->SetAlignement(CTextControl::TACenter);
	m_pScoreControl->SetTextColor(1.0f,0.588f,0.039f);
}

CPlayState::~CPlayState()
{
	if (m_pMatrix)
	{
		delete m_pMatrix;
		m_pMatrix = NULL;
	}

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

void CPlayState::Reset()
{
	// TODO srand(GetTickCount());
	m_curLevel = 1;
	m_curScore = 0;

	for (int i = 0; i < 3; i++)
		AddRandomCircle();
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
	newCircle.y = 1 - radius;
	newCircle.x = double(rand()) / RAND_MAX * (1 - radius);
	newCircle.color = ((rand() * 128 / RAND_MAX + 128) << 16) +  // TODO: сделать превалирование цветов радуги или что-нибудь в этом духе
		                ((rand() * 128 / RAND_MAX + 128) << 8) +
										(rand() * 128 / RAND_MAX + 128);
	newCircle.speedY = 0.1 / radius * speedMult;  
	  // ѕо умолчанию кружок радиусом 1/10 игрового пол€ пройдЄт его за 9 секунд
	m_circleSet.Add(newCircle);
	// TODO: провер€ть коллизии
	// TODO? было бы прикольно, если бы коллизии провер€лись и по ходу игры,
	// но это надо мен€ть игровую механику - в задании написано "двигаютс€ без ускорени€"

}

void CPlayState::OnKeyDown(WPARAM wKey)
{
	switch (wKey)
	{
	case VK_UP:
		if (!m_bGameOver)
			m_pMatrix->ShapeRotate();
		break;
	case VK_DOWN:
		if (!m_bGameOver)	
			m_pMatrix->ShapeDown();
		break;
	case VK_LEFT:
		if (!m_bGameOver)
			m_pMatrix->ShapeLeft();
		break;
	case VK_RIGHT:
		if (!m_bGameOver)
			m_pMatrix->ShapeRight();
		break;
	case VK_ESCAPE:
//		ChangeState(CMenuState::GetInstance(m_pStateManager));
		break;
	// case VK_RETURN:
	//	if (m_bGameOver)
	//	{
	//		CHighScoreState* pHighScores = 
	//			CHighScoreState::GetInstance(m_pStateManager);
	//		pHighScores->SetNewHighScore(m_ulCurrentScore);
	//		ChangeState(pHighScores);
	//	}
	}
}

void CPlayState::Update(double dt)
{
	m_circleSet.MoveAll(dt);

		if (!m_bGameOver)
	{
		m_pMatrix->Update(GetTickCount());
		m_pComboControl->Update(GetTickCount());
	}

}

void CPlayState::Draw()  
{ 
	DrawCircles();


	m_pMatrix->Draw();

	stringstream ssScore;
	ssScore << m_ulCurrentScore;
	m_pScoreControl->SetText(ssScore.str());
	m_pScoreControl->Draw();
	
	//stringstream ssLines;
	//ssLines << m_iTotalLines;
	//m_pLinesControl->SetText(ssLines.str());
	//m_pLinesControl->Draw();

	//stringstream ssLevel;
	//ssLevel << m_iCurrentLevel;
	//m_pLevelControl->SetText(ssLevel.str());
	//m_pLevelControl->Draw();

	//if (m_pMatrix->GetNextShape())
	//	m_pMatrix->GetNextShape()->DrawOnScreen(TRectanglei(165,220,80,225));

	//m_pComboControl->Draw();
	//if (m_bGameOver)
	//{
	//	// In game over, we draw a semi-transparent black screen on top
	//	// of the background. This is possible because blending has 
	//	// been enabled.
	//	glColor4f(0.0,0.0,0.0,0.5);
	//	// Disable 2D texturing because we want to draw a non
	//	// textured rectangle over the screen.
	//	glDisable(GL_TEXTURE_2D);
	//	glBegin(GL_QUADS);
	//	glVertex3i(0,0,0);
	//	glVertex3i(0,600,0);
	//	glVertex3i(800,600,0);
	//	glVertex3i(800,0,0);
	//	glEnd();
	//	glEnable(GL_TEXTURE_2D);

	//	m_pFont->DrawText("GAME OVER",340,200);
	//	m_pFont->DrawText("Press Enter to continue",285,300);
	//}

}

void CPlayState::DrawCircles()
{
	const CCircleSet::TCircleList& circles = m_circleSet.GetCurCircles();

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINE_STRIP);
	for (CCircleSet::TCircleList::const_iterator it = circles.begin(); it != circles.end(); it++)
	{
		const TCircle& circle = *it;

		glColor3i(circle.color, 100, 100);
		for (int deg = 0; deg <= 360; deg += 30)
		{
			double x = circle.x + circle.radius * cos(double(deg) / 180 * M_PI);
			double y = circle.y + circle.radius * 300 * sin(double(deg) / 180 * M_PI);

			glVertex2f(x, y);
		}
	}
	glEnd();
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
