#include "hero.h"
#include "const.h"


void Hero::move() {
    double t = QDateTime::currentDateTime().toMSecsSinceEpoch() - playerPrevTime.toMSecsSinceEpoch();

    if ( pressLeft == true && playerPosition >= -PLAYER_POSITION + 1 ) {
        playerPosition -= 0.25 * t;
    }
    if ( pressRight == true && playerPosition <= PLAYER_POSITION + HERO_SIZE - 1 ) {
        playerPosition += 0.25 * t;
    }

    playerPrevTime = QDateTime::currentDateTime();
}

void Hero::draw() {
    rectangle->setPos( rectangle->mapToScene( playerPosition, 0 ) - QPointF( rectangle->x(), 0 ) );
}
