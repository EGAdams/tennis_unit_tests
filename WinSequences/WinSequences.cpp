#include "WinSequences.h"

WinSequences::~WinSequences() {
    // std::cout << "*** WinSequences destructor called. ***" << std::endl;
    delete _setWin; }
    
WinSequences::WinSequences( IPlayer* player1, IPlayer* player2, IPinInterface* pinInterface,
                                      IGameState* gameState ): 
    _player1( player1 ), _player2( player2 ),
    _pinInterface( pinInterface ),
    _gameState( gameState ),
    _pointLeds( player1, player2, pinInterface ),
    _gameLeds( player1, player2, pinInterface ),
    _setLeds( player1, player2, pinInterface ),
    _reset( player1, player2, pinInterface, gameState ),
    _undo( player1, player2, pinInterface, gameState ) { 
        _setWin = new SetWin( &_undo, _gameState, &_setLeds );}

void WinSequences::setScoreBoards( ScoreBoard* scoreBoard ) {
    _pointLeds.setScoreBoard( scoreBoard );
    _gameLeds.setScoreBoard(  scoreBoard );
    _setLeds.setScoreBoard(   scoreBoard );
    _scoreBoard =             scoreBoard; } // set mine too!

void WinSequences::p1GameWinSequence() {
    // std::cout << "//////////////////////// p1GameWinSequence() ////////////////////////" << std::endl;
    GameWinSequence gameWinSequence; 
    gameWinSequence.run( _player1, _gameState, &_gameLeds, _scoreBoard, _player1->getGames());
    // std::cout << "*** inside WinSequences class.  p1GameWinSequence() ***" << std::endl;
    _undo.memory();
    // std::cout << "*** delaying game after p1GameWinSequence()... ***" << std::endl;
    GameTimer::gameDelay( 2000 );
    // std::cout << "*** done delaying game after p1GameWinSequence()  setting points to zero... ***" << std::endl;
    _player1->setPoints( 0 );
    _player2->setPoints( 0 );}

void WinSequences::p1SetWinSequence() { 
    std::cout << "*** executing _setWin->execute for player one... ***" << std::endl;
    _setWin->execute( _player1 ); }

void WinSequences::p1MatchWinSequence() {
    std::cout << "//////////////////////// p1MatchWinSequence() ////////////////////////" << std::endl;
    _undo.memory();
    _pointLeds.updateTBPoints();
    _player2->setGames( 5 );
    _gameLeds.updateGames();
    MatchWinSequence matchWinSequence; matchWinSequence.run( _player1, _gameState, &_gameLeds, &_setLeds );
    _reset.resetScoreboard();}

void WinSequences::p2GameWinSequence() {
    GameWinSequence gameWinSequence; 
    gameWinSequence.run( _player2, _gameState, &_gameLeds, _scoreBoard, _player2->getGames());
    std::cout << "*** inside WinSequences class.  executing p2GameWinSequence()... ***" << std::endl;
    _undo.memory();  
    // std::cout << "*** delaying game after p2GameWinSequence()... ***" << std::endl;
    GameTimer::gameDelay( 1000 );
    // std::cout << "*** done delaying game after p2GameWinSequence()  setting points to zero... ***" << std::endl;
    _player1->setPoints( 0 );
    _player2->setPoints( 0 );}

void WinSequences::p2SetWinSequence() { 
     std::cout << "*** executing _setWin->execute... ***" << std::endl;
    _setWin->execute( _player2 ); }   
    // _undo.memory();  does this go here?

void WinSequences::p2MatchWinSequence() {
    std::cout << "//////////////////////// p2MatchWinSequence() ////////////////////////" << std::endl;
    _undo.memory();               
    _pointLeds.updateTBPoints();
    _player1->setGames( 5 );
    _gameLeds.updateGames();      
    MatchWinSequence matchWinSequence; matchWinSequence.run( _player2, _gameState, &_gameLeds, &_setLeds );
    _reset.resetScoreboard();}

void WinSequences::p1TBGameWinSequence() {
    _undo.memory();
    if ( _scoreBoard->hasCanvas()) {
        GameWinSequence gameWinSequence; 
        gameWinSequence.run( _player1, _gameState, &_gameLeds, _scoreBoard, _player1->getGames());
    } else {
        for ( int currentPulseCount = 0; currentPulseCount < _gameState->getGameWinPulseCount(); 
                currentPulseCount++ ) {
                _player1->setSets( _gameState, 0 );
                _setLeds.updateSets();
                GameTimer::gameDelay( _gameState->getFlashDelay());
                _player1->setSets(    _gameState, _gameState->getP1SetsMem());
                _setLeds.updateSets();
                GameTimer::gameDelay( _gameState->getFlashDelay());}}
    tieLEDsOff();
    _gameState->setTieBreak( 0 );
    _player1->setGames( 0 );
    _player2->setGames( 0 );
    _gameLeds.updateGames();}

void WinSequences::p2TBGameWinSequence() {     
    _undo.memory();  
    if ( _scoreBoard->hasCanvas()) {     // the matrix is active
        GameWinSequence gameWinSequence; 
        gameWinSequence.run( _player2, _gameState, &_gameLeds, _scoreBoard, _player2->getGames());
    } else {
        for ( int currentPulseCount = 0;
            currentPulseCount < _gameState->getGameWinPulseCount();
            currentPulseCount++ ) {
            _player2->setSets( _gameState, 0 );
            _setLeds.updateSets();
            GameTimer::gameDelay( _gameState->getFlashDelay());
            _player2->setSets( _gameState, _gameState->getP2SetsMem());
            _setLeds.updateSets();
            GameTimer::gameDelay( _gameState->getFlashDelay()); }}
    tieLEDsOff();
    _gameState->setTieBreak( 0 );
    _player1->setGames( 0 );
    _player2->setGames( 0 );
    _gameLeds.updateGames(); }    

////////////////////////////////// SET WIN SEQUENCES //////////////////////////////////////////////
void WinSequences::p1TBSetWinSequence() {  // for entering set t/b
    _undo.memory();                               
    for ( int currentPulseCount = 0; currentPulseCount < SET_WIN_PULSE_COUNT; currentPulseCount++ ) {
        _player1->setSets( _gameState, 0 );
        tieLEDsOff();
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());
        _player1->setSets( _gameState, 1 );
        tieLEDsOn();
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());}
    _player1->setGames( 0 );
    _player2->setGames( 0 );
    tieLEDsOn();}

void WinSequences::p2TBSetWinSequence() {  // for entering set t/b
    _undo.memory();                               
    for ( int currentPulseCount = 0; currentPulseCount < SET_WIN_PULSE_COUNT; currentPulseCount++ ) {
        _player2->setSets( _gameState, 0 );
        tieLEDsOff();
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());
        _player2->setSets( _gameState, 1 );
        tieLEDsOn();
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());}
    _player1->setGames( 0 );
    _player2->setGames( 0 );
    tieLEDsOn();}
///////////////////////////// END OF SET WIN SEQUENCES ////////////////////////////////////////////


////////////////////////// SET TIE BREAKER WIN SEQUENCES //////////////////////////////////////////
void WinSequences::p1SetTBWinSequence() {  // for winning set t/b
    _undo.memory();                               

    for ( int currentPulseCount = 0; currentPulseCount < SET_WIN_PULSE_COUNT; currentPulseCount++ ) {
        _player1->setSets( _gameState, 0 );
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());
        _player1->setSets( _gameState, 3 );
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());}}

void WinSequences::p2SetTBWinSequence() {  // for winning set t/b
    _undo.memory();                               
    for ( int currentPulseCount = 0; currentPulseCount < SET_WIN_PULSE_COUNT; currentPulseCount++ ) {
        _player2->setSets( _gameState, 0 );
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());
        _player2->setSets( _gameState, 3 );
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());}}
//////////////////////// END OF SET TIE BREAKER WIN SEQUENCES /////////////////////////////////////

void WinSequences::p1TBMatchWinSequence() {
    _player2->setGames( 99 );
    _gameLeds.updateGames();  
    _undo.memory();           
    tieLEDsOff();
    MatchWinSequence matchWinSequence; matchWinSequence.run( _player1, _gameState, &_gameLeds, &_setLeds );
    _reset.resetScoreboard();}

void WinSequences::p2TBMatchWinSequence() {
    _player1->setGames( 99 );
    _gameLeds.updateGames();  
    _undo.memory();           
    tieLEDsOff();
    MatchWinSequence matchWinSequence; matchWinSequence.run( _player2, _gameState, &_gameLeds, &_setLeds );
    _reset.resetScoreboard();}

void WinSequences::tieLEDsOn() {
    _gameState->setTieLEDsOn( 1 );  // tieLEDsOn = true;
    _pinInterface->pinDigitalWrite( P1_TIEBREAKER, HIGH );
    _pinInterface->pinDigitalWrite( P2_TIEBREAKER, HIGH );}

void WinSequences::tieLEDsOff() {
    _gameState->setTieLEDsOn( 0 );  // tieLEDsOn = false;
    _pinInterface->pinDigitalWrite( P1_TIEBREAKER, LOW );
    _pinInterface->pinDigitalWrite( P2_TIEBREAKER, LOW );}
