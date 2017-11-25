#include "Game.h"
#include "Application.h"
#include "Drawer.h"
#include "Image.h"

const int FPS = 30;
const int START_TIME = 60 * FPS;
const std::array< int, MAX_PLAYER > INIT_SCORE = { 0 };
const int DRAW_SCORE1_X = SPRITE_SIZE;
const int DRAW_SCORE2_X = WIDTH - SPRITE_SIZE * 5;
const int DRAW_TIME_X = WIDTH / 2 - SPRITE_SIZE / 2;
const int DRAW_NUM_Y = HEIGHT - SPRITE_SIZE;

GamePtr Game::getTask( ) {
	return std::dynamic_pointer_cast< Game >( Application::getInstance( )->getTask( getTag( ) ) );
}

Game::Game( ) :
_time ( START_TIME ),
_score( INIT_SCORE ),
_scene( SCENE_STAGE ) {
}

Game::~Game( ) {
}

void Game::initialize( ) {
	DrawerPtr drawer = Drawer::getTask( );
	_number = drawer->createImage( "num.png" );
	_player_name = drawer->createImage( "playerName.png" );
}

void Game::update( ) {
	_time--;
	draw( );
}

void Game::draw( ) const {
	const int NUM_SIZE = 10;
	const int NUM[ NUM_SIZE ] = { 9, 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	{ // time
		const int TIME = _time / FPS;
		const int DIGIT = ( int )log10( TIME ) + 1;

		for ( int i = 0; i < DIGIT; i++ ) {
			int divided = 10 * ( DIGIT - 1 - i );
			if ( divided < 1 ) divided = 1;
			int tx = NUM[ ( TIME / divided ) % NUM_SIZE ] * SPRITE_SIZE;
			int ty = 0;
			_number->setRect( tx, ty, SPRITE_SIZE, SPRITE_SIZE );
			int adjust_pos = i * SPRITE_SIZE - ( DIGIT - 1 ) * SPRITE_SIZE / 2;
			_number->setPos( DRAW_TIME_X + adjust_pos, DRAW_NUM_Y );
			_number->draw( );
		}
	}
	//player score
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		const int DIGIT = ( int )log10( _score[ i ] ) + 1;
		for ( int j = 0; j < DIGIT; j++ ) {
			int divided = 10 * ( DIGIT - 1 - j );
			if ( divided < 1 ) divided = 1;
			int tx = NUM[ ( _score[ i ] / divided ) % NUM_SIZE ] * SPRITE_SIZE;
			int ty = 0;
			_number->setRect( tx, ty, SPRITE_SIZE, SPRITE_SIZE );
			int sx = i ? DRAW_SCORE2_X : DRAW_SCORE1_X;
			_number->setPos( sx + j * SPRITE_SIZE, DRAW_NUM_Y );
			_number->draw( );
		}
		{
			_number->setRect( NUM[ 0 ] * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE );
			int sx = i ? DRAW_SCORE2_X : DRAW_SCORE1_X;
			_number->setPos( sx + DIGIT * SPRITE_SIZE, DRAW_NUM_Y );
			_number->draw( );
		}
	}
	{ //player name
		const int TW = 224;
		const int TH = 64;
		// player1
		_player_name->setRect( 0, 0, TW, TH );
		_player_name->setPos( DRAW_SCORE1_X, DRAW_NUM_Y - TH );
		_player_name->draw( );
		// player2
		_player_name->setRect( 0, 1 * TH, TW, TH );
		_player_name->setPos( DRAW_SCORE2_X, DRAW_NUM_Y - TH );
		_player_name->draw( );
	}
}

void Game::setNextScene( SCENE scene ) {
	_scene = scene;
}

Game::SCENE Game::getNowScene( ) const {
	return _scene;
}

void Game::addScore( PLAYER idx, int score ) {
	_score[ idx ] += score;
}

int Game::getGameTime( ) const {
	return _time;
}
