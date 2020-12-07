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
    QColor fig[3];
    int m_i;
    int m_j;
    const int m_W = 20;
public:
    Figure();

    void setI(int i) {
        m_i = i;
    }

    void setJ(int i) {
        m_i = i;
    }

    int i() {
        return m_i;
    }

    int j() {
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
        for(int i = 0 ; i < 3; i++ ) {
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
        for (int i = 0; i < 3; i++) {
            painter.setBrush(fig[i]);
            painter.drawRect(0, 0 + i*m_W, m_W, m_W);
        }
    }
};

#endif // FIGURE_H
