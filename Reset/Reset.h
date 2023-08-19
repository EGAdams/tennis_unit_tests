#ifndef RESET_h
#define RESET_h

#include "../Arduino/Arduino.h"
#include "../GameState/GameState.h"
#include "../GameTimer/GameTimer.h"
#include "../PinInterface/PinInterface.h"
#include "../Logger/Logger.h"
#include "../TennisConstants/TennisConstants.h"
#include "../PinInterface/PinInterface.h"

class Reset {
 public:
  Reset( IPlayer* player1,
         IPlayer* player2,
         IPinInterface* pinInterface,
         IGameState* gameState);
  ~Reset();
  void resetScoreboard();
  void zeroPlayerValues();
  void refresh();
  void tieLEDsOn();
  void tieLEDsOff();

 private:
  IPlayer* _player1;
  IPlayer* _player2;
  IPinInterface* _pinInterface;
  IGameState* _gameState;
  Logger* _logger;
};

#endif
