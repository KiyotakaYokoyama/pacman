#include "Pacman.h"
#include "Game.h"
#include "SceneStage.h"
#include "Map.h"
#include "Drawer.h"
#include "Image.h"
#include "Keyboard.h"
#include "Sound.h"
#include <assert.h>

#if DEVICE
#include "Device.h"
#endif

#ifdef _DEBUG
const int MAX_SPEED = 3; //最適値2
#else
const int MAX_SPEED = 2;
#endif // _DEBUG
const int MOVE_SPEED = 3;
const int WAIT_ANIM_TIME = 3;
const int TURNAROUND_TIME = 300;
const int TURNAROUND_FLASHING_TIME = TURNAROUND_TIME - 60;
const int ANIM[ ] = { 0, 1, 2, 3, 4, 3, 2, 1 };
const int ANIM_NUM = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
const int DAMAGE_TIME = 60;

Pacman::Pacman( int id, const Vector& pos ) :
Character( pos ),
_id( ( PLAYER )id ),
_damage( 0 ),
_auto_move( false ),
_turnaround( false ),
_auto_vec( Vector( ) ) {
	if ( id == 0 ) {
		_sprite = Drawer::getTask( )->createImage( "pacman.png" );
	}
	if ( id == 1 ) {
		_sprite = Drawer::getTask( )->createImage( "pacwoman.png" );
	}
	assert( id == 0 || id == 1 );
}


Pacman::~Pacman( ) {
}

void Pacman::act( ) {
	if ( _damage > DAMAGE_TIME / 2 ) {
		Vector vec = getVec( );
		vec -= vec.normalize( ) * ( MOVE_SPEED / 3 );
		if ( vec.getLength( ) < MOVE_SPEED / 3 ) {
			vec = Vector( );
		}
		setVec( vec );
	} else {
		if ( !_auto_move ) {
			actOnMove( );
			actOnEat( );
			actOnWarp( );
		} else {
			actOnAutoMove( );
		}
	}

	if ( _damage > 0 ) {
		_damage--;
	}

	if ( _turnaround && getActTime( ) > TURNAROUND_TIME ) {
		_turnaround = false;
	}
}

void Pacman::actOnMove( ) {
	Vector vec;
	bool brake = true;
#if DEVICE
	DevicePtr device = Device::getTask( );
	if ( device->getDirX( _id ) < 0 ) {
		vec.x -= MOVE_SPEED;
		brake = false;
	}
	if ( device->getDirX( _id ) > 0 ) {
		vec.x += MOVE_SPEED;
		brake = false;
	}
	if ( device->getDirY( _id ) < 0 ) {
		vec.y -= MOVE_SPEED;
		brake = false;
	}
	if ( device->getDirY( _id ) > 0 ) {
		vec.y += MOVE_SPEED;
		brake = false;
	}
#else
	KeyboardPtr key = Keyboard::getTask( );
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
#endif

	if ( brake ) {
		vec = Vector( );
	}

	if ( vec.x != 0 && vec.y != 0 ) {
		vec = Vector( vec.x, 0 ).normalize( ) * MAX_SPEED;
	}
	
	GamePtr game = Game::getTask( );
	const int CHIP_SIZE = game->getChipSize( );
	const int CHARA_SIZE = game->getCharaSize( );
	bool center_x = ( int )getPos( ).x % CHIP_SIZE == CHIP_SIZE / 2;
	bool center_y = ( int )getPos( ).y % CHIP_SIZE == CHARA_SIZE;

	Vector pos = getPos( );
	pos = Vector( fabs( pos.x ), fabs( pos.y ) );
	Vector before_vec = getVec( );
	if ( !center_x && vec.x == 0 ) {
		double diff = abs( ( CHIP_SIZE / 2 ) - ( ( int )pos.x % CHIP_SIZE ) );
		diff += pos.x - ( int )pos.x;
		if ( before_vec.x < 0 ) {
			vec.x = -diff;
		}
		if ( before_vec.x > 0 ) {
			vec.x = diff;
		}
	}
	if ( !center_y && vec.y == 0 ) {
		double diff = abs( ( CHIP_SIZE / 2 ) - ( ( int )pos.y % CHIP_SIZE ) );
		diff += pos.y - ( int )pos.y;
		if ( before_vec.y < 0 ) {
			vec.y = -diff;
		}
		if ( before_vec.y > 0 ) {
			vec.y = diff;
		}
	}

	if ( vec.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
		vec = vec.normalize( ) * MAX_SPEED;
	}
	setVec( vec );
}

void Pacman::actOnEat( ) {
	GamePtr game = Game::getTask( );
	MapPtr map = game->getStage( )->getMap( );
	const int CHIP_SIZE = game->getChipSize( );
	Vector check = getPos( ) + Vector( 0, -CHIP_SIZE / 2 );
	unsigned char obj = map->getObject( check );
	if ( obj == OBJECT_ENHANCE_FEED || obj == OBJECT_FEED ) {
		map->eatFeed( check );
		Sound::getTask( )->playSE( "pac_se_eatingcokkie.mp3" );
	}
	if ( obj == OBJECT_ENHANCE_FEED ) {
		_turnaround = true;
		setActCount( 0 );
	}
	if ( obj == OBJECT_FEED ) {
		Game::getTask( )->getStage( )->addScore( _id, SCORE_FEED );
	}
}

void Pacman::actOnWarp( ) {
	GamePtr game = Game::getTask( );
	MapPtr map = game->getStage( )->getMap( );
	const int CHIP_SIZE = game->getChipSize( );
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
	const int CHIP_SIZE = Game::getTask( )->getChipSize( );
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
	if ( _damage % 6 < 3 && _damage > 0 ) {
		//ダメージ中の点滅
		return;
	}
	int act_count = getActTime( );
	if ( isTurnaround( ) && act_count > TURNAROUND_FLASHING_TIME && act_count % 6 < 3 ) {
		//パワーアップ終了目前の点滅
		return;
	}

	const int DRAW_SIZE = Game::getTask( )->getCharaSize( );
	Vector pos = getPos( );
	int tx = ANIM[ ( getActTime( ) / WAIT_ANIM_TIME ) % ANIM_NUM ] * SPRITE_SIZE;
	int ty = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		ty = SPRITE_SIZE * 1;
	}
	if ( getDir( ) == DIR_UP ) {
		ty = SPRITE_SIZE * 2;
	}
	if ( getDir( ) == DIR_DOWN ) {
		ty = SPRITE_SIZE * 3;
	}
	//パワーアップ中
	if ( isTurnaround( ) ){
		ty += SPRITE_SIZE * 4;
	}
	_sprite->setRect( tx, ty, SPRITE_SIZE, SPRITE_SIZE );
	int sx = ( int )( pos.x - DRAW_SIZE / 2 );
	int sy = ( int )( pos.y - DRAW_SIZE );
	_sprite->setPos( sx, sy, sx + DRAW_SIZE, sy + DRAW_SIZE );
	_sprite->draw( );
}

void Pacman::drawStageing( const int time, const int max_time ) const {
	const int CHIP_SIZE = Game::getTask( )->getChipSize( );
	const int DRAW_SIZE = Game::getTask( )->getCharaSize( );
	const int STAGE_WIDTH = CHIP_SIZE * MAP_WIDTH_CHIP_NUM;
	const int STAGE_HEIGHT = CHIP_SIZE * MAP_HEIGHT_CHIP_NUM;
	const double RATIO = ( ( double )( max_time - time ) / max_time );
	const Vector START_POS( STAGE_WIDTH / 2, STAGE_HEIGHT );
	Vector distance = getPos( ) - START_POS;
	Vector pos = distance * ( 1.0 - RATIO ) + START_POS;

	_sprite->setRect( SPRITE_SIZE * 1, SPRITE_SIZE * 1, SPRITE_SIZE, SPRITE_SIZE );
	const int MAGNIFICAT = 30;
	int sx = ( int )( pos.x - ( DRAW_SIZE * 0.5 ) * ( RATIO * MAGNIFICAT ) );
	int sy = ( int )( pos.y - DRAW_SIZE * ( ( RATIO * MAGNIFICAT ) + 1 ) );
	int sx2 = ( int )( sx + DRAW_SIZE * ( RATIO * MAGNIFICAT ) );
	int sy2 = ( int )pos.y;
	if ( abs( sx - sx2 ) < DRAW_SIZE ) {
		sx2 = sx + DRAW_SIZE;
	}
	if ( sy2 - sy < DRAW_SIZE ) {
		sy2 = sy + DRAW_SIZE;
	}
	_sprite->setPos( sx, sy, sx2, sy2 );
	_sprite->draw( );
}

void Pacman::entryStage( const Vector& pos ) {
	setPos( pos );
}

void Pacman::damage( ) {
	_damage = DAMAGE_TIME;
}

bool Pacman::isTurnaround( ) const {
	return _turnaround;
}

bool Pacman::isDamaging( ) const {
	return _damage > 0;
}
