#ifndef LARGESTICKMAN_H
#define LARGESTICKMAN_H

#include "stickman.h"

class LargeStickman : public Stickman
{
public:
    LargeStickman(const std::vector<QPixmap> &sprites);
    ~LargeStickman();

    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual int getGravity() const;
    virtual void setScale(int scale);
    virtual void setGravity(double gravity);
private:
    int m_scale;
    double m_gravityscale;
};

#endif // LARGESTICKMAN_H
