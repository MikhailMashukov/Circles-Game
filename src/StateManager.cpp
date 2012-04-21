#include "StateManager.h"
#include "GameStateBase.h"

CStateManager::CStateManager() : m_pActiveState(NULL)
{
}

CStateManager::~CStateManager()
{
}

void CStateManager::OnSize(int width, int height)
{
	if (m_pActiveState)
		m_pActiveState->OnSize(width, height);
}

void CStateManager::OnKeyDown(WPARAM wKey)
{
	if (m_pActiveState)
		m_pActiveState->OnKeyDown(wKey);
}

void CStateManager::OnKeyUp(WPARAM wKey)
{
	if (m_pActiveState)
		m_pActiveState->OnKeyUp(wKey);
}

void CStateManager::OnChar(WPARAM wChar)
{
	if (m_pActiveState)
		m_pActiveState->OnChar(wChar);
}

void CStateManager::Update(double dt)
{
	if (m_pActiveState)
		m_pActiveState->Update(dt);
}

void CStateManager::Draw()
{
	if (m_pActiveState)
		m_pActiveState->Draw();
}

void CStateManager::OnMouseLButtonDown(int x, int y)
{
	if (m_pActiveState)
		m_pActiveState->OnMouseLButtonDown(x, y);
}