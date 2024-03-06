#include <cmath>
#include <QPainter>
#include <QPoint>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QMediaPlayer>
#include "../object.h"
#include "../shoot.h"
#include "../enemy.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      engine_(38, 25),
      playerPixmapOrginal_(QString::fromUtf8(":/player.png")),
      backgroundOrginal_(QString::fromUtf8(":/background.png")),
      bulletOriginal_(QString::fromUtf8(":/bullet.png")),
      enemyOriginal_(QString::fromUtf8(":/enemy.png"))
{
    ui_->setupUi(this);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::update);
    timer_.start(/*msec=*/100);

    playlist_.addMedia(QUrl("qrc:/music.mp3"));
    playlist_.setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer(&playlist_);
    music->setPlaylist(&playlist_);
    music->play();

    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui_;
}


void MainWindow::redrawView()
{
    QPixmap newBackground(backgroundOrginal_);
    QPainter painter(&newBackground);
    if (!engine_.isPlayerAlieve())
    {
        painter.drawRect(newBackground.rect());
    }

    drawPlayer(painter);
    drawShoots(painter);
    drawEnemies(painter);

    ui_->background->setPixmap(newBackground);
}

void MainWindow::drawPlayer(QPainter& painter)
{
    if (engine_.isPlayerAlieve())
    {
        auto playerPixmap = getRotatedPlayerImage();
        auto [playerPositionTopLeft, playerPositionBottomRight] = calculatePlayerPosition();
        QRect playerPosition(playerPositionTopLeft, playerPositionBottomRight);
        painter.drawPixmap(playerPosition, playerPixmap);
    }
}


void MainWindow::drawShoots(QPainter& painter)
{
    for (const Shoot& shoot : engine_.shoots())
    {
        auto [shootPositionTopLeft, shootPositionBottomRight] = position2PairOfQPoints(shoot.position());
        auto cellSize = shootPositionBottomRight - shootPositionTopLeft;
        auto shootSize = cellSize / 3;
        shootPositionTopLeft += shootSize;
        shootPositionBottomRight -= shootSize;
        QRect shootPosition(shootPositionTopLeft, shootPositionBottomRight);
        painter.drawPixmap(shootPosition, bulletOriginal_);
    }
}

void MainWindow::drawEnemies(QPainter& painter)
{
    for (const auto& enemy : engine_.enemies())
    {
        auto [enemyPositionTopLeft, enemyPositionBottomRight] = position2PairOfQPoints(enemy->position());
        QRect enemyPosition(enemyPositionTopLeft, enemyPositionBottomRight);
        painter.drawPixmap(enemyPosition, enemyOriginal_);

        drawLifeBarAboveEnemy(painter, *enemy);
    }
}

void MainWindow::drawLifeBarAboveEnemy(QPainter& painter, const Enemy& enemy)
{
    auto [enemyPositionTopLeft, enemyPositionBottomRight] = position2PairOfQPoints(enemy.position());

    auto cellSize = enemyPositionBottomRight - enemyPositionTopLeft;
    auto lifeBarLength = abs(cellSize.x() * enemy.lifePercent() / 100);
    QPoint lifeBarPositionBottomRight(enemyPositionTopLeft.x()+lifeBarLength,
                enemyPositionTopLeft.y()+cellSize.y()/10);

    painter.setBrush(Qt::red);
    painter.drawRect(QRect{enemyPositionTopLeft, lifeBarPositionBottomRight});
}

std::pair<QPoint,QPoint> MainWindow::calculatePlayerPosition() const
{
    return position2PairOfQPoints(engine_.playerPosition());
}

QPoint MainWindow::position2QPoint(Position position) const
{
    // engineWidth - backgroundWidth
    // positionX - x
    auto newX = position.x_ * backgroundOrginal_.width() / engine_.stageWidthCells();
    auto newY = position.y_ * backgroundOrginal_.height() / engine_.stageHeightCells();

    return QPoint(newX, newY);
}
std::pair<QPoint,QPoint> MainWindow::position2PairOfQPoints(Position position) const
{
    auto positionFrom = position2QPoint(position);
    auto positionTo = position2QPoint(position.moveUpRight())-QPoint(1,1);
    return {positionFrom, positionTo};
}


void MainWindow::onPressUp()
{
    engine_.movePlayerDown();
}

void MainWindow::onPressDown()
{
    engine_.movePlayerUp();
}
void MainWindow::onPressLeft()
{
    engine_.movePlayerLeft();
}
void MainWindow::onPressRight()
{
    engine_.movePlayerRight();
}

void MainWindow::onPressShoot()
{
    engine_.playerShoots();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        qDebug() << "Esc pressed, goodbye";
        close();
        qApp->quit();
        return;
    }
    else if (event->key() == Qt::Key_Up)
    {
        onPressUp();
    }
    else if (event->key() == Qt::Key_Down)
    {
        onPressDown();
    }
    else if (event->key() == Qt::Key_Left)
    {
        onPressLeft();
    }
    else if (event->key() == Qt::Key_Right)
    {
        onPressRight();
    }
    else if (event->key() == Qt::Key_Space)
    {
        onPressShoot();
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::update()
{
    engine_.update();
    redrawView();
}

QPixmap MainWindow::getRotatedPlayerImage() const
{
    int rotationAngle = 0;
    switch(engine_.playerDirection())
    {
    case Direction::UP:
        rotationAngle = 90;
        break;
    case Direction::DOWN:
        rotationAngle = 270;
        break;
    case Direction::LEFT:
        rotationAngle = 180;
        break;
    case Direction::RIGHT:
        break;
    case Direction::UPPER_LEFT:
        break;
    case Direction::UPPER_RIGHT:
        break;
    case Direction::DOWNER_LEFT:
        break;
    case Direction::DOWNER_RIGHT:
        break;
    case Direction::CENTER:
        break;
    case Direction::INMOVABLE:
        break;
    case Direction::UNKNOWN:
        break;
    }
    QPixmap playerPixmapCopy(playerPixmapOrginal_);
    QMatrix rm;
    rm.rotate(rotationAngle);
    QPixmap playerPixmapRotated = playerPixmapCopy.transformed(rm);
    return playerPixmapRotated;
}
