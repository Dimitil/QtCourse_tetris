#ifndef FIGURE_H
#define FIGURE_H

#include <QColor>
#include <QPainter>
#include <QDebug>

enum class Rotate{
    UP, DOWN
};

class Figure
{

private:

    QColor fig[3];
    uint m_x = 0;
    uint m_y = 0;
    const uint W = 20;

public:
    Figure();

    QColor getColor(uint index) const;

    void setX(uint i);

    void setY(uint i);

    uint x() const;

    uint y() const;

    void rotateColors(Rotate rot);

    void MakeRandomColors();

    void paintFigure(QPainter &painter);


};

#endif // FIGURE_H
