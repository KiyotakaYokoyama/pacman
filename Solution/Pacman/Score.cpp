#include "Score.h"
#include "Image.h"

const std::array< int, MAX_PLAYER > INIT_SCORE = { 0 };
const int FPS = 30;
const int DRAW_SCORE1_X = SPRITE_SIZE;
const int DRAW_SCORE2_X = WIDTH - SPRITE_SIZE * 5;
const int DRAW_TIME_X = WIDTH / 2 - SPRITE_SIZE / 2;
const int DRAW_NUM_Y = HEIGHT - SPRITE_SIZE * 2;
const int INIT_SCORE_EFFECT_TIME = 25;
const int GAME_TIME = 120 * FPS;
const int NUM_SIZE = 10;
const int NUM[ NUM_SIZE ] = { 9, 0, 1, 2, 3, 4, 5, 6, 7, 8 };

Score::Score( ImagePtr number, ImagePtr player_name ) :
_battle_time( GAME_TIME ),
_score( INIT_SCORE ),
_number( number ),
_player_name( player_name ) {
}

Score::~Score( ) {
}

Score::PERFORMER::PERFORMER( ) :
time( 0 ),
player( PLAYER_1 ),
score( ( SCORE )0 ) {
}

Score::PERFORMER::PERFORMER( int time_, PLAYER player_, SCORE score_ ) :
time( time_ ),
player( player_ ),
score( score_ ) {
}

void Score::update( ) {
	_battle_time--;

	if ( !_performer.empty( ) ) {
		std::list< PERFORMER >::iterator ite = _performer.begin( );
		while ( ite != _performer.end( ) ) {
			PERFORMER * performer = &(*ite);
			performer->time--;

			if ( performer->time < 0 ) {
				ite = _performer.erase( ite );
				continue;
			}

			ite++;
		}
	}
}

void Score::draw( ) const {
	{ // time
		const int TIME = _battle_time / FPS;
		const int DIGIT = ( int )log10( TIME ) + 1;

		for ( int i = 0; i < DIGIT; i++ ) {
			int divided = ( int )pow( 10, DIGIT - 1 - i );
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
			int divided = ( int )pow( 10, DIGIT - 1 - j );
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

	drawScoreEffet( );

	{ //player name
		const int TW = 224;
		const int TH = 64;
		// player1
		_player_name->setRect( 0, 0, TW, TH );
		_player_name->setPos( DRAW_SCORE1_X, DRAW_NUM_Y + TH );
		_player_name->draw( );
		// player2
		_player_name->setRect( 0, 1 * TH, TW, TH );
		_player_name->setPos( DRAW_SCORE2_X, DRAW_NUM_Y + TH );
		_player_name->draw( );
	}
}

void Score::drawScoreEffet( ) const {
	if ( !_performer.empty( ) ) {
		std::list< PERFORMER >::const_iterator ite = _performer.begin( );
		while ( ite != _performer.end( ) ) {
			PERFORMER performer = *ite;
			const int DIGIT = ( int )log10( ( int )performer.score ) + 1;
			for ( int j = 0; j < DIGIT; j++ ) {
				int divided = 10 * ( DIGIT - 1 - j );
				if ( divided < 1 ) divided = 1;
				int tx = NUM[ ( ( int )performer.score / divided ) % NUM_SIZE ] * SPRITE_SIZE;
				int ty = 0;
				_number->setRect( tx, ty, SPRITE_SIZE, SPRITE_SIZE );
				int sx = performer.player ? DRAW_SCORE2_X : DRAW_SCORE1_X;
				int sy = DRAW_NUM_Y - ( ( INIT_SCORE_EFFECT_TIME - performer.time ) * 3 );
				_number->setPos( sx + j * SPRITE_SIZE, sy );
				_number->draw( );
			}
			{
				_number->setRect( NUM[ 0 ] * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE );
				int sx = performer.player ? DRAW_SCORE2_X : DRAW_SCORE1_X;
				int sy = DRAW_NUM_Y - ( ( INIT_SCORE_EFFECT_TIME - performer.time ) * 3 );
				_number->setPos( sx + DIGIT * SPRITE_SIZE, sy );
				_number->draw( );
			}
			ite++;
		}
	}
}

void Score::addScore( PLAYER idx, SCORE score ) {
	_score[ idx ] += score;
	if ( _score[ idx ] < 0 ) {
		_score[ idx ] = 0;
	}

	if ( ( int )score > 0 ) {
		_performer.push_back( PERFORMER( INIT_SCORE_EFFECT_TIME, idx, score ) );
	}
}

void Score::initialize( ) {
	_battle_time = GAME_TIME;
	_score = INIT_SCORE;
	_performer.clear( );
}

int Score::getScore( PLAYER idx ) const {
	return _score[ idx ];
}

bool Score::isFinished( ) const {
	return _battle_time < 0;
}
