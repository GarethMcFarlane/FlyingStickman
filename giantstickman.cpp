#include "giantstickman.h"

GiantStickman::GiantStickman(const std::vector<QPixmap> &sprites) :
    Stickman(STICKMAN_GIANT, sprites),
    m_scale(8),
    m_gravityscale(1)
{
}

GiantStickman::~GiantStickman()
{
}

int GiantStickman::getWidth() const
{
    return getSprite().width() * m_scale;
}

int GiantStickman::getHeight() const
{
    return getSprite().height() * m_scale;
}
int GiantStickman::getGravity() const
{
    return m_gravity*m_gravityscale;
}

void GiantStickman::setScale(int scale) {
    m_scale = scale;
}

void GiantStickman::setGravity(double gravity) {
    m_gravityscale = gravity;
}
