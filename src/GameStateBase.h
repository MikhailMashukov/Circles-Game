#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <Windows.h>

class CStateManager;

// —истема получаетс€ несколько громоздкой, у мен€ концептуально был один класс,
// который отвечал и за обработку клавиш и за то, идЄт ли игра. 
// ≈стественно, этот класс разбивалс€, например, на CBaseTetrisEngine и 
// CDXTrihalfEngine (“етрис с треугольничками вместо квадратов, реализованный 
// через DirectX). ј при необходимости из CBaseTetrisEngine можно было бы
// выделить CBaseGameEngine - если бы надо было написать что-то, отличное от “етриса.
// Ќо вообще иде€ с CGameState правильна€ - код дл€ реализацию меню игры,
// окна About и т.п. совершенно не св€зан с логикой собственно игры, так что
// очень желательно их разделить по разным классам

// Base class for the different states
// of the game.
// ѕо-моему, CGameStateBase - более правильное название, чем CGameState,
// не путаетс€ с CPlayState
class CGameStateBase
{
public:
	// Constructor
	CGameStateBase(CStateManager* pManager);
	// Destructor
	virtual ~CGameStateBase();

	// The different 'events' functions. Child classes can 
	// implement the ones in which they are interested in.
	// ƒействительно, не требуетс€ заставл€ть определ€ть все эти методы
	// в классах-наследниках, поэтому методы не чисто виртуальные
	virtual void OnSize(int , int )  { }
	virtual void OnKeyDown(WPARAM ) { }
	virtual void OnKeyUp(WPARAM )   { }
	virtual void OnChar(WPARAM )    { }
	virtual void OnMouseLButtonDown(int , int )  { }

	virtual void Update(double )  { }  
	            // ќбновить игровое состо€ние с учЄтом того, что прошло
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