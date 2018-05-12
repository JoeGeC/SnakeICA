#include "GameState.h"

GameState::GameState()
{
    //ctor
}

EGameState GameState::GetGameState()
{
    return m_gameState;
}

void GameState::SetGameState(EGameState gameState)
{
    m_gameState = gameState;
}
