#pragma once

class Scene {
public:
	Scene( );
	virtual ~Scene( );
public:
	enum SCENE {
		SCENE_CONTINUE,
		SCENE_TITLE,
		SCENE_SELECT,
		SCENE_STAGE,
		SCENE_RESULT,
	};
public:
	virtual SCENE update( ) = 0;
	virtual void draw( ) const = 0;
};

