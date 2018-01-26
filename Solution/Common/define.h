#pragma once

const int WIDTH = 1920;
const int HEIGHT = 1080;
const int SPRITE_SIZE = 64;
enum PLAYER {
	PLAYER_1,
	PLAYER_2,
	MAX_PLAYER,
};
enum SCORE {
	SCORE_DAMAGE  = 0,
	SCORE_FEED    = 1,
	SCORE_SHADOW  = 10,
	SCORE_BASHFUL = 30,
	SCORE_SPEEDY  = 20,
	SCORE_POKEY   = 20,
	SCORE_BLUNDER = 50,
	SCORE_GREEN   = 30,
	SCORE_PURPLE  = 10,
	SCORE_YELLOW  = 30,
};

enum RESULT {
	RESULT_DRAW,
	RESULT_PLAYER1,
	RESULT_PLAYER2
};

struct IMGAE_DATA {
	int sx1;
	int sy1;
	int sx2;
	int sy2;
	int tx;
	int ty;
	int tw;
	int th;
	
	IMGAE_DATA( )  {
		this->sx1 =  0;
		this->sy1 =  0;
		this->tx  = -1;
		this->ty  = -1;
		this->tw  = -1;
		this->th  = -1;
		this->sx2 = -1;
		this->sy2 = -1;
	}
};

//Editor
const int MAP_WIDTH_CHIP_NUM = 75;
const int MAP_HEIGHT_CHIP_NUM = 30;
const int EDITOR_CHIP_SIZE = 16;
const int DRAW_X = ( WIDTH - ( EDITOR_CHIP_SIZE * MAP_WIDTH_CHIP_NUM ) ) / 2;
const int DRAW_Y = HEIGHT - ( EDITOR_CHIP_SIZE * MAP_HEIGHT_CHIP_NUM );

const unsigned char OBJECT_NONE          = 0x00;
const unsigned char OBJECT_WALL          = 0x01;
const unsigned char OBJECT_FEED          = 0x02;
const unsigned char OBJECT_ENHANCE_FEED  = 0x03;
const unsigned char OBJECT_PLAYER1       = 0x04;
const unsigned char OBJECT_PLAYER2       = 0x05;
const unsigned char OBJECT_SHADOW        = 0x06;
const unsigned char OBJECT_SPEEDY        = 0x07;
const unsigned char OBJECT_BASHFUL       = 0x08;
const unsigned char OBJECT_POKEY         = 0x09;
const unsigned char OBJECT_STAGE_WARP    = 0x0A;
const unsigned char OBJECT_REVIVAL_FEED  = 0x0B;
const unsigned char OBJECT_BLUNDER       = 0x0C;
const unsigned char OBJECT_GREEN         = 0x0D;
const unsigned char OBJECT_PURPLE        = 0x0E;
const unsigned char OBJECT_YELLOW        = 0x0F;
