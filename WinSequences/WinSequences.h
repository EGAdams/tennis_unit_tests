#ifndef MODE_1_WIN_SEQUENCES_H
#define MODE_1_WIN_SEQUENCES_H

#include "../Arduino/Arduino.h"
#include "../TennisConstants/TennisConstants.h"
#include "../GameLeds/GameLeds.h"
#include "../GameState/GameState.h"
#include "../GameTimer/GameTimer.h"
#include "../GameWinSequence/GameWinSequence.h"
#include "../PointLeds/PointLeds.h"
#include "../PinInterface/PinInterface.h"
#include "../Player/Player.h"
#include "../Reset/Reset.h"
#include "../SetLeds/SetLeds.h"
#include "../MatchWinSequence/MatchWinSequence.h"
#include "../Undo/Undo.h"
#include "../ScoreBoard/ScoreBoard.h"
#include "../SetWin/SetWin.h"

class WinSequences {
 public:
    WinSequences(  IPlayer* player1,
                   IPlayer* player2,
                   IPinInterface* pinInterface,
                   IGameState* gameState);
    ~WinSequences();
    void setScoreBoards( ScoreBoard* scoreBoard );
    void p1GameWinSequence();
    void p1SetWinSequence();
    void p1MatchWinSequence();
    void p2GameWinSequence();
    void p2SetWinSequence();
    void p2MatchWinSequence();
    void p1TBGameWinSequence();
    void p2TBGameWinSequence();
    void p1TBSetWinSequence();
    void p2TBSetWinSequence();
    void p1SetTBWinSequence();
    void p2SetTBWinSequence();
    void p1TBMatchWinSequence();
    void p2TBMatchWinSequence();
    void tieLEDsOn();
    void tieLEDsOff();

 private:
    IPlayer* _player1;
    IPlayer* _player2;
    IPinInterface* _pinInterface;
    IGameState* _gameState;
    PointLeds _pointLeds;
    GameLeds _gameLeds;
    SetLeds _setLeds;
    Reset _reset;
    Undo _undo;
    SetWin* _setWin;
    ScoreBoard* _scoreBoard; };
#endif