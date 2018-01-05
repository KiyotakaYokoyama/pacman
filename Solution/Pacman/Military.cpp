#include "Military.h"
#include "SceneStage.h"
#include "Enemy.h"
#include "Pacman.h"
#include "define.h"
#include "Drawer.h"
#include "Image.h"
#include "Game.h"

Military::Military( ) {
	_image = Drawer::getTask( )->createImage( "enemies.png" );
}


Military::~Military( ) {
}

void Military::update( ) {
	GamePtr game = Game::getTask( );
	SceneStagePtr scene_stage = SceneStage::getTask( );
	int chara_size = scene_stage->getCharaSize( );
	PacmanPtr player1 = scene_stage->getPacman( PLAYER_1 );
	PacmanPtr player2 = scene_stage->getPacman( PLAYER_2 );
	bool escape1 = player1->isTurnaround( );
	bool escape2 = player2->isTurnaround( );
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = *ite;
		enemy->update( );

		if ( enemy->isAction( ) ) {
			Vector distance1 = player1->getPos( ) - enemy->getPos( );
			if ( distance1.getLength2( ) < chara_size * chara_size ) {
				if ( escape1 ) {
					game->addScore( PLAYER_1, enemy->getScore( ) );
					enemy->setHide( );
				} else {
					if ( !player1->isDamaging( ) ) {
						game->addScore( PLAYER_1, SCORE_DAMAGE );
						player1->damage( );
					}
				}
			}

			Vector distance2 = player2->getPos( ) - enemy->getPos( );
			if ( distance2.getLength2( ) < chara_size * chara_size ) {
				if ( escape2 ) {
					game->addScore( PLAYER_2, enemy->getScore( ) );
					enemy->setHide( );
				} else {
					if ( !player2->isDamaging( ) ) {
						game->addScore( PLAYER_2, SCORE_DAMAGE );
						player2->damage( );
					}
				}
			}
		}
		ite++;
	}
}

void Military::draw( ) const {
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = *ite;
		if ( enemy->isDrawing( ) ) {
			IMGAE_DATA data = enemy->getImageData( );

			_image->setRect( data.tx, data.ty, data.tw, data.th );
			_image->setPos( data.sx1, data.sy1, data.sx2, data.sy2 );
			_image->draw( );
		}
		ite++;
	}
}

void Military::addEnemy( EnemyPtr enemy ) {
	_enemies.push_back( enemy );
}
