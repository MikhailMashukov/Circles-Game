#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include "GameStateBase.h"

// Объект класса CMainWindow общается с объектом этого класса, 
// а последний отслеживает текущий режим игры и передаёт
// события объекту, отвечающему за текущий режим
class CStateManager
{
public:
	// Default constructor
	CStateManager();
	// Default destructor
	~CStateManager();

	// Switches to another active state.
	void ChangeState(CGameStateBase* pNewState)
	{
		if (m_pActiveState)
			m_pActiveState->LeaveState();
		m_pActiveState = pNewState;
		m_pActiveState->EnterState();
	}

	// Returns the current active state.
	CGameStateBase* GetActiveState()  { return m_pActiveState; }

	// 'Events' function, they are simply redirected to
	// the active state.
	void OnSize(int width, int height);
	void OnKeyDown(WPARAM wKey);
	void OnKeyUp(WPARAM wKey);
	void OnChar(WPARAM wChar);
	void OnMouseLButtonDown(int x, int y);

	void Update(double dt);
	void Draw();

private:
	// Active State of the game (intro, play, ...)
	CGameStateBase* m_pActiveState;		
};

#endif  // _STATEMANAGER_H_