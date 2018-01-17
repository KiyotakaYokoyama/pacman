#pragma once
#include "Enemy.h"

class EnemyPokey : public Enemy {
public:
	EnemyPokey( const Vector& pos );
	virtual ~EnemyPokey( );
private:
	void moving( );
	void setMoveDir( );
	SCORE getScore( ) const;
	IMGAE_DATA getImageData( ) const;
private:
	int _move_count;
	int _move_lenght;
	DIR _dir;
};

