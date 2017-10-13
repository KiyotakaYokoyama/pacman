#include "Pacman.h"
#include "Drawer.h"
#include "Image.h"
#include "Keyboard.h"
#include "define.h"

const int SPRITE_SIZE = 256;
const int MOVE_SPEED = 3;
const int MAX_SPEED = 10;

Pacman::Pacman( Vector pos ) :
Character( pos ) {
	_sprite = Drawer::getTask( )->createImage( "pacman.png" );
}


Pacman::~Pacman( ) {
}

void Pacman::act( ) {
	actOnMove( );
	adjustPos( );
	draw( );
}

void Pacman::actOnMove( ) {
	Vector vec = getVec( );
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isHoldKey( "ARROW_LEFT" ) ) {
		vec.x -= MOVE_SPEED;
	}
	if ( key->isHoldKey( "ARROW_RIGHT" ) ) {
		vec.x += MOVE_SPEED;
	}
	if ( key->isHoldKey( "ARROW_UP" ) ) {
		vec.y -= MOVE_SPEED;
	}
	if ( key->isHoldKey( "ARROW_DOWN" ) ) {
		vec.y += MOVE_SPEED;
	}
	if ( vec.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
		vec = vec.normalize( ) * MAX_SPEED;
	}
	setVec( vec );
}

void Pacman::adjustPos( ) {
	Vector vec = getVec( );
	Vector pos = getPos( );
	Vector f_pos = pos + vec;
	if ( f_pos.x < 0 + SPRITE_SIZE / 2 ) {
		vec.x = 0 - pos.x + SPRITE_SIZE / 2;
	}
	if ( f_pos.x > WIDTH - SPRITE_SIZE / 2 ) {
		vec.x = WIDTH - pos.x - SPRITE_SIZE / 2;
	}
	if ( f_pos.y < 0 + SPRITE_SIZE ) {
		vec.y = 0 - pos.y + SPRITE_SIZE;
	}
	if ( f_pos.y > HEIGHT ) {
		vec.y = HEIGHT - pos.y;
	}
	setVec( vec );
}

void Pacman::draw( ) const {
	Vector pos = getPos( );
	_sprite->setPos( pos.x - SPRITE_SIZE / 2, pos.y - SPRITE_SIZE );
	_sprite->draw( );
}
