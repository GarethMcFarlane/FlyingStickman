#include "dialog.h"

#include "circleobstacle.h"
#include "configreader.h"
#include "rectangleobstacle.h"
#include "stickmanfactory.h"
#include "triangleobstacle.h"
#include "checkpoint.h"
#include "tinypowerup.h"
#include "normalpowerup.h"
#include "largepowerup.h"
#include "giantpowerup.h"

#include "ui_dialog.h"

#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include <sstream>
#include <iostream>


bool Dialog::loadConfiguration(const ConfigReader &reader)
{
    bool successful = true;
    bool parseOk = false;

    // Parse frame rate
    int frameRate = QString(reader.get("Game", "FrameRate").c_str()).toInt(&parseOk);
    if (!parseOk || frameRate <= 0 || frameRate > 1000) {
        frameRate = 30;
        successful = false;
    }

    m_timerMs = 1000 / frameRate;

    // Parse pause screen on/off
    std::string pauseScreenStatus = reader.get("Game", "PauseScreen");
    if (pauseScreenStatus != "on" && pauseScreenStatus != "off") {
        pauseScreenStatus = "on";
        successful = false;
    }

    m_pauseScreenEnabled = (pauseScreenStatus == "on");


    // Parse background image
    QPixmap bgImage;
    if (!bgImage.load(QString(reader.get("Background", "Sprite").c_str()))) {
        bgImage.load(":/resources/background.png");
        successful = false;
    }

    m_background = new Background(bgImage);

    // Parse background size
    int screenWidth = QString(reader.get("Background", "Width").c_str()).toInt(&parseOk);
    if (!parseOk || screenWidth <= 0) {
        screenWidth = bgImage.width() * 2;
        successful = false;
    }

    int screenHeight = QString(reader.get("Background", "Height").c_str()).toInt(&parseOk);
    if (!parseOk || screenHeight <= 0) {
        screenHeight = bgImage.height();
        successful = false;
    }

    setFixedSize(screenWidth, screenHeight);

    // Parse day duration for night filter effect
    int dayDuration = QString(reader.get("Background", "DayDuration").c_str()).toInt(&parseOk);
    if (!parseOk || dayDuration < 0) {
        dayDuration = 60000; // Defaults to 1 minute
        successful = false;
    }

    m_background->setDayDuration(dayDuration);

    // Parse stickman size
    std::string stickmanSize = reader.get("Stickman", "Size");
    if (stickmanSize != "tiny" && stickmanSize != "normal" && stickmanSize != "large" && stickmanSize != "giant") {
        stickmanSize = "normal";
        successful = false;
    }

    // Parse stickman sprites

    std::istringstream ss(reader.get("Stickman", "Sprites").c_str());

    std::string stickmanSpritePath;
    while (ss >> stickmanSpritePath) {
        QPixmap sprite;
        if (!sprite.load(stickmanSpritePath.c_str())) {
            m_sprites.clear();
            break;
        }
        m_sprites.push_back(sprite);
    }

    if (m_sprites.empty()) {
        m_sprites.push_back(QPixmap(":/resources/flap_up.png"));
        m_sprites.push_back(QPixmap(":/resources/flap_down.png"));
        successful = false;
    }

    // Now we've got enough information to construct a stickman
    m_stickman = StickmanFactory::create(stickmanSize, m_sprites);

    // Parse other stickman properties
    int stickmanXOffset = QString(reader.get("Stickman", "XOffset").c_str()).toInt(&parseOk);
    if (!parseOk ||!( stickmanXOffset >0 && stickmanXOffset < screenWidth)) {
        stickmanXOffset = 0;
        successful = false;
    }

    m_stickman->setXOffset(stickmanXOffset);

    float stickmanXVelocity = QString(reader.get("Stickman", "XVelocity").c_str()).toFloat(&parseOk);
    if (!parseOk || !(stickmanXVelocity >-51 && stickmanXVelocity < 51)) {
        stickmanXVelocity = 10.0;
        successful = false;
    }

    m_stickman->setXVelocity(stickmanXVelocity);

    int stickmanSpriteDuration = QString(reader.get("Stickman", "SpriteDuration").c_str()).toInt(&parseOk);
    if (!parseOk || stickmanSpriteDuration <= 0) {
        stickmanSpriteDuration = 300;
        successful = false;
    }

    m_stickman->setSpriteDuration(stickmanSpriteDuration);

    //set amount of jumps
    int maxJumps = QString(reader.get("Stickman", "Jumps").c_str()).toInt(&parseOk);
    if (!parseOk || maxJumps < 1) {
        maxJumps = 1;
    }
    m_stickman->setMaxJumps(maxJumps);


    //Set number of lives
    int lives = QString(reader.get("Stickman","Lives").c_str()).toInt(&parseOk);
    if (lives == 0) {
        m_stickman->setLives(3);
    } else {
        m_stickman->setLives(lives);
    }

    //Set number of levels
    int levels = QString(reader.get("Game","Levels").c_str()).toInt(&parseOk);
    if (levels == 0) {
        m_levelnum= 1;
    } else {
        m_levelnum = levels;
    }

    //Allocate memory for levels
    m_levels = new CompositeObstacle*[m_levelnum];

    //Goes through each level and checks if an obstacle is part of that level.
    for (int i = 0; i < m_levelnum; ++i) {
        m_levels[i] = new CompositeObstacle;


        //make the obstacles
        int max = screenWidth;
        m_xCollisionCheck = stickmanXOffset + stickmanXVelocity;
        int obstacles = 0;

        while(1) {
            obstacles++;
            char str[20];
            sprintf(str, "Obstacle%d",obstacles);
            int NextObstacle = QString(reader.get(str, "NextObstacle").c_str()).toInt(&parseOk);
           if(!parseOk){
                break;
            }

            int level = QString(reader.get(str,"Level").c_str()).toInt(&parseOk);
            if (level == 0) {
                level = 1;
            }



            //Check if this obstacle is in the current level
            if (i+1 == level) {
                int NextObstacle = QString(reader.get(str, "NextObstacle").c_str()).toInt(&parseOk);
                if(NextObstacle <0){
                    NextObstacle = 0;
                }
                int Height = QString(reader.get(str, "Height").c_str()).toInt(&parseOk);
                if(!parseOk || Height < 1){
                    Height = 50;
                }
                int Width = QString(reader.get(str, "Width").c_str()).toInt(&parseOk);
                if(!parseOk || Width < 1){
                    Width = 50;
                }
                int Radius = QString(reader.get(str, "Radius").c_str()).toInt(&parseOk);
                if(!parseOk || Radius < 1){
                    Radius = 10;
                }
                int StartY = QString(reader.get(str, "StartY").c_str()).toInt(&parseOk);
                if(!parseOk && StartY >0){
                    StartY = 0;
                }


                QColor Colour = QColor(QString(reader.get(str, "Colour").c_str()));
                if(!Colour.isValid()){
                    Colour = QColor(0,0,0);
                }
                std::string Shape = reader.get(str, "Shape");

                if(Shape == "triangle"){
                    m_levels[i]->add(new TriangleObstacle(max,StartY,stickmanXVelocity, Height,Width,Colour,screenWidth,screenHeight));
                    max += Width + NextObstacle;
                } else if(Shape == "circle"){
                    m_levels[i]->add(new CircleObstacle(max,StartY,stickmanXVelocity, Radius,Colour,screenWidth,screenHeight));
                    max += 2*Radius + NextObstacle;
                } else if (Shape == "rectangle"){
                    m_levels[i]->add(new RectangleObstacle(max,StartY,stickmanXVelocity, Height,Width,Colour,screenWidth,screenHeight));
                    max += Width + NextObstacle;
                } else if (Shape == "checkpoint"){
                    m_levels[i]->add(new Checkpoint(max,StartY,stickmanXVelocity, Height,Width,Colour,screenWidth,screenHeight, level));
                    max += Width + NextObstacle;
                } else if(Shape == "tiny") {
                    m_levels[i]->add(new TinyPowerup(max,StartY,stickmanXVelocity, Height,Width,Colour,screenWidth,screenHeight));
                    max += Width + NextObstacle;
                } else if(Shape == "normal") {
                    m_levels[i]->add(new NormalPowerup(max,StartY,stickmanXVelocity, Height,Width,Colour,screenWidth,screenHeight));
                    max += Width + NextObstacle;
                } else if(Shape == "large") {
                    m_levels[i]->add(new LargePowerup(max,StartY,stickmanXVelocity, Height,Width,Colour,screenWidth,screenHeight));
                    max += Width + NextObstacle;
                } else if(Shape == "giant") {
                    m_levels[i]->add(new GiantPowerup(max,StartY,stickmanXVelocity, Height,Width,Colour,screenWidth,screenHeight));
                    max += Width + NextObstacle;
                }
            }
        }
        if(max - screenWidth > screenWidth){
            max -= screenWidth;
        }
        //set max for obstacles(lets them know where to reset too)
        m_levels[i]->setMax(max);

    }
    return successful;
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_stickman(NULL),
    m_background(NULL),
    m_paused(false),
    m_pauseImage(":/resources/paused.png"),
    m_jumps(0),
    m_moveSpeed(3),
    m_score(0),
    m_currlevel(1),
    m_finished(false),
    m_won(false),
    m_sprites(NULL),
    m_explosioncounter(0),
    explosion(new QMovie(":/resources/explosion.gif")),
    label(this)
{
    ui->setupUi(this);

    // Read the configuration file to initialise the background and stickman.
    // Opens a message box if the configuration file couldn't be read.
    ConfigReader reader("game.config");
    if (!loadConfiguration(reader)) {
        QMessageBox messageBox;
        if (reader.fileRead())
            messageBox.warning(this, "Error", "Invalid values in configuration file. Using default settings.");
        else
            messageBox.warning(this, "Error", "Could not open configuration file. Using default settings.");
    }

    // Create a timer to update and redraw at regular intervals.
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    m_timer->start(m_timerMs);
    label.setMovie(explosion);

    mediator = new GameMediator(m_stickman,m_background,m_levels, m_xCollisionCheck, m_levelnum,m_pauseScreenEnabled);
}

Dialog::~Dialog()
{
    delete m_background;
    delete m_stickman;
    delete ui;
    delete m_timer;
    for(int i = 0; i < m_levelnum; ++i) {
        delete m_levels[i];
    }
    delete[] m_levels;
    delete mediator;
}

void Dialog::nextFrame()
{

    mediator->update();

    // Redraw the screen
    update();
}

//Method for rendering all elements
void Dialog::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    // Render game components
    m_background->render(painter, -m_stickman->getXPosition());
    m_stickman->render(painter);
    m_levels[m_stickman->getCurrLevel()-1]->render(painter,m_xCollisionCheck,m_invuln);



    char text[40];
    sprintf(text,"Score: %d, Lives: %d, Level: %d",mediator->getScore(),m_stickman->getLives(),m_stickman->getCurrLevel());
    painter.drawText(5,20, text);


    if (mediator->isPaused()) {
        // Render a pause message, with darkened background.
        QRectF windowRect(0, 0, painter.device()->width(), painter.device()->height());
        painter.fillRect(windowRect, QBrush(QColor(0, 0, 0, 128)));

        int x = painter.device()->width() / 2 - m_pauseImage.width() / 2;
        int y = painter.device()->height() / 2 - m_pauseImage.height() / 2;
        painter.drawImage(x, y, m_pauseImage);
    }

    if (mediator->isFinished()) {
        // Render a game over message.
        QFont font = QFont("Helvetica");
        font.setPointSize(font.pointSize() * 4);
        painter.setFont(font);


        QRectF windowRect(0, 0, painter.device()->width(), painter.device()->height());
        painter.fillRect(windowRect, QBrush(QColor(0, 0, 0, 128)));
        char finalscore[20];
        std::string finaltext;

        if (m_won) {
            finaltext = "Game complete!";
        } else {
            finaltext = "Game over";
        }

        sprintf(finalscore,"Final score: %d",mediator->getScore() );
        painter.drawText(250,100,finaltext.c_str());
        painter.drawText(200,200,finalscore);
    }


}

void Dialog::keyPressEvent(QKeyEvent *e)
{
    if (m_pauseScreenEnabled && e->key() == Qt::Key_Escape){
        m_paused = !m_paused;
    }
    if (!m_paused) {
        if(e->key() == Qt::Key_Space){
            m_stickman->setJumps(m_stickman->getJumps() + 1);
            if(m_stickman->getJumps() > m_stickman->getMaxJumps()){
                return;
            }
            m_stickman->setYVelocity(30);
        } else if(e->key() == Qt::Key_Right) {
            m_stickman->setXVelocity(m_stickman->getXVelocity() + m_moveSpeed);
            m_levels[m_stickman->getCurrLevel()-1]->setXVelocity(m_moveSpeed);
        } else if (e->key() == Qt::Key_Left) {
            m_stickman->setXVelocity(m_stickman->getXVelocity() - m_moveSpeed);
            m_levels[m_stickman->getCurrLevel()-1]->setXVelocity(-m_moveSpeed);
        }
    }
}


