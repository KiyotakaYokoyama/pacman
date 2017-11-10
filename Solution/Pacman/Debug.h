#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "define.h"

PTR( Debug );
PTR( Image );
PTR( Pacman );

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
	bool isNewStage( ) const;
private:
	bool _active;
	bool _new_stage;
	ImagePtr _block_chip;
};

