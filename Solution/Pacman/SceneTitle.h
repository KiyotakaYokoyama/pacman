#pragma once
#include "Scene.h"
#include "smart_ptr.h"

PTR( Image );

class SceneTitle : public Scene {
public:
	SceneTitle( );
	virtual ~SceneTitle( );
private:
	SCENE update( );
	void draw( ) const;
	bool checkKey( );
private:
	ImagePtr _title;
};
