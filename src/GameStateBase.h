#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <Windows.h>

class CStateManager;

// ������� ���������� ��������� ����������, � ���� ������������� ��� ���� �����,
// ������� ������� � �� ��������� ������ � �� ��, ��� �� ����. 
// �����������, ���� ����� ����������, ��������, �� CBaseTetrisEngine � 
// CDXTrihalfEngine (������ � ��������������� ������ ���������, ������������� 
// ����� DirectX). � ��� ������������� �� CBaseTetrisEngine ����� ���� ��
// �������� CBaseGameEngine - ���� �� ���� ���� �������� ���-��, �������� �� �������.
// �� ������, ���� � CGameState ����������, - ��� ��� ���������� ���� ����,
// ���� About � �.�. ���������� �� ������ � ������� ���������� ����, ��� ���
// ����� ���������� �� ��������� �� ������ �������. ������� � ��� �������

// Base class for the different states
// of the game.
// ��-�����, CGameStateBase - ����� ���������� ��������, ��� CGameState,
// �� �������� � CPlayState
class CGameStateBase
{
public:
	// Constructor
	CGameStateBase(CStateManager* pManager);
	// Destructor
	virtual ~CGameStateBase();

	// The different 'events' functions. Child classes can 
	// implement the ones in which they are interested in.
	// �������������, �� ��������� ���������� ���������� ��� ��� ������
	// � �������-�����������, ������� ������ �� ����� �����������
	virtual void OnSize(int , int )  { }
	virtual void OnKeyDown(WPARAM ) { }
	virtual void OnKeyUp(WPARAM )   { }
	virtual void OnChar(WPARAM )    { }
	virtual void OnMouseLButtonDown(int , int )  { }

	virtual void Update(double )  { }  
	            // �������� ������� ��������� � ������ ����, ��� ������
	            // ��������� ���������� ������
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