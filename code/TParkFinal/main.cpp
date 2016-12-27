#include "game.h"
#include "const.h"
#include <QApplication>

int main( int argc, char *argv[] ) {

    QApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

    QApplication a( argc, argv );

    Game w;

    w.setFocus();
    w.setFixedSize( SCENE_X + 3, SCENE_Y + 3 );
    w.show();
    w.startMenu( w.bestScore );


    return a.exec();
}
