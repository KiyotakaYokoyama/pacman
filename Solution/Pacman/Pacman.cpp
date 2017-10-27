#include "Pacman.h"
#include "define.h"
#include "Map.h"
#include "Drawer.h"
#include "Image.h"
#include "Keyboard.h"

const int SPRITE_SIZE = 64;
const int DRAW_SIZE = CHIP_SIZE;
const int MOVE_SPEED = 3;
const int MAX_SPEED = 8;
const int WAIT_ANIM_TIME = 5;
const int ANIM_NUM = 3;

Pacman::Pacman( Vector pos ) :
Character( pos ),
_turnaround( false ) {
	_sprite = Drawer::getTask( )->createImage( "player1.png" );
}


Pacman::~Pacman( ) {
}

void Pacman::act( ) {
	actOnMove( );
	actOnEat( );
}

void Pacman::actOnMove( ) {
	Vector vec = getVec( );
	KeyboardPtr key = Keyboard::getTask( );
	bool brake = true;
	if ( key->isHoldKey( "ARROW_LEFT" ) ) {
		vec.x -= MOVE_SPEED;
		brake = false;
	}
	if ( key->isHoldKey( "ARROW_RIGHT" ) ) {
		vec.x += MOVE_SPEED;
		brake = false;
	}
	if ( key->isHoldKey( "ARROW_UP" ) ) {
		vec.y -= MOVE_SPEED;
		brake = false;
	}
	if ( key->isHoldKey( "ARROW_DOWN" ) ) {
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
	MapPtr map = Map::getTask( );
	Vector check = getPos( ) + Vector( 0, -CHIP_SIZE / 2 );
	unsigned char obj = map->getObject( check );
	if ( obj == OBJECT_ENHANCE_FEED || obj == OBJECT_FEED ) {
		map->eatFeed( check );
	}
	if ( obj == OBJECT_ENHANCE_FEED ) {
		_turnaround = true;
	}
}

void Pacman::draw( ) const {
	Vector pos = getPos( );
	_sprite->setRect( ( ( getActTime( ) / WAIT_ANIM_TIME ) % ANIM_NUM ) * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE );
	int sx = ( int )( pos.x - DRAW_SIZE / 2 );
	int sy = ( int )( pos.y - DRAW_SIZE );
	_sprite->setPos( sx, sy, sx + DRAW_SIZE, sy + DRAW_SIZE );
	_sprite->draw( );
}
