#ifndef GAME_H
#define GAME_H

#include "mainmenu.h"
#include "gameover.h"
#include "hero.h"
#include "strangerect.h"
#include <QWidget>
#include <QDateTime>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QSound>

namespace Ui {
class Game;
}


class Game : public QWidget {
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);

    void startMenu(int bestScore);

    int bestScore = 0;

    ~Game();

private:

    mainMenu menu;

    gameOver gameover;

    Ui::Game *ui;

    QGraphicsScene *scene;

    Hero hero;

    StrangeRect strangeRect;

    QGraphicsSimpleTextItem *scoreText;

    QTimer *gameTimer;

    QTimer *scoreTimer;

    QTimer *eventTimer;

    QTimer *timerFlickerEvent = nullptr;

    QTimer *timerDiskoEvent = nullptr;

    bool stop = false;

    int score = 0;

    QSound *music;

    QSound *crashMusic;

    bool newSpeed = false;

 //   void ( *masEvent[] )( void ) = { changeBackgroundEvent, newSpeedEvent, freezeEvent, invisibleEvent, disguiseEvent, flickerEvent, diskoEvent };

  //  void (*pfn_MyFuncType[10])(char * str, int len);

  //  typedef void func_type( );

   // func_type* masEvent[] = { changeBackgroundEvent, newSpeedEvent, freezeEvent, invisibleEvent, disguiseEvent, flickerEvent, diskoEvent };








    void moveToCenter();

    void newGame();

    void Play();

    void newBestScore();

    int gameIteration();

    void musicFiles();


    void changeBackgroundEvent();

    void freezeEvent();

    void invisibleEvent();

    void disguiseEvent();

    void newSpeedEvent();

    void flickerEvent();

    void diskoEvent();

    void endAllEvents();

private slots:

    void Ready();

    void exitGameAndMenu();

    void exitGameIsOver();

    virtual void keyPressEvent( QKeyEvent *event );

    virtual void keyReleaseEvent( QKeyEvent *event );

    void scoreIncrease();

    void changeScore( int score );


    void randomGameEvent();

    void endChangeBackgroundEvent();

    void endFreezeEvent();

    void endInvisibleEvent();

    void endDisguiseEvent();

    void endNewSpeedEvent();

    void endFlickerEvent();

    void changeInvisibleEvent();

    void endDiskoEvent();

    void diskoBackgroundEvent();

};

#endif // GAME_H
