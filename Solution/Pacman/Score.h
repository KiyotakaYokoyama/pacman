#pragma once
#include <array>
#include <list>
#include "smart_ptr.h"
#include "define.h"

PTR( Image );

class Score {
public:
	Score( ImagePtr number, ImagePtr player_name );
	virtual ~Score( );
public:
	void update( );
	void draw( ) const;
	void addScore( PLAYER idx, SCORE score );
private:
	struct PERFORMER {
		int time;
		PLAYER player;
		SCORE score;

		PERFORMER( );
		PERFORMER( int time_, PLAYER player_, SCORE score_ );
	};
private:
	void drawScoreEffet( ) const;
private:
	int _battle_time;
	std::array< int, MAX_PLAYER > _score;
	std::list< PERFORMER > _performer;
	ImagePtr _number;
	ImagePtr _player_name;
};

