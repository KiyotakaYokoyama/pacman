#include "Player1.h"
#include "Keyboard.h"

Player1::Player1( const Vector& pos ) :
Pacman( pos ) {
}

Player1::~Player1( ) {
}

void Player1::updateKey( ) {
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isHoldKey( "ARROW_RIGHT" )  ) {
		setKey( KEY_RIGHT );
	}

}
