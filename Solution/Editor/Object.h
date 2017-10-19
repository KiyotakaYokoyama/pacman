#pragma once
#include <vector>
#include <string>

class Object {
public:
	Object( );
	virtual ~Object( );
public:
	unsigned char getChip( int ox, int oy ) const;
	void setChip( int ox, int oy, unsigned char chip );
	void save( std::string directory, std::string filename ) const;
	void load( std::string directory, std::string filename ) const;
private:
	std::vector< unsigned char > _chips;
};

