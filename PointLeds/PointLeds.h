#ifndef PointLeds_h
#define PointLeds_h

#include "../GameState/GameState.h"
#include "../PinInterface/IPinInterface.h"
#include "../Player/Player.h"
#include "../Arduino/Arduino.h"
#include "../ScoreBoard/ScoreBoard.h"

class PointLeds {
 public:
  PointLeds( IPlayer* player1, IPlayer* player2, IPinInterface* pinInterface );
  PointLeds( IPlayer* player1, IPlayer* player2, ScoreBoard*   scoreBoard   );
  ~PointLeds();
  void updatePoints();
  void updateTBPoints();
  void setScoreBoard( ScoreBoard* scoreBoard );

 private:
  IPlayer* _player1;
  IPlayer* _player2;
  IPinInterface* _pinInterface;
  ScoreBoard* _scoreBoard;
};

#endif