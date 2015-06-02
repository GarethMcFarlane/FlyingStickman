#ifndef DIALOG_H
#define DIALOG_H

#include "background.h"
#include "configreader.h"
#include "compositeobstacle.h"
#include "stickman.h"
#include "gamemediator.h"


#include <QDialog>
#include <QKeyEvent>
#include <sstream>
#include <QLabel>
#include <QMovie>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void nextFrame();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* e);

private:
    // Reads from a configuration file and initialises the game.
    // Returns false if there are settings missing, in which case default values are used.
    bool loadConfiguration(const ConfigReader &reader);
    Ui::Dialog *ui;
    int m_timerMs;
    Stickman *m_stickman;
    Background *m_background;
    bool m_paused;
    bool m_finished;
    bool m_won;
    bool m_pauseScreenEnabled;
    QImage m_pauseImage;
    CompositeObstacle** m_levels;
    int m_xCollisionCheck;
    int m_maxjumps;
    int m_jumps;
    QTimer* m_timer;
    int m_moveSpeed;
    int m_score;
    int m_levelnum;
    int m_currlevel;
    std::vector<QPixmap> m_sprites;
    QLabel label;
    QMovie *explosion;
    int m_explosioncounter;
    bool m_invuln;
    GameMediator *mediator;

};

#endif // DIALOG_H
