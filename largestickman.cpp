#include "largestickman.h"

LargeStickman::LargeStickman(const std::vector<QPixmap> &sprites) :
    Stickman(STICKMAN_LARGE, sprites),
    m_scale(4),
    m_gravityscale(1)
{
}

LargeStickman::~LargeStickman()
{
}

int LargeStickman::getWidth() const
{
    return getSprite().width() * m_scale;
}

int LargeStickman::getHeight() const
{
    return getSprite().height() * m_scale;
}
int LargeStickman::getGravity() const
{
    return m_gravity * m_gravityscale;
}

void LargeStickman::setScale(int scale) {
    m_scale = scale;
}

void LargeStickman::setGravity(double gravity) {
    m_gravityscale = gravity;
}
