#include "Military.h"
#include "Enemy.h"
#include "define.h"
#include "Drawer.h"
#include "Image.h"

Military::Military( ) {
	_image = Drawer::getTask( )->createImage( "enemies.png" );
}


Military::~Military( ) {
}

void Military::update( ) {
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = *ite;
		enemy->update( );
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
