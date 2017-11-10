#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include <string>
#include <vector>
#include <array>
#include "define.h"

PTR( Image );

class Map {
public:
	Map( );
	virtual ~Map( );
public:
	void update( );
	void draw( ) const;
	void drawFeed( ) const;
	void eatFeed( const Vector& pos );
	void eatFeed( int ox, int oy );
	int getMapX( const Vector& pos ) const;
	int getMapY( const Vector& pos ) const;
	bool loadStage( int idx );
	unsigned char getObject( const Vector& pos ) const;
	unsigned char getObject( int ox, int oy ) const;
	Vector getPlayerPos( int id );
private:
	struct ENEMY {
		unsigned char index;
		Vector pos;

		ENEMY( ) :
		index( OBJECT_NONE ),
		pos( Vector( ) ) {
		};
	};
private:
	void loadStage( std::string stage_name );
private:
	std::vector< std::string > _stages;
	std::vector< unsigned char > _objects;
	std::vector< Vector > _feed_pos;
	std::vector< ENEMY > _enemy_pos;
	std::array< Vector, PLAYER_NUM > _player_pos;
	ImagePtr _stage;
	ImagePtr _feeds;
};

