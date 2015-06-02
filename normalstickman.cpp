#include "normalstickman.h"

NormalStickman::NormalStickman(const std::vector<QPixmap> &sprites) :
    Stickman(STICKMAN_NORMAL, sprites),
    m_scale(2),
    m_gravityscale(1)
{
}

NormalStickman::~NormalStickman()
{
}

int NormalStickman::getWidth() const
{
    return getSprite().width() * m_scale;
}

int NormalStickman::getHeight() const
{
    return getSprite().height() * m_scale;
}
int NormalStickman::getGravity() const
{
    return m_gravity * m_gravityscale;
}

void NormalStickman::setScale(int scale) {
    m_scale = scale;
}


void NormalStickman::setGravity(double gravity) {
    m_gravityscale = gravity;
}
