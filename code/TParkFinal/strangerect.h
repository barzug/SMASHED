#ifndef STRANGERECT_H
#define STRANGERECT_H

#include <QDateTime>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "hero.h"
#include "const.h"

struct Rect_t {
    int speedFactor;

    double position;

    bool statusRand = false;

    QDateTime prevTime;

    QGraphicsRectItem *rectangle;
};


class StrangeRect {
public:
    bool invisible = false;

    void init( QGraphicsScene *scene );

    void ready();

    void move();

    void reverseTime();

    int draw( Hero hero );

    int randCoordinate();

    int randSpeed();

    void newSpeed( int x );

    void changeColour( QBrush newBrush, QPen newPen );

    void invisibleNew();

private:
    Rect_t rect[2][RECT_LINES];
};

#endif // STRANGERECT_H
