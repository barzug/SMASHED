#ifndef CONST_H
#define CONST_H
#include "QColor"

const int SCENE_X = 290;
const int SCENE_Y = 290; //нечётные десятки

const int HERO_SIZE = 5;
const int STRANGE_RECT_SIZE = 4;

const int RECT_LINES = ( SCENE_Y + 10 ) / 20;

const int GAMEOVER_X = 200;
const int GAMEOVER_Y = 125;

const int MENU_X = 125;
const int MENU_Y = 125;

const int PLAYER_POSITION = SCENE_X / 2 - HERO_SIZE;




const QColor BACKGROUND_COLOR = Qt::yellow;

const QColor HERO_COLOR = Qt::blue;

#endif // CONST_H
