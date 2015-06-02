#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPainter>
#include <QPixmap>

class Obstacle
{
public:
    Obstacle();
    //Renders the obstacles
    virtual void render(QPainter &painter, int collisioncheck, bool invuln)const = 0;
    //Updates obstacles
    virtual void update() = 0;
    //Sets the reset point
    virtual void setMax(float max) = 0;
    //Checks for collision.  Returns 0 for no collision, -1 for collision, and the number of the next level if reached a checkpoint.
    virtual int hasCollided(int x, int y, int width, int height) const = 0;
    //Updates obstacle velocity
    virtual void setXVelocity(int x) = 0;
    //Resets level back to initial positions.
    virtual void resetLevel() = 0;
    virtual ~Obstacle();
};

#endif // OBSTACLE_H
