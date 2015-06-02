#ifndef TINYSTICKMAN_H
#define TINYSTICKMAN_H

#include "stickman.h"

class TinyStickman : public Stickman
{
public:
    TinyStickman(const std::vector<QPixmap> &sprites);
    ~TinyStickman();

    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual int getGravity() const;
    virtual void setScale(int scale);
    virtual void setGravity(double gravity);
private:
    int m_scale;
    double m_gravityscale;

};

#endif // TINYSTICKMAN_H
