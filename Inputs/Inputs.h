#ifndef Inputs_h
#define Inputs_h

#include "../Arduino/Arduino.h"
#include "../GameState/GameState.h"
#include "../GameTimer/GameTimer.h"
#include "../PinInterface/PinInterface.h"
#include "../Inputs/Inputs.h"
#include "../Logger/Logger.h"
#include "../Reset/Reset.h"

class Inputs {
 public:
  Inputs( IPlayer* player1,
          IPlayer* player2,
          IPinInterface* pinInterface,
          IGameState* gameState);
  ~Inputs();
  void readReset();
  void readUndoButton();
  int readRotary();
  void readPlayerButtons();

 private:
  IPlayer* _player1;
  IPlayer* _player2;
  IPinInterface* _pinInterface;
  IGameState* _gameState;
  Reset _reset;
  Logger* _logger;
};

#endif
