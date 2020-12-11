#include "glass.h"
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include "nextfigure.h"
#include <QString>

const QColor glass::emptyCellQColor = Qt::gray;

glass::glass(QWidget *parent) : QWidget(parent), gameOn(false),
    score(0), cur(new Figure), next(new Figure)
{
    connect(this, &glass::signalGlassInit, this, &glass::slotGlassInit, Qt::QueuedConnection);
    signalGlassInit();
}

glass::~glass() {
    delete cur;
    delete next;
}

uint glass::rows() const
{
    return m_rows;
}

uint glass::columns() const
{
    return m_columns;
}

void glass::setRows(uint rows)
{
    m_rows = rows;
}

void glass::setColumns(uint columns)
{
    m_columns = columns;
}

void glass::slotGlassInit()
{
    glassArray.resize(m_rows);
    for (uint i = 0; i < m_rows; ++i) {
        glassArray[i].resize(m_columns);
        glassArray[i].fill(emptyCellQColor);
    }
    setFixedSize(windowSize());
}

void glass::clearGlass()
{
    for(int i = 0; i < glassArray.size(); i++) {
        glassArray[i].fill(emptyCellQColor);
    }
}

void glass::slotNewGame() {
    if(gameOn) {
        killTimer(idTimer);
    }
    gameOn = true;
    clearGlass();
    cur->MakeRandomColors();
    cur->setX(m_columns/2);
    cur->setY(0);
    next->MakeRandomColors();
    emit signalNewNext(next);
    repaint();
    setFocus();
    idTimer = startTimer(timeInterval);
}

QSize glass::windowSize(){
    return QSize(W*m_columns, W*m_rows);
}

void glass::shiftLeft() {
    if( (cur->x() != 0)
            && (glassArray[cur->y() + 2][cur->x()-1] == emptyCellQColor)) {
        cur->setX(cur->x() - 1);
    }
}

void glass::shiftRight() {
    if( (cur-> x() != (m_columns-1))
            && (glassArray[cur->y() + 2][cur->x() + 1] == emptyCellQColor)) {
        cur->setX(cur->x() + 1);
    }
}



void glass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::white);
    for (int i = 0; i < glassArray.size(); i++) {
        for (int j = 0; j < glassArray[i].size(); j++) {
            painter.setBrush(glassArray[i][j]);
            painter.drawRect(j*W, i*W, W, W);
        }
    }
    if (gameOn) {
       cur->paintFigure(painter);
    }
}

void glass::keyPressEvent(QKeyEvent *event)
{
    if(gameOn)
    {
        switch ( event->key()) {
            case Qt::Key_Left:
                shiftLeft();
                break;

            case Qt::Key_Right:
                shiftRight();
                break;

            case Qt::Key_Down:
                cur->rotateColors(Rotate::DOWN);
                break;

            case Qt::Key_Up:
                cur->rotateColors(Rotate::UP);
                break;

            case Qt::Key_Space:

                dropFigure();
                break;

            default:
                QWidget::keyPressEvent(event);
        }
    }
    else {
        QWidget::keyPressEvent(event);
    }
    repaint();
}

void glass::timerEvent(QTimerEvent *event) {
    uint futureJ = cur->y() + 1;
    if ( ( (futureJ + 2) < m_rows)
         && (glassArray[futureJ+2][cur->x()] == emptyCellQColor)) {
        cur -> setY(futureJ);
    }
    else {
        acceptFigure(cur);
        checkGlass();
        resetCurAndNext();
    }
    repaint();
}

void glass::resetCurAndNext() {
    std::swap(cur, next);
    next -> MakeRandomColors();
    next->setX(m_columns/2);
    next->setY(0);

    if (glassArray[2][m_columns/2] != emptyCellQColor) {
        killTimer(idTimer);
        QMessageBox::information(this, "Not bad!",
                                 "Game over!\nYou have "
                                 + QString::number(score) + " score!");
    }

    emit signalNewNext(next);
}

void glass::addScore() {
    score++;
    emit signalScore(score);
}

void glass::dropFigure() {
    int Y = cur->y() + 2;
    int X = cur->x() ;

    int newY = Y;
    for (int i = Y+1; i < glassArray.size(); i++) {
        if (glassArray[i][X] == emptyCellQColor) {
            newY++;
        }
        else {
            break;
        }
    }
    cur->setY((newY-2));
}

void glass::acceptFigure(Figure* fig) {
    uint column = fig -> x();
    uint row = fig -> y();

    for (uint i = 0; i < 3; i++) {
        glassArray[row+i][column] = fig->getColor(i);
    }
}

bool glass::checkRowsAndRebuild() {
    for (uint i = m_rows - 1; i > 2; i--) {
        for( uint j = 0; j < m_columns - 2; j++) { //чек строки
            if ( (glassArray[i][j] !=emptyCellQColor) &&
                 (glassArray[i][j] == glassArray[i][j+1]) &&
                 (glassArray[i][j] == glassArray[i][j+2]) )
            {
                addScore();
                for ( uint g = i; g > 0; g--) {
                    glassArray[g][j] = glassArray[g-1][j];
                    glassArray[g][j+1]   = glassArray[g-1][j+1];
                    glassArray[g][j+2] = glassArray[g-1][j+2];
                }
                return true;
            }
        }
    }
    return false;
}

bool glass::checkColumnsAndRebuild() {
    for (uint i = m_rows - 1; i > 2; i--) {
        for( uint j = 0; j < m_columns; j++) {
            if ( (glassArray[i][j] !=emptyCellQColor) &&        // чек столбцов
                 (glassArray[i][j] == glassArray[i-1][j]) &&
                 (glassArray[i][j] == glassArray[i-2][j]) )
            {
                addScore();
                for ( uint g = i; g > 5; g--) {
                    glassArray[g-2][j]   = glassArray[g-5][j];
                    glassArray[g-1][j] = glassArray[g-4][j];
                    glassArray[g][j] = glassArray[g-3][j];
                }
                return true;
            }
        }
    }
    return false;
}

bool glass::checkGlass() {
    if (checkRowsAndRebuild() ||
            checkColumnsAndRebuild()) {
        return checkGlass();
    }
    return false;
}
