#ifndef STICKMAN_H
#define STICKMAN_H

#include <QPainter>
#include <QPixmap>

enum StickmanSize
{
    STICKMAN_TINY,
    STICKMAN_NORMAL,
    STICKMAN_LARGE,
    STICKMAN_GIANT
};

class Stickman
{
public:
    // Initialises a new stickman
    // sprites is a list of animation frames
    Stickman(StickmanSize size, const std::vector<QPixmap> &sprites);
    virtual ~Stickman();

    virtual void render(QPainter &painter) const;
    virtual void update(int ms);
    virtual void updateJump();

    // X coordinate of the stickman on the screen
    int getXOffset() const;
    void setXOffset(int value);

    // X position of the stickman in the game world
    float getXPosition() const;

    // X velocity of the stickman in the game world
    float getXVelocity() const;
    void setXVelocity(float value);

    //Set Jump Velocity
    void setYVelocity(float value);
    //get Y position
    int getYOffset() const;
    //get Y velocity
    float getYVelocity() const;

    StickmanSize getSize() const;

    // Bounding box for the stickman
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    //get the effect of gravity for each stickman
    virtual int getGravity() const = 0;
    virtual void setScale(int scale) = 0;
    virtual void setGravity(double gravity) = 0;



    // Duration of each frame in ms
    int getSpriteDuration() const;
    void setSpriteDuration(int ms);

    //Sets number of lives
    void setLives(int lives);
    void loseLife();
    int getLives();

    void setMaxJumps(int jumps);
    int getMaxJumps();

    void setJumps(int jumps);
    int getJumps();

    void setCurrlevel(int level);
    int getCurrLevel();

protected:
    const QPixmap &getSprite() const;
    float m_gravity;

private:
    StickmanSize m_size;
    int m_xOffset;
    float m_xPosition;
    float m_xVelocity;

    float m_yVelocity;
    int m_yOffset;

    std::vector<QPixmap> m_sprites; // List of sprites for each frame
    std::vector<QPixmap>::size_type m_curSpriteIdx; // Index of the current frame of the sprite
    int m_spriteDurationMs; // Duration of each frame in ms
    int m_curSpriteDurationMs; // How long the current sprite has been shown for

    int m_lives;
    int m_jumps;
    int m_maxjumps;

    int m_currlevel;


};

#endif // STICKMAN_H
