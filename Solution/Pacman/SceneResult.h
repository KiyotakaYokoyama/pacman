#pragma once
#include "Scene.h"
#include <array>
#include "smart_ptr.h"

PTR( Image );

class SceneResult : public Scene {
public:
	SceneResult( );
	virtual ~SceneResult( );
private:
	SCENE update( );
	void draw( ) const;
	bool checkKey( );
private:
	int _count;
	std::array< ImagePtr, 45 > _cracker;
};

