#include "Pacman.h"
#include "define.h"
#include "Game.h"
#include "Map.h"
#include "Drawer.h"
#include "Image.h"
#include "Keyboard.h"
#include <assert.h>

const int SPRITE_SIZE = 64;
const int DRAW_SIZE = CHIP_SIZE;
const int MOVE_SPEED = 3;
const int MAX_SPEED = 8;
const int WAIT_ANIM_TIME = 5;
const int ANIM_NUM = 3;

Pacman::Pacman( int id, const Vector& pos  ) :
Character( pos ),
_id( id ),
_auto_move( false ),
_turnaround( false ) {
	if ( id == 0 ) {
		_sprite = Drawer::getTask( )->createImage( "player1.png" );
	}
	if ( id == 1 ) {
		_sprite = Drawer::getTask( )->createImage( "player2.png" );
	}
	assert( id == 0 || id == 1 );
}


Pacman::~Pacman( ) {
}

void Pacman::act( ) {
	if ( !_auto_move ) {
		actOnMove( );
		actOnEat( );
		actOnWarp( );
	} else {
		actOnAutoMove( );
	}
}

void Pacman::actOnMove( ) {
	Vector vec = getVec( );
	KeyboardPtr key = Keyboard::getTask( );
	bool brake = true;
	if ( key->isHoldKey( _id == 0 ? "A" : "ARROW_LEFT" ) ) {
		vec.x -= MOVE_SPEED;
		brake = false;
	}
	if ( key->isHoldKey( _id == 0 ? "D" : "ARROW_RIGHT" ) ) {
		vec.x += MOVE_SPEED;
		brake = false;
	}
	if ( key->isHoldKey( _id == 0 ? "W" : "ARROW_UP" ) ) {
		vec.y -= MOVE_SPEED;
		brake = false;
	}
	if ( key->isHoldKey( _id == 0 ? "S" : "ARROW_DOWN" ) ) {
		vec.y += MOVE_SPEED;
		brake = false;
	}

	if ( brake ) {
		double brake_ratio = vec.getLength( ) - MOVE_SPEED;
		if ( brake_ratio < 0 ) {
			brake_ratio = 0;
		}
		vec = vec.normalize( ) * brake_ratio;
	}

	if ( vec.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
		vec = vec.normalize( ) * MAX_SPEED;
	}
	setVec( vec );
}

void Pacman::actOnEat( ) {
	MapPtr map = Game::getTask( )->getMap( );
	Vector check = getPos( ) + Vector( 0, -CHIP_SIZE / 2 );
	unsigned char obj = map->getObject( check );
	if ( obj == OBJECT_ENHANCE_FEED || obj == OBJECT_FEED ) {
		map->eatFeed( check );
	}
	if ( obj == OBJECT_ENHANCE_FEED ) {
		_turnaround = true;
	}
}

void Pacman::actOnWarp( ) {
	MapPtr map = Game::getTask( )->getMap( );
	Vector check = getPos( ) + Vector( 0, -CHIP_SIZE / 2 );
	unsigned char obj = map->getObject( check );
	if ( obj == OBJECT_STAGE_WARP ) {
		_auto_move = true;
		setColl( false );
			
		if ( getPos( ).x < CHIP_SIZE * MAP_WIDTH_CHIP_NUM / 2 ) {
			_auto_vec = Vector( -MAX_SPEED * 0.8, 0 );
		} else {
			_auto_vec = Vector( MAX_SPEED * 0.8, 0 );
		}
		setVec( _auto_vec );
	}
}

void Pacman::actOnAutoMove( ) {
	const int MAP_WIDTH = CHIP_SIZE * MAP_WIDTH_CHIP_NUM;
	bool automatic = true;
	Vector pos = getPos( );

	if ( _auto_vec.x < 0 ) {
		if ( pos.x < 0 ) {
			pos.x += MAP_WIDTH;
			setPos( pos );
		}
		if ( pos.x > MAP_WIDTH / 2 &&
			 pos.x < MAP_WIDTH - ( CHIP_SIZE * 3 ) / 2 ) {
			automatic = false;
		}
	} else {
		if ( pos.x > MAP_WIDTH ) {
			pos.x -= MAP_WIDTH;
			setPos( pos );
		}
		if ( pos.x < MAP_WIDTH / 2 &&
			 pos.x > CHIP_SIZE * 3 / 2 ) {
			automatic = false;
		}
	}

	if ( !automatic ) {
		_auto_move = false;
		setColl( true );
		_auto_vec = Vector( );
	}

	setVec( _auto_vec );
}

void Pacman::draw( ) const {
	Vector pos = getPos( );
	_sprite->setRect( ( ( getActTime( ) / WAIT_ANIM_TIME ) % ANIM_NUM ) * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE );
	int sx = ( int )( pos.x - DRAW_SIZE / 2 );
	int sy = ( int )( pos.y - DRAW_SIZE );
	_sprite->setPos( sx, sy, sx + DRAW_SIZE, sy + DRAW_SIZE );
	_sprite->draw( );
}
