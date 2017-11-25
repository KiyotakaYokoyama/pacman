#include "Military.h"
#include "SceneStage.h"
#include "Enemy.h"
#include "Pacman.h"
#include "define.h"
#include "Drawer.h"
#include "Image.h"

Military::Military( ) {
	_image = Drawer::getTask( )->createImage( "enemies.png" );
}


Military::~Military( ) {
}

void Military::update( ) {
	SceneStagePtr game = SceneStage::getTask( );
	int chara_size = game->getCharaSize( );
	PacmanConstPtr player1 = game->getPacman( PLAYER_1 );
	PacmanConstPtr player2 = game->getPacman( PLAYER_2 );
	bool escape1 = player1->isTurnaround( );
	bool escape2 = player2->isTurnaround( );
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = *ite;
		enemy->update( );

		if ( escape1 ) {
			Vector distance = player1->getPos( ) - enemy->getPos( );
			if ( distance.getLength2( ) < chara_size * chara_size ) {
				ite = _enemies.erase( ite );
				enemy.reset( );
				continue;
			}
		}
		
		if ( escape2 ) {
			Vector distance = player2->getPos( ) - enemy->getPos( );
			if ( distance.getLength2( ) < chara_size * chara_size ) {
				ite = _enemies.erase( ite );
				enemy.reset( );
				continue;
			}
		}

		ite++;
	}
}

void Military::draw( ) const {
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = *ite;
		IMGAE_DATA data = enemy->getImageData( );

		_image->setRect( data.tx, data.ty, data.tw, data.th );
		_image->setPos( data.sx1, data.sy1, data.sx2, data.sy2 );
		_image->draw( );
		ite++;
	}
}

void Military::addEnemy( EnemyPtr enemy ) {
	_enemies.push_back( enemy );
}
