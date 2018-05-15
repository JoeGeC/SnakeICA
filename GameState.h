#ifndef GAMESTATE_H
#define GAMESTATE_H

enum class EGameState
{
    eAtMenu,
    eInGame,
    eAtEndScreen,
    eAtHighScores,
};

class GameState
{
    public:
        GameState();
        void SetGameState(EGameState gameState);
        EGameState GetGameState();

    protected:

    private:
        EGameState m_gameState { EGameState::eAtMenu };

};

#endif // GAMESTATE_H
