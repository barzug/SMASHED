#include "gameover.h"
#include "ui_gameover.h"

gameOver::gameOver( QWidget *parent ) :
        QWidget( parent ),
        ui( new Ui::gameOver ) {
    ui->setupUi( this );
    connect( this, SIGNAL( on_newGameButton_clicked() ), this, SLOT( close() ) );
}

gameOver::~gameOver() {
    delete ui;
}

void gameOver::gameIsOver( int bestScore, int score ) {
    ui->label_2->setText( "Best score: " + QString::number( bestScore ) );
    ui->label_3->setText( "Your score: " + QString::number( score ) );
}


