#pragma once
#include "Scene.h"
#include <array>
#include "smart_ptr.h"
#include "define.h"

PTR( Image );

class SceneResult : public Scene {
public:
	SceneResult( RESULT result );
	virtual ~SceneResult( );
private:
	SCENE update( );
	void draw( ) const;
	bool checkKey( );
private:
	int _count;
	int _loop_num;
	RESULT _winner;
	ImagePtr _result;
	ImagePtr _win_player;
	std::array< ImagePtr, 45 > _cracker;
};

