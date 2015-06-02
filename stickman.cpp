#include "stickman.h"

Stickman::Stickman(StickmanSize size, const std::vector<QPixmap> &sprites) :
    m_gravity(7),
    m_size(size),
    m_xOffset(0),
    m_xPosition(0),
    m_xVelocity(0),
    m_yVelocity(0),
    m_yOffset(0),
    m_sprites(sprites),
    m_curSpriteIdx(0),
    m_spriteDurationMs(1000),
    m_curSpriteDurationMs(0),
    m_currlevel(1)
{
}

Stickman::~Stickman()
{
}

void Stickman::render(QPainter &painter) const
{
    // Draw the stickman at the bottom of the screen
    int yPos = painter.device()->height() - getHeight() - m_yOffset;

    // Find how much to scale the sprite image by to match the bounding box of the stickman
    // If x velocity is negative, we flip the image as well.
    float scaleX = getWidth() / getSprite().width() * (m_xVelocity < 0 ? -1 : 1);
    float scaleY = getHeight() / getSprite().height();

    painter.drawPixmap(m_xOffset, yPos, getSprite().transformed(QTransform().scale(scaleX, scaleY)));
}

void Stickman::update(int ms)
{
    // Move the stickman
    m_xPosition += m_xVelocity;
    // Change the stickman's sprite to the next frame if we've spent too long on the current frame.
    m_curSpriteDurationMs += ms;
    if (m_curSpriteDurationMs > m_spriteDurationMs) {
        m_curSpriteIdx = (m_curSpriteIdx + 1) % m_sprites.size();
        m_curSpriteDurationMs = 0;
    }
}
void Stickman::updateJump(){
    if(m_yVelocity <= 0 && m_yOffset == 0){
        return;
    }
    m_yOffset += m_yVelocity;
    m_yVelocity -= this->getGravity();
    if(m_yOffset <= 0){
        m_yOffset = 0;
        m_yVelocity = 0;
    }
}

int Stickman::getXOffset() const
{
    return m_xOffset;
}

void Stickman::setXOffset(int value)
{
    m_xOffset = value;
}

float Stickman::getXPosition() const
{
    return m_xPosition;
}

float Stickman::getXVelocity() const
{
    return m_xVelocity;
}

void Stickman::setXVelocity(float value)
{
    m_xVelocity = value;
}

void Stickman::setYVelocity(float value)
{
    m_yVelocity = value;
}

int Stickman::getYOffset() const{
    return m_yOffset;
}

float Stickman::getYVelocity() const{
    return m_yVelocity;
}

StickmanSize Stickman::getSize() const
{
    return m_size;
}

int Stickman::getSpriteDuration() const
{
    return m_spriteDurationMs;
}

void Stickman::setSpriteDuration(int ms)
{
    m_spriteDurationMs = ms;
}

const QPixmap &Stickman::getSprite() const
{
    return m_sprites[m_curSpriteIdx];
}

void Stickman::setLives(int lives) {
    m_lives = lives;
}

void Stickman::loseLife() {
    m_lives--;
}

int Stickman::getLives() {
    return m_lives;
}


int Stickman::getJumps() {
    return m_jumps;
}

int Stickman::getMaxJumps() {
    return m_maxjumps;
}

void Stickman::setJumps(int jumps) {
    m_jumps = jumps;
}

void Stickman::setMaxJumps(int jumps) {
    m_maxjumps = jumps;
}


void Stickman::setCurrlevel(int level) {
    m_currlevel = level;
}

int Stickman::getCurrLevel() {
    return m_currlevel;
}
