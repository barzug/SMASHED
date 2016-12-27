#include "strangerect.h"


int StrangeRect::randCoordinate() {
    std::random_device rand;
    std::mt19937 generator( rand() );
    std::uniform_int_distribution<> distr( 0, SCENE_X - STRANGE_RECT_SIZE );
    int indx = distr( generator );
    return indx;
}

int StrangeRect::randSpeed() {
    std::random_device rand;
    std::mt19937 generator( rand() );
    std::uniform_int_distribution<> distr( 20, 30 );
    int indx = distr( generator );
    return indx;
}


void StrangeRect::init( QGraphicsScene *scene ) {
    for ( int j = 0; j < RECT_LINES; j++ ) {
        for ( int i = 0; i < 2; i++ ) {
            rect[i][j].rectangle = scene->addRect( -10, 0, STRANGE_RECT_SIZE, STRANGE_RECT_SIZE, ( QPen ) Qt::black, ( QBrush ) Qt::black );
            rect[i][j].speedFactor = randSpeed();
        }
    }
}

void StrangeRect::ready() {
    for ( int j = 0; j < RECT_LINES; j++ ) {
        for ( int i = 0; i < 2; i++ ) {
            rect[i][j].prevTime = QDateTime::currentDateTime();
            rect[i][j].rectangle->setPos( randCoordinate() + 10, -j * 20 );
            rect[i][j].position = -j * 20;
        }
    }
}


void StrangeRect::move() {
    for ( int j = 0; j < RECT_LINES; j++ ) {
        for ( int i = 0; i < 2; i++ ) {
            if ( rect[i][j].position < SCENE_Y + STRANGE_RECT_SIZE ) {
                double t = QDateTime::currentDateTime().toMSecsSinceEpoch() - rect[i][j].prevTime.toMSecsSinceEpoch();
                rect[i][j].position += t / 100.0 * rect[i][j].speedFactor;
            } else {
                rect[i][j].statusRand = true;
                rect[i][j].position = -10;
                }
            rect[i][j].prevTime = QDateTime::currentDateTime();
        }
    }
}

void StrangeRect::reverseTime() {
    for ( int j = 0; j < RECT_LINES; j++ ) {
        for ( int i = 0; i < 2; i++ ) {
            rect[i][j].prevTime = QDateTime::currentDateTime();
        }
    }
}

int StrangeRect::draw( Hero hero ) {
    for ( int j = 0; j < RECT_LINES; j++ ) {
        for ( int i = 0; i < 2; i++ ) {
            if ( !rect[i][j].statusRand ) {
                rect[i][j].rectangle->setPos( rect[i][j].rectangle->x(), rect[i][j].position );
            } else {
                rect[i][j].rectangle->setPos( randCoordinate() + 10, rect[i][j].position );
                rect[i][j].statusRand = false;
            }

            if ( hero.rectangle->collidesWithItem( rect[i][j].rectangle ) ) {
                return 1;
            }
        }
    }
    return 0;
}


void StrangeRect::newSpeed( int x ) {
    for ( int j = 0; j < RECT_LINES; j++ ) {
        for ( int i = 0; i < 2; i++ ) {
            rect[i][j].speedFactor += x;
        }
    }
}

void StrangeRect::changeColour( QBrush newBrush, QPen newPen ) {
    for ( int j = 0; j < RECT_LINES; j++ ) {
        for ( int i = 0; i < 2; i++ ) {
            rect[i][j].rectangle->setPen( newPen );
            rect[i][j].rectangle->setBrush( newBrush );
        }
    }
}

void StrangeRect::invisibleNew() {
    if ( invisible ) {
        invisible = false;
    } else {
        invisible = true;
    }
    for ( int j = 0; j < RECT_LINES; j++ ) {
        for ( int i = 0; i < 2; i++ ) {
            rect[i][j].rectangle->setVisible( invisible );
        }
    }
}

