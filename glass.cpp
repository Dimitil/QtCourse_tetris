#include "glass.h"
#include <QPainter>
#include <QDebug>

glass::glass(QWidget *parent) : QWidget(parent)
{
    gameOn = false;
    score = 0;
    connect(this, &glass::signalGlassInit, this, &glass::slotGlassInit);
    signalGlassInit();
    setFixedSize(windowSize());

    cur = new Figure;
    cur->setI(0);
    cur->setJ(0);

    next = new Figure;
    next->setI(0);
    next->setJ(0);
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
}

void glass::clearGlass()
{

}

QSize glass::windowSize(){
    return QSize(W*m_columns, W*m_rows);
}

const QColor glass::emptyCellQColor = Qt::gray;


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
    //painter.setBrush(Qt::black);
    //painter.drawRect(0, 0, W, W);
    if (gameOn) {
       cur->paintFigure(painter);
    }
}
