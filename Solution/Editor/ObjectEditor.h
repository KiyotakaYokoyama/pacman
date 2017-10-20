#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( Object );
PTR( Image );

class ObjectEditor {
public:
	ObjectEditor( ObjectPtr object );
	virtual ~ObjectEditor( );
public:
	enum MODE {
		MODE_NONE,
		MODE_WALL,
		MODE_FEED,
		MODE_ENHANCE_FEET
	};
public:
	void update( );
	void drawCursor( ) const;
	MODE getMode( ) const;
	Vector getCursor( ) const;
private:
	void updateMode( );
	void updateCursor( );
	void edit( );
private:
	MODE _mode;
	Vector _cursor;
	ObjectPtr _object;
	ImagePtr _cursor_sprite;
};

