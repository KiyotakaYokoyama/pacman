#include "SceneTitle.h"
#include "Application.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Sound.h"
#include "Image.h"
#include "ImageTarget.h"
#include "Game.h"
#include "define.h"

#if DEVICE
#include "Device.h"
#endif

const int FPS = 30;
const int NEXT_SCENE_TIME = 10 * FPS;
const int MAX_EFFECT_COUNT = 30 * FPS;
const int PACMAN_SIZE = 64;
const int MOVE_SPEED = 10;
const int WAIT_ANIM_TIME = 3;
const int ANIM[ ] = { 0, 1, 2, 3, 4, 3, 2, 1 };
const int ANIM_NUM = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
const Vector DIRECT[ 4 ] = {
	Vector( 0, -MOVE_SPEED ),
	Vector( 0, MOVE_SPEED ),
	Vector( -MOVE_SPEED, 0 ),
	Vector( MOVE_SPEED, 0 ),
};
const int ENHANCE_TIME = 8 * FPS;
const int FEED_NUM = 3;
const Vector FEED_POS[ FEED_NUM ] = {
	Vector( 100, 90 ),
	Vector( WIDTH / 2 - 180, 700 ),
	Vector( WIDTH - 245, 200 )
};

SceneTitle::SceneTitle( ) :
_enhance_count( 0 ) {
	Sound::getTask( )->playBGM( "pac_music_coffeebreak.mp3" );
	DrawerPtr drawer = Drawer::getTask( );
	ApplicationPtr app = Application::getInstance( );
	int width = app->getWindowWidth( );
	int height = app->getWindowHeight( );
	{
		_feed = drawer->createImage( "feed.png" );
		_feed->setRect( 64, 0, 64, 64 );
		_pacman = drawer->createImage( "pacman2.png" );
		_pacman_shadow = drawer->createImage( "pacman3.png" );
		_title = drawer->createImage( "title.png" );
		int w;
		int h;
		_title->getImageSize( w, h );
		_title->setRect( 0, 0, w, h );
		_title->setPos( 0, 0, width, height );
	}
	{
		_title_effect = ImageTargetPtr( new ImageTarget );
		_title_effect->create( width, height );
		drawer->setImageTarget( _title_effect );
		_title->draw( );
		for ( int i = 0; i < FEED_NUM; i++ ) {
			_feed->setPos( ( int )FEED_POS[ i ].x, ( int )FEED_POS[ i ].y );
			_feed->draw( );
		}
		drawer->setImageTarget( );
	}
	_pacman_pos = Vector( width / 2, height / 2 + PACMAN_SIZE / 2 );
	_pacman_vec = Vector( 0, 0 );
}

SceneTitle::~SceneTitle( ) {
}

void SceneTitle::initTitleEffect( ) {
	DrawerPtr drawer = Drawer::getTask( );
	_title_effect->clear( );
	drawer->setImageTarget( _title_effect );
	_title->draw( );
	for ( int i = 0; i < FEED_NUM; i++ ) {
		_feed->setPos( ( int )FEED_POS[ i ].x, ( int )FEED_POS[ i ].y );
		_feed->draw( );
	}
	drawer->setImageTarget( );
}

Scene::SCENE SceneTitle::update( ) {
	setVec( );
	setEnhance( );
	_pacman_pos += _pacman_vec;
	createTitle( );
	_count++;
	_enhance_count--;
	if ( _count == 29.8 * FPS ) {
		_pacman_vec = Vector( );
	}
	if ( _count == 35 * FPS ) {
		_count = 0;
		_enhance_count = 0;
		initTitleEffect( );
	}
	if ( checkKey( ) ) {
		return SCENE_SELECT;
	}
	return SCENE_CONTINUE;
}

void SceneTitle::createTitle( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->setImageTarget( _title_effect );
	if ( _enhance_count > 0 ) {
		int sx = ( int )_pacman_pos.x - PACMAN_SIZE / 2;
		int sy = ( int )_pacman_pos.y - PACMAN_SIZE;
	
		int tx = ANIM[ ( _count / WAIT_ANIM_TIME ) % ANIM_NUM ] * SPRITE_SIZE;
		int ty = 0;
		if ( _pacman_vec == DIRECT[ DIR_RIGHT ] ) {
			ty = SPRITE_SIZE * 1;
		}
		if ( _pacman_vec == DIRECT[ DIR_UP ] ) {
			ty = SPRITE_SIZE * 2;
		}
		if ( _pacman_vec == DIRECT[ DIR_DOWN ] ) {
			ty = SPRITE_SIZE * 2;
		}

		_pacman_shadow->setRect( tx, ty, 64, 64 );
		_pacman_shadow->setPos( sx, sy );
		_pacman_shadow->draw( );
	}
	
	drawer->setImageTarget( );
}

void SceneTitle::draw( ) const {
	_title_effect->draw( );
	if ( _enhance_count > 0 && _enhance_count < 1 * 30 && _enhance_count % 6 < 3 ) {
		return;
	}
	if ( _count > 30 * FPS && _count % 6 < 3 ) {
		return;
	}
	int tx = ANIM[ ( _count / WAIT_ANIM_TIME ) % ANIM_NUM ] * SPRITE_SIZE;
	int ty = SPRITE_SIZE * 2;
	if ( _pacman_vec == DIRECT[ DIR_LEFT ] ) {
		ty = SPRITE_SIZE * 0;
	}
	if ( _pacman_vec == DIRECT[ DIR_RIGHT ] ) {
		ty = SPRITE_SIZE * 1;
	}
	if ( _pacman_vec == DIRECT[ DIR_DOWN ] ) {
		ty = SPRITE_SIZE * 3;
	}
	if ( _enhance_count > 0 ) {
		ty += 64 * 4;
	}
	_pacman->setRect( tx, ty, 64, 64 );
	int sx = ( int )_pacman_pos.x - PACMAN_SIZE / 2;
	int sy = ( int )_pacman_pos.y - PACMAN_SIZE;
	_pacman->setPos( sx, sy );
	_pacman->draw( );
}

void SceneTitle::setVec( ) {
	if ( _count == 0 ) {
		_pacman_vec = DIRECT[ DIR_UP ];
	}
	if ( _count == 1.4 * FPS ) {
		_pacman_vec = DIRECT[ DIR_LEFT ];
	}
	if ( _count == 4.2 * FPS ) {
		_pacman_vec = DIRECT[ DIR_DOWN ];
	}
	if ( _count == 7 * FPS ) {
		_pacman_vec = DIRECT[ DIR_RIGHT ];
	}
	if ( _count == 12.3 * FPS ) {
		_pacman_vec = DIRECT[ DIR_UP ];
	}
	if ( _count == 15 * FPS ) {
		_pacman_vec = DIRECT[ DIR_LEFT ];
	}
	if ( _count == 19.2 * FPS ) {
		_pacman_vec = DIRECT[ DIR_DOWN ];
	}
	if ( _count == 20 * FPS ) {
		_pacman_vec = DIRECT[ DIR_RIGHT ];
	}
	if ( _count == 20.5 * FPS ) {
		_pacman_vec = DIRECT[ DIR_DOWN ];
	}
	if ( _count == 21 * FPS ) {
		_pacman_vec = DIRECT[ DIR_RIGHT ];
	}
	if ( _count == 21.7 * FPS ) {
		_pacman_vec = DIRECT[ DIR_DOWN ];
	}
	if ( _count == 22.5 * FPS ) {
		_pacman_vec = DIRECT[ DIR_RIGHT ];
	}
		if ( _count == 25 * FPS ) {
		_pacman_vec = DIRECT[ DIR_UP ];
	}
		if ( _count == 26.5 * FPS ) {
		_pacman_vec = DIRECT[ DIR_LEFT ];
	}
		if ( _count == 27.5 * FPS ) {
		_pacman_vec = DIRECT[ DIR_DOWN ];
	}
	if ( _count == 28.5 * FPS ) {
		_pacman_vec = DIRECT[ DIR_LEFT ];
	}
	if ( _count == 29.5 * FPS ) {
		_pacman_vec = DIRECT[ DIR_UP ];
	}
}

void SceneTitle::setEnhance( ) {
	if ( _count == ( int )( 4.15 * FPS ) ) {
		_enhance_count = ENHANCE_TIME;
	}
	if ( _count == ( int )( 14.7 * FPS ) ) {
		_enhance_count = ENHANCE_TIME;
	}
	if ( _count == ( int )( 22.4 * FPS ) ) {
		_enhance_count = ENHANCE_TIME;
	}
}

bool SceneTitle::checkKey( ) {
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
