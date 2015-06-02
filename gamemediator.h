#ifndef GAMEMEDIATOR_H
#define GAMEMEDIATOR_H
#include "background.h"
#include "configreader.h"
#include "compositeobstacle.h"
#include "stickman.h"
#include <QLabel>
#include <QMovie>


class GameMediator
{
public:
    GameMediator(Stickman *stickman, Background *background, CompositeObstacle** levels,int xcollisioncheck, int numlevels, bool pausescreen);
    ~GameMediator();
    void update();
    bool isFinished();
    bool isPaused();
    int getScore();
    bool getinvuln();


private:
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
    int m_moveSpeed;
    int m_score;
    int m_levelnum;
    int m_currlevel;
    std::vector<QPixmap> m_sprites;
    int m_explosioncounter;
    bool m_invuln;

};

#endif // GAMEMEDIATOR_H
