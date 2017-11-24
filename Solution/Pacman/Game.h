#pragma once
#include "Task.h"
#include <string>

PTR( Game );

class Game : public Task {
public:
	static std::string getTag( ) { return "GAME"; };
	static GamePtr getTask( );
public:
	Game( );
	virtual ~Game( );
public:
	enum SCENE {
		SCENE_TITLE,
		SCENE_STAGE,
		SCENE_RESULT,
	};
public:
	void initialize( );
	void update( );
	void setNextScene( SCENE scene );
	SCENE getNowScene( ) const;
private:
	SCENE _scene;
};

