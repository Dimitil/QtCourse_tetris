#include "figure.h"

Figure::Figure()
{

}

QColor Figure::getColor(uint index) const {
    return fig[index];
}

void Figure::setX(uint i) {
    m_x = i;
}

void Figure::setY(uint i) {
    m_y = i;
}

uint Figure::x() const {
    return m_x;
}

uint Figure::y() const {
    return m_y;
}

void Figure::rotateColors(Rotate rot) {
    if (rot == Rotate::UP) {
        QColor tmp = fig[0];
        fig[0] = fig[1];
        fig[1] = fig[2];
        fig[2] = tmp;
    }
    else if (rot == Rotate::DOWN) {
        QColor tmp = fig[2];
        fig[2] = fig[1];
        fig[1] = fig[0];
        fig[0] = tmp;
    }
}

void Figure::MakeRandomColors() {
    for(uint i = 0 ; i < 3; i++ ) {
        int tmp = rand() % 4;
        switch (tmp) {
        case 1:
            fig[i] = Qt::red;
            break;
        case 2:
            fig[i] = Qt::green;
            break;
        case 3:
            fig[i] = Qt::yellow;
            break;
        case 4:
            fig[i] = Qt::blue;
            break;
        default:
            fig[i] = Qt::black;
        }
    }
}

void Figure::paintFigure(QPainter &painter) {
    for (uint i = 0; i < 3; i++) {
        painter.setBrush(fig[i]);
        painter.drawRect(x() * W, y() * W + i*W, W, W);
    }
}
