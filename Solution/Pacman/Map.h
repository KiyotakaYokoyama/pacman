#pragma once
#include "Task.h"
#include "mathmatics.h"
#include <string>
#include <vector>

PTR( Map );
PTR( Image );

class Map : public Task {
public:
	static std::string getTag( ) { return "MAP"; };
	static MapPtr getTask( );
public:
	Map( );
	virtual ~Map( );
public:
	void initialize( );
	void update( );
	void draw( ) const;
	unsigned char getObject( const Vector& pos ) const;
	unsigned char getObject( int ox, int oy ) const;
private:
	std::vector< unsigned char > _objects;
	ImagePtr _stage;
	ImagePtr _chip;
};

