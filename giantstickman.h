#ifndef GIANTSTICKMAN_H
#define GIANTSTICKMAN_H

#include "stickman.h"

class GiantStickman : public Stickman
{
public:
    GiantStickman(const std::vector<QPixmap> &sprites);
    ~GiantStickman();

    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual int getGravity() const;
    virtual void setScale(int scale);
    virtual void setGravity(double gravity);
private:
    int m_scale;
    double m_gravityscale;
};

#endif // GIANTSTICKMAN_H
