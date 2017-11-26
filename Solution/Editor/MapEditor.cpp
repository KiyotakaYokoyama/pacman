#include "MapEditor.h"
#include "Application.h"
#include "Keyboard.h"
#include "Drawer.h"
#include "Image.h"
#include "ImageTarget.h"

#include "define.h"
#include "Object.h"
#include "ObjectEditor.h"
#include "ObjectViewer.h"

const std::string DIRECTORY = "Resource/MapData/";

MapEditorPtr MapEditor::getTask( ) {
	return std::dynamic_pointer_cast< MapEditor >( Application::getInstance( )->getTask( getTag( ) ) );
}

MapEditor::MapEditor( ) :
_mode( MODE_EDIT ),
_init( false ) {
}

MapEditor::~MapEditor( ) {
}

void MapEditor::initialize( ) {
	_object = ObjectPtr( new Object );
	_editor = ObjectEditorPtr( new ObjectEditor( _object ) );
	_viewer = ObjectViewerPtr( new ObjectViewer( _object ) );
}

void MapEditor::update( ) {
	Drawer::getTask( )->flip( );
	updateMode( );
	drawInfo( );
	switch ( _mode ) {
	case MODE_EDIT:
		modeEditing( );
		break;
	case MODE_SAVE:
		modeSaveing( );
		_mode = MODE_EDIT;
		break;
	case MODE_LOAD:
		modeLoading( );
		_mode = MODE_EDIT;
		break;
	case MODE_INIT:
		modeInitialize( );
		break;
	}
}

void MapEditor::drawInfo( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	switch ( _mode ) {
	case MODE_EDIT:
		{
			std::string str = "編集中：";
			switch ( _editor->getMode( ) ) {
			case ObjectEditor::MODE_NONE:		  str += "削除\n"; break;
			case ObjectEditor::MODE_WALL:		  str += "壁\n"; break;
			case ObjectEditor::MODE_FEED:		  str += "餌\n"; break;
			case ObjectEditor::MODE_ENHANCE_FEET: str += "パワーエサ\n"; break;
			case ObjectEditor::MODE_PLAYER1:	  str += "プレイヤー1\n"; break;
			case ObjectEditor::MODE_PLAYER2:	  str += "プレイヤー2\n"; break;
			case ObjectEditor::MODE_SAHDOW:	      str += "アカベエ\n"; break;
			case ObjectEditor::MODE_SPEEDY:       str += "ピンキー\n"; break;
			case ObjectEditor::MODE_BASHFUL:	  str += "アオスケ\n"; break;
			case ObjectEditor::MODE_POKEY:        str += "グズタ\n"; break;
			case ObjectEditor::MODE_STAGE_WARP:	  str += "ワープブロック\n"; break;
			case ObjectEditor::MODE_REVIVAL_FEED: str += "エサ復活ポジション\n"; break;
			}
			str += "1:削除\n";
			str += "2:壁\n";
			str += "3:餌\n";
			str += "4:パワーエサ\n";
			str += "5:ワープブロック\n";
			str += "6:エサ復活ポジション\n";
			str += "Q:プレイヤー１\n";
			str += "W:プレイヤー２\n";
			str += "E:アカベエ\n";
			str += "R:ピンキー\n";
			str += "T:アオスケ\n";
			str += "Y:グズタ\n";
			drawer->drawString( 0, 10, str.c_str( ) );
		}
		break;
	case MODE_SAVE:
		drawer->drawString( 0, 10, "セーブ\nキャンセル：何も入力せずEnter\nfilename" );
		break;
	case MODE_LOAD:
		drawer->drawString( 0, 10, "ロード\nキャンセル：何も入力せずEnter\nfilename" );
		break;
	case MODE_INIT:
		{
			std::string message = "初期化\n本当に初期化しますか\n";
			if ( _init ) {
				message += "→ yes    no";
			} else {
				message += "   yes → no";
			}
			drawer->drawString( 0, 10, message.c_str( ) );
		}
		break;
	}

	{
		std::string message = "F1：セーブ\n";
		message += "F2：ロード\n";
		message += "F9：初期化";
		drawer->drawString( 1150, 10, message.c_str( ) );
	}
}

void MapEditor::updateMode( ) {
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "F1" ) ) {
		_mode = MODE_SAVE;
	}
	if ( key->isPushKey( "F2" ) ) {
		_mode = MODE_LOAD;
	}
	if ( key->isPushKey( "F9" ) ) {
		_mode = MODE_INIT;
	}
}

void MapEditor::modeEditing( ) {
	_editor->update( );
	_viewer->draw( );
	_editor->drawCursor( );
}

void MapEditor::modeSaveing( ) {
	std::string filename = Application::getInstance( )->inputString( 80, 47 );
	if ( filename.size( ) == 0 ) {
		return;
	}

	_object->save( DIRECTORY, filename );
	ImageTargetPtr stage = _viewer->getStageSprite( );
	std::string image_name = filename;
	int pos = ( int )image_name.find( "." );
	if ( pos != std::string::npos ) {
		image_name.erase( pos );
	}
	image_name += "_stage";
	stage->save( DIRECTORY + image_name );
}

void MapEditor::modeLoading( ) {
	std::string filename = Application::getInstance( )->inputString( 80, 47 );
	if ( filename.size( ) == 0 ) {
		return;
	}

	_object->load( DIRECTORY, filename );
}

void MapEditor::modeInitialize( ) {
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "ARROW_LEFT" ) ) {
		_init = true;
	}
	if ( key->isPushKey( "ARROW_RIGHT" ) ) {
		_init = false;
	}
	if ( key->isPushKey( "ENTER" ) ) {
		if ( _init ) {
			_editor->initData( );
		}
		_init = false;
		_mode = MODE_EDIT;
	}
}
