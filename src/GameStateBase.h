#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <Windows.h>

class CStateManager;

// Система получается несколько громоздкой, у меня концептуально был один класс,
// который отвечал и за обработку клавиш и за то, идёт ли игра. 
// Естественно, этот класс разбивался, например, на CBaseTetrisEngine и 
// CDXTrihalfEngine (Тетрис с треугольничками вместо квадратов, реализованный 
// через DirectX). А при необходимости из CBaseTetrisEngine можно было бы
// выделить CBaseGameEngine - если бы надо было написать что-то, отличное от Тетриса.
// Но вообще, идея с CGameState правильная, - код для реализацию меню игры,
// окна About и т.п. совершенно не связан с логикой собственно игры, так что
// очень желательно их разделить по разным классам. Поэтому я это оставил

// Base class for the different states
// of the game.
// По-моему, CGameStateBase - более правильное название, чем CGameState,
// не путается с CPlayState
class CGameStateBase
{
public:
	// Constructor
	CGameStateBase(CStateManager* pManager);
	// Destructor
	virtual ~CGameStateBase();

	// The different 'events' functions. Child classes can 
	// implement the ones in which they are interested in.
	// Действительно, не требуется заставлять определять все эти методы
	// в классах-наследниках, поэтому методы не чисто виртуальные
	virtual void OnSize(int , int )  { }
	virtual void OnKeyDown(WPARAM ) { }
	virtual void OnKeyUp(WPARAM )   { }
	virtual void OnChar(WPARAM )    { }
	virtual void OnMouseLButtonDown(int , int )  { }

	virtual void Update(double )  { }  
	            // Обновить игровое состояние с учётом того, что прошло
	            // указанное количество секунд
	virtual void Draw()  { }

	// Functions called when the state is entered or left
	// (transition from/to another state).
	virtual void EnterState()  { }
	virtual void LeaveState()   { }

protected:
	// Helper function to switch to a new active state.
	void ChangeState(CGameStateBase* pNewState);

	// The state manager.
	CStateManager* m_pStateManager;
};

#endif  // _GAMESTATE_H_