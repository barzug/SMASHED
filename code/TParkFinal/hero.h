#ifndef HERO_H
#define HERO_H

#include <QGraphicsRectItem>
#include <QDateTime>


class Hero {
public:
    QGraphicsRectItem *rectangle;

    bool pressLeft = false;

    bool pressRight = false;

    double playerPosition = 0;

    QDateTime playerPrevTime;


    void move();

    void draw();
};


#endif // HERO_H
