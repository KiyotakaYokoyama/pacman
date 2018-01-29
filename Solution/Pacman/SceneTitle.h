#pragma once
#include "Scene.h"
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( Image );
PTR( ImageTarget );

class SceneTitle : public Scene {
public:
	SceneTitle( ImagePtr push_key );
	virtual ~SceneTitle( );
private:
	enum DIR {
		DIR_UP,
		DIR_DOWN,
		DIR_LEFT,
		DIR_RIGHT,
		MAX_DIR
	};
private:
	SCENE update( );
	void createTitle( );
	void setVec( );
	void setEnhance( );
	void initTitleEffect( );
	void draw( ) const;
	bool checkKey( );
private:
	int _count;
	int _enhance_count;
	Vector _pacman_pos;
	Vector _pacman_vec;
	ImagePtr _title;
	ImagePtr _push_key;
	ImagePtr _pacman;
	ImagePtr _pacman_shadow;
	ImagePtr _feed;
	ImageTargetPtr _title_effect;
};
