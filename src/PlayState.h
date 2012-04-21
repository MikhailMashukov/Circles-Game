#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include "GameStateBase.h"
#include "CircleSet.h"
#include "GameFont.h"

class CTextControl;
class CPlayState : public CGameStateBase
{
	// В этом классе реализована основная логика игры - обработка событий,
	// подсчёт и отображение очков... Единственное, хранилище объектов 
	// реализовано в отдельном классе CCircleSet. Этот класс вообще не знает 
	// про очки, OpenGL, клики мышкой и т.п.

public:
	~CPlayState();

	// Implementation of specific events
	void OnSize(int width, int height);
	void OnKeyDown(WPARAM wKey);
	void Update(double dt);
	void Draw();

	// Implementation of the CMatrixEventsListener class
	//void OnStartRemoveLines();
	//void OnLinesRemoved(int iLinesCount);
	//void OnMatrixFull();

	void Reset();
//	bool IsGameOver()  { return m_bGameOver; }

	// Returns the single instance
	static CPlayState* GetInstance(CStateManager* pManager);

protected:
	CPlayState(CStateManager* pManager);

	void InitNewGame();
	void AddRandomCircle();
	void DrawField();
	void DrawCircles();

private:
	CCircleSet m_circleSet;
	int m_curLevel, m_curScore;

	int m_windowWidth, m_windowHeight;
	// The font used to draw text
	CGameFont* m_pFont;
	// The text controls to display the current
	// information.
	CTextControl* m_pScoreControl;
};

#endif  // _PLAYSTATE_H_