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
		MODE_PLAYER1,
		MODE_PLAYER2,
		MODE_SAHDOW,
		MODE_SPEEDY,
		MODE_BASHFUL,
		MODE_POKEY,
		MODE_BLUNDER,
		MODE_GREEN,
		MODE_PURPLE,
		MODE_WALL,
		MODE_FEED,
		MODE_ENHANCE_FEET,
		MODE_STAGE_WARP,
		MODE_REVIVAL_FEED
	};
public:
	void update( );
	void drawCursor( ) const;
	void initData( ) const;
	MODE getMode( ) const;
	Vector getCursor( ) const;
private:
	void updateMode( );
	void updateCursor( );
	void edit( );
	void checkAndEditChip( unsigned int chip );
private:
	MODE _mode;
	Vector _cursor;
	ObjectPtr _object;
	ImagePtr _cursor_sprite;
};

