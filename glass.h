#ifndef GLASS_H
#define GLASS_H

#include <QWidget>
#include <QVector>
#include "figure.h"

class glass : public QWidget
{
    Q_OBJECT
    const uint W = 20;
    static const QColor emptyCellQColor;
    const uint timeInterval = 50;
    Q_PROPERTY(uint rows READ rows WRITE setRows)
    Q_PROPERTY(uint columns READ columns WRITE setColumns)
    uint m_rows;
    uint m_columns;
    bool gameOn;
    uint score;
    QVector<QVector<QColor>>glassArray;
    Figure *cur;
    Figure *next;
    int idTimer;
public:
    explicit glass(QWidget *parent = nullptr);
    ~glass();

    uint rows() const;

    uint columns() const;

    void resetCurAndNext();

    void dropFigure() {
        int Y = cur->j() / W + 2;
        int X = cur->i() / W;

        int newY = Y;
        for (int i = Y+1; i < glassArray.size(); i++) {
            if (glassArray[i][X] == emptyCellQColor) {
                newY++;
            }
            else {
                break;
            }
        }
        cur->setJ((newY-2)*W);
    }

public slots:
    void setRows(uint rows);

    void setColumns(uint columns);

    void slotGlassInit();

    void clearGlass();

    void slotNewGame();

    QSize windowSize();

    void shiftLeft();

    void shiftRight();

    void acceptFigure(Figure* fig);

    void checkGlass() {
        //сделать
    }
signals:
    void signalGlassInit();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void timerEvent(QTimerEvent *event) override;
};

#endif // GLASS_H
