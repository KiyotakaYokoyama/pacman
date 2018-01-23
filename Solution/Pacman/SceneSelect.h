#pragma once
#include "Scene.h"
#include "smart_ptr.h"
#include "define.h"

PTR( Image );

class SceneSelect :	public Scene {
public:
	SceneSelect( ImagePtr number );
	virtual ~SceneSelect( );
public:
	int getSelectStage( ) const;
private:
	SCENE update( );
	void updateSelect( );
	void draw( ) const;
	bool isDecision( ) const;
private:
	int _count;
	int _select;
	ImagePtr _number;
	ImagePtr _stage;
	ImagePtr _pacman[ MAX_PLAYER ];
};

