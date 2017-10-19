#pragma once

const int WIDTH = 1280;
const int HEIGHT = 720;

//Editor
const int CHIP_SIZE = 16;
const int MAP_WIDTH_CHIP_NUM = 75;
const int MAP_HEIGHT_CHIP_NUM = 30;
const int DRAW_X = ( WIDTH - ( CHIP_SIZE * MAP_WIDTH_CHIP_NUM ) ) / 2;
const int DRAW_Y = HEIGHT - ( CHIP_SIZE * MAP_HEIGHT_CHIP_NUM );

const unsigned char OBJECT_NONE         = 0x00;
const unsigned char OBJECT_WALL         = 0x01;
const unsigned char OBJECT_FEED         = 0x02;
const unsigned char OBJECT_ENHANCE_FEED = 0x03;
