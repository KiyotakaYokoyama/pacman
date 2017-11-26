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
			std::string str = "�ҏW���F";
			switch ( _editor->getMode( ) ) {
			case ObjectEditor::MODE_NONE:		  str += "�폜\n"; break;
			case ObjectEditor::MODE_WALL:		  str += "��\n"; break;
			case ObjectEditor::MODE_FEED:		  str += "�a\n"; break;
			case ObjectEditor::MODE_ENHANCE_FEET: str += "�p���[�G�T\n"; break;
			case ObjectEditor::MODE_PLAYER1:	  str += "�v���C���[1\n"; break;
			case ObjectEditor::MODE_PLAYER2:	  str += "�v���C���[2\n"; break;
			case ObjectEditor::MODE_SAHDOW:	      str += "�A�J�x�G\n"; break;
			case ObjectEditor::MODE_SPEEDY:       str += "�s���L�[\n"; break;
			case ObjectEditor::MODE_BASHFUL:	  str += "�A�I�X�P\n"; break;
			case ObjectEditor::MODE_POKEY:        str += "�O�Y�^\n"; break;
			case ObjectEditor::MODE_STAGE_WARP:	  str += "���[�v�u���b�N\n"; break;
			case ObjectEditor::MODE_REVIVAL_FEED: str += "�G�T�����|�W�V����\n"; break;
			}
			str += "1:�폜\n";
			str += "2:��\n";
			str += "3:�a\n";
			str += "4:�p���[�G�T\n";
			str += "5:���[�v�u���b�N\n";
			str += "6:�G�T�����|�W�V����\n";
			str += "Q:�v���C���[�P\n";
			str += "W:�v���C���[�Q\n";
			str += "E:�A�J�x�G\n";
			str += "R:�s���L�[\n";
			str += "T:�A�I�X�P\n";
			str += "Y:�O�Y�^\n";
			drawer->drawString( 0, 10, str.c_str( ) );
		}
		break;
	case MODE_SAVE:
		drawer->drawString( 0, 10, "�Z�[�u\n�L�����Z���F�������͂���Enter\nfilename" );
		break;
	case MODE_LOAD:
		drawer->drawString( 0, 10, "���[�h\n�L�����Z���F�������͂���Enter\nfilename" );
		break;
	case MODE_INIT:
		{
			std::string message = "������\n�{���ɏ��������܂���\n";
			if ( _init ) {
				message += "�� yes    no";
			} else {
				message += "   yes �� no";
			}
			drawer->drawString( 0, 10, message.c_str( ) );
		}
		break;
	}

	{
		std::string message = "F1�F�Z�[�u\n";
		message += "F2�F���[�h\n";
		message += "F9�F������";
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
