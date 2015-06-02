#include "tinystickman.h"

TinyStickman::TinyStickman(const std::vector<QPixmap> &sprites) :
    Stickman(STICKMAN_TINY, sprites),
    m_scale(1),
    m_gravityscale(1)
{
}

TinyStickman::~TinyStickman()
{
}

int TinyStickman::getWidth() const
{
    return getSprite().width()*m_scale;
}

int TinyStickman::getHeight() const
{
    return getSprite().height() * m_scale;
}

int TinyStickman::getGravity() const
{
    return m_gravity * m_gravityscale;
}

void TinyStickman::setScale(int scale) {
    m_scale = scale;
}

void TinyStickman::setGravity(double gravity) {
    m_gravityscale = gravity;
}
