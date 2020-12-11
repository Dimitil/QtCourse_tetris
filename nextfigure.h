#ifndef NEXTFIGURE_H
#define NEXTFIGURE_H

#include <QWidget>
#include "figure.h"
#include <QPainter>

class NextFigure : public QWidget
{
    Q_OBJECT
    Figure* fig;
    const uint  W = 20;

public:
    explicit NextFigure(QWidget *parent = nullptr);

public slots:
    void slotNewFig(Figure* NewFig);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // NEXTFIGURE_H
