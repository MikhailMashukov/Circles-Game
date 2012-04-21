#include "GameStateBase.h"
#include "StateManager.h"

CGameStateBase::CGameStateBase(CStateManager* pManager)
  : m_pStateManager(pManager)
{
}

CGameStateBase::~CGameStateBase()
{
}

void CGameStateBase::ChangeState(CGameStateBase* pNewState)
{
	m_pStateManager->ChangeState(pNewState);
}