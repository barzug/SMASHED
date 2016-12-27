#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>

namespace Ui {
    class gameOver;
}

class gameOver : public QWidget {
    Q_OBJECT

public:
    explicit gameOver( QWidget *parent = 0 );

    ~gameOver();

    void gameIsOver( int bestScore, int score );

private:
    Ui::gameOver *ui;

signals:
    void on_newGameButton_clicked();

    void on_pushButton_2_clicked();
};

#endif // GAMEOVER_H
