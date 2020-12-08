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
public:
    const static uint rectCount = 3;

private:

    QColor fig[rectCount];
    uint m_i = 0;
    uint m_j = 0;
    const uint m_W = 20;

public:

    Figure();

    QColor getColor(uint index) const {
        return fig[index];
    }

    void setI(uint i) {
        m_i = i;
    }

    void setJ(uint i) {
        m_j = i;
    }

    uint i() const {
        return m_i;
    }

    uint j() const {
        return m_j;
    }

    void rotateColors(Rotate rot) {
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

    void MakeRandomColors() {
        for(uint i = 0 ; i < rectCount; i++ ) {
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

    void paintFigure(QPainter &painter) {
        for (uint i = 0; i < rectCount; i++) {
            painter.setBrush(fig[i]);
            painter.drawRect(this->i(), j() + i*m_W, m_W, m_W);
        }
    }


};

#endif // FIGURE_H
