#include "game.h"
#include "ui_game.h"
#include "const.h"
#include <random>
#include <QKeyEvent>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopWidget>


Game::Game( QWidget *parent ) :
        QWidget( parent ),
        ui( new Ui::Game ) {
    ui->setupUi( this );

    scene = new QGraphicsScene( 0, 0, SCENE_X, SCENE_Y, this );
    scene->setBackgroundBrush( BACKGROUND_COLOR );
    ui->graphicsView->setScene( scene );

    scoreText = scene->addSimpleText( "0" );
    QFont font(" Purisa", 12, QFont::Bold );
    scoreText->setFont(font);
    scoreText->setPos( SCENE_X - 20, 10 );

    strangeRect.init( scene );

    hero.rectangle = scene->addRect( PLAYER_POSITION, SCENE_Y - HERO_SIZE, HERO_SIZE, HERO_SIZE, ( QPen ) HERO_COLOR, ( QBrush ) HERO_COLOR );

    if ( QFile::exists( "score.bin" ) ) {
        QFile in( "score.bin" );
        if ( in.open( QIODevice::ReadOnly ) ) {
            QDataStream stream( &in );
            stream >> bestScore;
            qDebug() << bestScore;
            in.close();
        }
    }

    connect( &menu, SIGNAL( on_pushButton_clicked() ), this, SLOT( Ready() ) );
    connect( &gameover, SIGNAL( on_newGameButton_clicked() ), this, SLOT( Ready() ) );
    connect( &menu, SIGNAL( on_pushButton_2_clicked() ), this, SLOT( exitGameAndMenu() ) );
    connect( &gameover, SIGNAL( on_pushButton_2_clicked() ), this, SLOT( exitGameIsOver() ) );

    musicFiles();

    moveToCenter();
}

Game::~Game() {
    delete ui;
}

void Game::moveToCenter() {
    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry( desktop.primaryScreen() );
    QPoint center = rect.center();
    center.setX( center.x() - ( this->width() / 4 ) );
    center.setY( center.y() - ( this->height() / 4 ) );
    move( center );

}

void Game::startMenu( int bestScore ) {
    menu.setFixedSize( MENU_X, MENU_Y );
    menu.setBestScore( bestScore );
    menu.move( this->width() / 2 + this->x() - menu.width() / 2, this->height() / 2 + this->y() - menu.height() / 2 );
    menu.show();
}

void Game::exitGameAndMenu() {
    close();
    menu.close();
}

void Game::exitGameIsOver() {
    close();
    gameover.close();
}

void Game::Ready() {

//    scene->setBackgroundBrush( SCENE_COLOR );
    hero.rectangle->setPos( 0, 0 );
    hero.playerPosition = 0;
    hero.playerPrevTime = QDateTime::currentDateTime();

    strangeRect.ready();

    score = 0;
    changeScore( score );

    hero.pressLeft = false;
    hero.pressRight = false;

    scoreTimer = new QTimer( this );
    connect( scoreTimer, SIGNAL( timeout() ), this, SLOT( scoreIncrease() ) );
    scoreTimer->start( 0 );
    scoreTimer->setInterval( 1000 );

    eventTimer = new QTimer( this );
    connect( eventTimer, SIGNAL( timeout() ), this, SLOT( randomGameEvent() ) );
    eventTimer->start( 0 );
    eventTimer->setInterval( 5000 );

    music->setLoops( -1 );
    music->play();

    Play();
}


void Game::Play() {
    while ( !gameIteration() ) {
        QCoreApplication::processEvents();
    }
}

void Game::newBestScore() {
    bestScore = score;

    QFile out( "score.bin" );
    if ( out.open( QIODevice::WriteOnly ) ) {
        QDataStream stream( &out );
        stream << bestScore;
        out.close();
    }
}


int Game::gameIteration() {

    hero.move();
    if ( !stop ) {
        strangeRect.move();
    }
    hero.draw();
    int i = strangeRect.draw( hero );
    scene->update();


    if ( i == 1 ) {
        music->stop();
        crashMusic->play();

        if ( score >= bestScore ) {
            newBestScore();
        }

        scoreTimer->stop();
        eventTimer->stop();
        endAllEvents();
        gameover.setFixedSize( GAMEOVER_X, GAMEOVER_Y );
        gameover.gameIsOver( bestScore, score );
        gameover.move( this->width() / 2 + this->x() - gameover.width() / 2,
                       this->height() / 2 + this->y() - gameover.height() / 2 );
        gameover.show();

        return 1;

    }
    return 0;
}


void Game::keyPressEvent( QKeyEvent *event ) {
    switch ( event->key() ) {
        case Qt::Key_Left:
            hero.pressLeft = true;
            break;
        case Qt::Key_Right:
            hero.pressRight = true;
            break;
    }
}

void Game::keyReleaseEvent( QKeyEvent *event ) {
    switch ( event->key() ) {
        case Qt::Key_Left:
            hero.pressLeft = false;
            break;
        case Qt::Key_Right:
            hero.pressRight = false;
            break;
    }
}

void Game::scoreIncrease() {
    score++;
    changeScore( score );
}

void Game::changeScore( int score )
{
    QFont font("Purisa", 12, QFont::Bold );
    scoreText->setFont(font);
    scoreText->setText( QString::number( score ) );
}

void Game::musicFiles()
{
    QFile out( "music" );
    if ( !out.exists() ) {
        QFile in( ":/sounds/music" );
        in.open( QIODevice::ReadOnly );
        out.open( QIODevice::WriteOnly );
        out.write( in.readAll() );
        out.close();
    }

    music = new QSound( "music", this );

    QFile outCrashed( "crashMusic" );
    if ( !outCrashed.exists() ) {
        QFile in( ":/sounds/crashMusic" );
        in.open( QIODevice::ReadOnly );
        outCrashed.open( QIODevice::WriteOnly );
        outCrashed.write( in.readAll() );
        outCrashed.close();
    }

    crashMusic = new QSound( "crashMusic", this );

}



void Game::randomGameEvent() {
    std::random_device rand;
    std::mt19937 generator( rand() );
    std::uniform_int_distribution<> distr( 0, 6 );
    int indx = distr( generator );

  //  masEvent[indx]();
    switch ( indx ) {
        case 0:
            changeBackgroundEvent();
            break;
        case 1:
            newSpeedEvent();
            break;
        case 2:
            freezeEvent();
            break;
        case 3:
            invisibleEvent();
            break;
        case 4:
            disguiseEvent();
            break;
        case 5:
            flickerEvent();
            break;
        case 6:
            diskoEvent();
            break;
    }

}

void Game::endAllEvents() {
    if ( newSpeed ) {
        strangeRect.newSpeed( -10 );
        newSpeed = false;
    }
    if ( timerFlickerEvent != nullptr ) {
        timerFlickerEvent->stop();
    }
    if ( timerDiskoEvent != nullptr ) {
        timerDiskoEvent->stop();
    }
    strangeRect.invisible = false;
    strangeRect.invisibleNew();
    scene->setBackgroundBrush( BACKGROUND_COLOR );
    strangeRect.changeColour( QBrush( Qt::black ), QPen( Qt::black ) );
    hero.rectangle->setVisible( true );
    stop = false;
}


void Game::changeBackgroundEvent() {
    scene->setBackgroundBrush( QBrush( Qt::darkBlue ) );
    QTimer::singleShot( 5000, this, SLOT( endChangeBackgroundEvent() ) );
}



void Game::endChangeBackgroundEvent() {
    scene->setBackgroundBrush( QBrush( BACKGROUND_COLOR ) );
}


void Game::freezeEvent() {
    stop = true;
    QTimer::singleShot( 3000, this, SLOT( endFreezeEvent() ) );
}

void Game::endFreezeEvent() {
    strangeRect.reverseTime();
    stop = false;
}


void Game::invisibleEvent() {
    hero.rectangle->setVisible( false );
    QTimer::singleShot( 2000, this, SLOT( endInvisibleEvent() ) );
}

void Game::endInvisibleEvent() {
    hero.rectangle->setVisible( true );

}

void Game::changeInvisibleEvent() {
    strangeRect.invisibleNew();
}


void Game::disguiseEvent() {
    strangeRect.changeColour( QBrush( BACKGROUND_COLOR ),
                              QPen( Qt::white ) );//hero.rectangle->brush(), hero.rectangle->pen() );
    QTimer::singleShot( 5000, this, SLOT( endDisguiseEvent() ) );
}

void Game::endDisguiseEvent() {
    strangeRect.changeColour( QBrush( Qt::black ), QPen( Qt::black ) );
}


void Game::newSpeedEvent() {
    strangeRect.newSpeed( 10 );
    newSpeed = true;
    QTimer::singleShot( 4000, this, SLOT( endNewSpeedEvent() ) );
}

void Game::endNewSpeedEvent() {
    if ( newSpeed ) {
        strangeRect.newSpeed( -10 );
        newSpeed = false;
    }
}


void Game::flickerEvent() {
    timerFlickerEvent = new QTimer( this );
    connect( timerFlickerEvent, SIGNAL( timeout() ), this, SLOT( changeInvisibleEvent() ) );
    timerFlickerEvent->start( 0 );
    timerFlickerEvent->setInterval( 200 );
    QTimer::singleShot( 3100, this, SLOT( endFlickerEvent() ) );
}

void Game::endFlickerEvent() {
    timerFlickerEvent->stop();
    strangeRect.invisible = false;
    strangeRect.invisibleNew();
}


void Game::diskoEvent() {
    timerDiskoEvent = new QTimer( this );
    connect( timerDiskoEvent, SIGNAL( timeout() ), this, SLOT( diskoBackgroundEvent() ) );
    timerDiskoEvent->start( 0 );
    timerDiskoEvent->setInterval( 150 );
    QTimer::singleShot( 3100, this, SLOT( endDiskoEvent() ) );
}

void Game::diskoBackgroundEvent() {
    std::random_device rand;
    std::mt19937 generator( rand() );
    std::uniform_int_distribution<> distr( 2, 17 );
    int indx = distr( generator );
    scene->setBackgroundBrush( QColor( Qt::GlobalColor( indx ) ) );
}

void Game::endDiskoEvent() {
    timerDiskoEvent->stop();
    scene->setBackgroundBrush( BACKGROUND_COLOR );
}
