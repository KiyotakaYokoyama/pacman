#pragma once
#include "Task.h"
#include <string>

PTR( Debug );
PTR( Image );

class Debug : public Task {
public:
	static std::string getTag( ) { return "DEBUG"; };
	static DebugPtr getTask( );
public:
	Debug( );
	virtual ~Debug( );
public:
	void initialize( );
	void update( );
	void draw( ) const;
	bool isActive( ) const;
private:
	bool _active;
	ImagePtr _block_chip;
};

