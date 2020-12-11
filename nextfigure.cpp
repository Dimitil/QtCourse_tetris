#include "nextfigure.h"
#include <QDebug>
NextFigure::NextFigure(QWidget *parent) : QWidget(parent)
{

}

void NextFigure::slotNewFig(Figure *NewFig) {
    fig = NewFig;
    repaint();
}

void NextFigure::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    for (uint i = 0; i < 3; i++) {
        painter.setBrush(fig->getColor(i));
        painter.drawRect(rect().center().x() - W/2,
                         (rect().center().y() - 3 * W ) + i * W,
                         W, W);
    }
}
