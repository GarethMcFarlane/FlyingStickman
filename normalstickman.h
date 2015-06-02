#ifndef NORMALSTICKMAN_H
#define NORMALSTICKMAN_H

#include "stickman.h"

class NormalStickman : public Stickman
{
public:
    NormalStickman(const std::vector<QPixmap> &sprites);
    ~NormalStickman();

    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual int getGravity() const;
    virtual void setScale(int scale);
    virtual void setGravity(double gravity);
private:
    int m_scale;
    double m_gravityscale;
};

#endif // NORMALSTICKMAN_H
