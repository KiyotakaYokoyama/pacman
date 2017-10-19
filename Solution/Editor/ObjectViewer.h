#pragma once
#include "smart_ptr.h"

PTR( Object );
PTR( Image );
PTR( ImageTarget );

class ObjectViewer {
public:
	ObjectViewer( ObjectConstPtr object );
	virtual ~ObjectViewer( );
public:
	void draw( ) const;
	ImageTargetPtr getStageSprite( );
private:
	void drawBoxTable( ) const;
	void drawObjects( ) const;
	void setWallImageRect( int ox, int oy ) const;
private:
	ObjectConstPtr _object;
	ImagePtr _image;
	ImagePtr _wall;
};

