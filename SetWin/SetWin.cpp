#include "SetWin.h"

SetWin::SetWin( Undo* undo, IGameState* gameState, SetLeds* setLeds ): 
    _undo( undo ), _gameState( gameState ), _setLeds( setLeds ) {}
SetWin::~SetWin() {}

void SetWin::execute( IPlayer* player ) {
    std::cout << "*** SetWin::execute() ***" << std::endl;
    _undo->memory();
    _setLeds->updateSets();
    std::cout << "setting player games to 0" << std::endl;
    player->setGames( 0 ); player->getOpponent()->setGames( 0 );
    std::cout << "updating set leds" << std::endl;
    _setLeds->updateSets(); 
    std::cout << "*** end of SetWin::execute() ***" << std::endl; }