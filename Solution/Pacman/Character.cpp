#include "Character.h"
#include "Game.h"
#include "SceneStage.h"
#include "Map.h"
#include "define.h"

static const int MAX_ACT_TIME = 0xfffffff;

Character::Character( Vector pos, bool coll ) :
_pos( pos ),
_coll( coll ),
_bumped( false ),
_dir( DIR_RIGHT ),
_act_count( 0 ) {
}

Character::~Character( ) {
}

void Character::update( ) {
	act( );
	_act_count = ( _act_count++ ) % MAX_ACT_TIME;

	if( _coll ) {
		updateColl( );
	}

	updateDir( );

	_pos += _vec;
}

void Character::updateColl( ) {
	_bumped = false;
	GamePtr game = Game::getTask( );
	MapPtr map = game->getStage( )->getMap( );
	const int CHIP_SIZE = game->getChipSize( );
	const int CHARA_SIZE = game->getCharaSize( );
	const int HARF_CHARA_SIZE = CHARA_SIZE / 2;
	//上
	if ( _vec.y < 0 ) {
		if ( ( _pos.y + _vec.y ) - CHARA_SIZE < 0 ) {
			_pos.y = CHIP_SIZE;
			_vec.y = 0;
			_bumped = true;
		} else {
			//左上
			unsigned char left_obj = map->getObject( _pos + Vector( -HARF_CHARA_SIZE, _vec.y - CHARA_SIZE ) );
			//右上
			unsigned char light_obj = map->getObject( _pos + Vector( HARF_CHARA_SIZE, _vec.y - CHARA_SIZE ) );
			if ( left_obj == OBJECT_WALL || light_obj == OBJECT_WALL ) {
				_pos.y = ( ( int )( _pos.y + _vec.y - CHARA_SIZE ) / CHIP_SIZE + 1 ) * CHIP_SIZE + CHARA_SIZE;
				_vec.y = 0;
				_bumped = true;
			}
		}
	}
	//下
	if ( _vec.y > 0 ) {
		//左下
		unsigned char left_obj = map->getObject( _pos + Vector( -HARF_CHARA_SIZE, _vec.y ) );
		//右下
		unsigned char light_obj = map->getObject( _pos + Vector( HARF_CHARA_SIZE, _vec.y ) );
		if ( left_obj == OBJECT_WALL || light_obj == OBJECT_WALL ) {
			_pos.y = ( ( int )( _pos.y + _vec.y ) / CHIP_SIZE ) * CHIP_SIZE - 1;
			_vec.y = 0;
			_bumped = true;
		}
	}
	//左側
	if ( _vec.x < 0 ) {
		Vector f_pos = _pos + Vector( _vec.x - HARF_CHARA_SIZE, 0 );
		if ( f_pos.x < 0 ) {
			_pos.x = HARF_CHARA_SIZE;
			_vec.x = 0;
			_bumped = true;
		} else {
			//左上
			unsigned char up_obj = map->getObject( f_pos + Vector( 0, -CHARA_SIZE ) );
			//左下
			unsigned char down_obj = map->getObject( f_pos + Vector( 0, 0 ) );
			if ( up_obj == OBJECT_WALL || down_obj == OBJECT_WALL ) {
				_pos.x = ( ( ( int )f_pos.x / CHIP_SIZE ) + 1 ) * CHIP_SIZE + HARF_CHARA_SIZE;
				_vec.x = 0;
				_bumped = true;
			}
		}
	}
	//右側
	if ( _vec.x > 0 ) {
		Vector f_pos = _pos + Vector( _vec.x + HARF_CHARA_SIZE, 0 );
		//右上
		unsigned char up_obj = map->getObject( f_pos + Vector( 0, -CHARA_SIZE ) );
		//右下
		unsigned char down_obj = map->getObject( f_pos + Vector( 0, 0 ) );
		if ( up_obj == OBJECT_WALL || down_obj == OBJECT_WALL ) {
			_pos.x = ( ( int )f_pos.x / CHIP_SIZE ) * CHIP_SIZE - HARF_CHARA_SIZE - 1;
			_vec.x = 0;
			_bumped = true;
		}
	}
}

void Character::updateDir( ) {
	double abs_vec_x = fabs( _vec.x );
	double abs_vec_y = fabs( _vec.y );
	if ( abs_vec_x < abs_vec_y && _vec.y < 0 ) {
		_dir = DIR_UP;
	}
	if ( abs_vec_x < abs_vec_y && _vec.y > 0 ) {
		_dir = DIR_DOWN;
	}
	if ( abs_vec_x > abs_vec_y && _vec.x < 0 ) {
		_dir = DIR_LEFT;
	}
	if ( abs_vec_x > abs_vec_y && _vec.x > 0 ) {
		_dir = DIR_RIGHT;
	}
}

int Character::getActTime( ) const {
	return _act_count;
}

Vector Character::getPos( ) const {
	return _pos;
}

Vector Character::getVec( ) const {
	return _vec;
}

void Character::setPos( const Vector& pos ) {
	_pos = pos;
}

void Character::setVec( const Vector& vec ) {
	_vec = vec;
}

void Character::setColl( bool coll ) {
	_coll = coll;
}

Character::DIR Character::getDir( ) const {
	return _dir;
}

void Character::setActCount( int count ) {
	_act_count = count;
}

bool Character::isBumped( ) const {
	return _bumped;
}
