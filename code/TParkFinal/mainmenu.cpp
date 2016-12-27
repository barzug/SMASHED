#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
    connect( this, SIGNAL( on_pushButton_clicked() ),this, SLOT(close()));

}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::setBestScore(int newBestScore)
{
    bestScore = newBestScore;
    ui->label->setText("Best score: ");
    ui->label_2->setText(QString::number(bestScore));
}
