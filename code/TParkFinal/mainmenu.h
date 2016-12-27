#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>


namespace Ui {
    class mainMenu;
}

class mainMenu : public QWidget {
    Q_OBJECT

public:
    explicit mainMenu( QWidget *parent = 0 );

    ~mainMenu();

    void setBestScore( int newBestScore );

private:
    Ui::mainMenu *ui;

    int bestScore;

signals:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

};

#endif // MAINMENU_H
