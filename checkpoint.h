#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "obstacle.h"

class Checkpoint : public Obstacle
{
public:
    Checkpoint(int startX, int startY, float xVelocity, int height, int width, QColor color, int xBack, int yBack, int level);
    void render(QPainter &painter, int collisioncheck, bool invuln) const;
    void update();
    void setMax(float max);
    int hasCollided(int x, int y, int width, int height) const;
    void setXVelocity(int x);
    void resetLevel();
    ~Checkpoint();
private:
    int m_x;
    int m_y;
    int m_xVelocity;
    int m_height;
    int m_width;
    QColor m_color;
    int m_xBack;
    int m_yBack;
    float m_max;
    int m_level;
    QImage checkpointimage;
    int m_initialx;
};

#endif // CHECKPOINT_H
