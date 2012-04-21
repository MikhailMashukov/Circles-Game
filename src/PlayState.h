#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include "GameStateBase.h"
#include "CircleSet.h"
#include "GameFont.h"


#include "BlocksMatrix.h"
#include "ComboControl.h"
#include "TextControl.h"

class CPlayState : public CGameStateBase
{
	// � ���� ������ ����������� �������� ������ ���� - ��������� �������,
	// ������� � ����������� �����... ������������, ��������� �������� 
	// ����������� � ��������� ������ CCircleSet. ���� ����� ������ �� ����� 
	// ��� ����, OpenGL, ����� ������ � �.�.

public:
	~CPlayState();

	// Implementation of specific events
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
	void DrawCircles();

private:
	CCircleSet m_circleSet;
	int m_curLevel, m_curScore;



	// The blocks matrix class
	CBlocksMatrix* m_pMatrix;
	// The font used to draw text
	CGameFont* m_pFont;
	// The control in charge of the decreasing 
	// time for the combo score.
	CComboControl* m_pComboControl;

	// The text controls to display the current
	// information.
	CTextControl* m_pScoreControl;
	CTextControl* m_pLevelControl;
	CTextControl* m_pLinesControl;

	// The current number of lines completed
	int m_iTotalLines;
	// The current level
	int m_iCurrentLevel;
	// The current score
	ULONG m_ulCurrentScore;

	bool m_bGameOver;

	// The background image
};

#endif  // _PLAYSTATE_H_