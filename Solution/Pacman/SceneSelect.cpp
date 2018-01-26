#include "SceneSelect.h"
#include "Game.h"
#include "Keyboard.h"
#include "Drawer.h"
#include "Image.h"
#include "Sound.h"

#if DEVICE
#include "Device.h"
#endif

const int MAX_STAGE = 10;
const int TEXTURE_WIDTH = 160;
const int WAIT_ANIM_TIME = 3;
const int ANIM[ ] = { 0, 1, 2, 3, 4, 3, 2, 1 };
const int ANIM_NUM = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );

SceneSelect::SceneSelect( ImagePtr number ) :
_count( 0 ),
_select( 0 ),
_number( number ) {
	DrawerPtr drawer = Drawer::getTask( );
	_stage = drawer->createImage( "string.png" );
	_stage->setRect( 0, 0, TEXTURE_WIDTH, SPRITE_SIZE );
	_pacman[ 0 ] = drawer->createImage( "pacman2.png" );
	_pacman[ 1 ] = drawer->createImage( "pacwoman2.png" );
	Sound::getTask( )->playBGM( "pac_music_coffeebreak.mp3" );
}

SceneSelect::~SceneSelect( ) {
}

Scene::SCENE SceneSelect::update( ) {
	updateSelect( );
	_count++;
	if ( isDecision( ) ) {
		return SCENE_STAGE;
	}
	return SCENE_CONTINUE;
}

void SceneSelect::updateSelect( ) {
	const int CHECK = MAX_STAGE / 2;
	int select_x = _select / CHECK;
	int select_y = _select % CHECK;
#if DEVICE
	DevicePtr device = Device::getTask( );
	if ( device->getDirY( PLAYER_1 ) > 0 ||
		 device->getDirY( PLAYER_2 ) > 0 ) {
		select_y = select_y + 1;
		if ( select_y > CHECK - 1 ) select_y = CHECK - 1;
	}
	if ( device->getDirY( PLAYER_1 ) < 0 ||
		 device->getDirY( PLAYER_2 ) < 0 ) {
		select_y = select_y - 1;
		if ( select_y < 0 ) select_y = 0;
	}
	if ( device->getDirX( PLAYER_1 ) > 0 ||
		 device->getDirX( PLAYER_2 ) > 0 ) {
		select_x = select_x + 1;
		if ( select_x > 1 ) select_x = 1;
	}
	if ( device->getDirX( PLAYER_1 ) < 0 ||
		 device->getDirX( PLAYER_2 ) < 0 ) {
		select_x = select_x - 1;
		if ( select_x < 0 ) select_x = 0;
	}
#else
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "S" ) || key->isPushKey( "ARROW_DOWN" ) ) {
		select_y = select_y + 1;
		if ( select_y > CHECK - 1 ) select_y = CHECK - 1;
	}
	if ( key->isPushKey( "W" ) || key->isPushKey( "ARROW_UP" ) ) {
		select_y = select_y - 1;
		if ( select_y < 0 ) select_y = 0;
	}
	if ( key->isPushKey( "D" ) || key->isPushKey( "ARROW_RIGHT" ) ) {
		select_x = select_x + 1;
		if ( select_x > 1 ) select_x = 1;
	}
	if ( key->isPushKey( "A" ) || key->isPushKey( "ARROW_LEFT" ) ) {
		select_x = select_x - 1;
		if ( select_x < 0 ) select_x = 0;
	}
#endif
	_select = select_y + select_x * CHECK;
}

void SceneSelect::draw( ) const {
	//文字
	const int CHECK = MAX_STAGE / 2;
	const int NUM[ 10 ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	for ( int i = 0; i < MAX_STAGE; i++ ) {
		int sx = ( int )( WIDTH * 0.2 + ( i / CHECK ) * WIDTH * 0.4 ) + ( i != MAX_STAGE - 1 ) * 16;
		int sy = ( int )( HEIGHT * 0.1 + ( i % CHECK ) * 128 );
		_stage->setPos( sx, sy );
		_stage->draw( );
		_number->setRect( NUM[ i ] * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE );
		_number->setPos( sx + TEXTURE_WIDTH, sy );
		_number->draw( );
		if ( i == MAX_STAGE - 1 ) {
			_number->setRect( 9 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE );
			_number->setPos( sx + TEXTURE_WIDTH + 32, sy );
			_number->draw( );
		}
	}

	//パックマン
	int tx = ANIM[ ( _count / WAIT_ANIM_TIME ) % ANIM_NUM ] * SPRITE_SIZE;
	const int STR_WIDTH = 320;
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		int ty = i == PLAYER_1 ? SPRITE_SIZE * 1 : 0;
		_pacman[ i ]->setRect( tx, ty, SPRITE_SIZE, SPRITE_SIZE );
		int sx = ( int )( WIDTH * 0.2 + ( _select / CHECK ) * WIDTH * 0.4 ) - SPRITE_SIZE;
		int sy = ( int )( HEIGHT * 0.1 + ( _select % CHECK ) * 128 );
		if ( i == PLAYER_2 ) {
			sx += STR_WIDTH;
		}
		_pacman[ i ]->setPos( sx, sy );
		_pacman[ i ]->draw( );
	}
}

bool SceneSelect::isDecision( ) const {
#if DEVICE
	DevicePtr device = Device::getTask( );
	if ( device->getButton( PLAYER_1 ) ||
		 device->getButton( PLAYER_2 ) ) {
		return true;
	}
#else
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "SPACE" ) ) {
		return true;
	}
#endif
	return false;
}

int SceneSelect::getSelectStage( ) const {
	return _select;
}
