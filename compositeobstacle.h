#ifndef COMPOSITEOBSTACLE_H
#define COMPOSITEOBSTACLE_H

#include "obstacle.h"

#include <QPainter>
#include <QPixmap>

class CompositeObstacle : public Obstacle
{
public:
    CompositeObstacle();
    void add(Obstacle *obst);
    void render(QPainter &painter, int collisioncheck, bool invuln) const;
    void update();
    void setMax(float max);
    int hasCollided(int x, int y, int width, int height) const;
    void setXVelocity(int x);
    void resetLevel();
    ~CompositeObstacle();


private:
    std::list<Obstacle*> m_obstacles;
};

#endif // COMPOSITEOBSTACLE_H
