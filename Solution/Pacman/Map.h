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
	unsigned char getObject( const Vector& pos ) const;
	unsigned char getObject( int ox, int oy ) const;
	Vector getPlayerPos( int id );
private:
	void loadStage( std::string stage_name );
private:
	std::vector< std::string > _stages;
	std::vector< unsigned char > _objects;
	std::array< Vector, PLAYER_NUM > _player_pos;
	ImagePtr _stage;
	ImagePtr _feeds;
};

