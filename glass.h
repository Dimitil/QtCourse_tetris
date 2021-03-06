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
    const uint timeInterval = 300;
    Q_PROPERTY(uint rows READ rows WRITE setRows)
    Q_PROPERTY(uint columns READ columns WRITE setColumns)
    uint m_rows;
    uint m_columns;
    bool gameOn;
    int score;
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

    void addScore();

    void dropFigure();

    bool checkRowsAndRebuild();

    bool checkColumnsAndRebuild();

    void setRows(uint rows);

    void setColumns(uint columns);

    void clearGlass();

    QSize windowSize();

    void shiftLeft();

    void shiftRight();

    void acceptFigure(Figure* fig);

    bool checkGlass();

public slots:
    void slotGlassInit();

    void slotNewGame();

signals:
    void signalScore(int);

    void signalGlassInit();

    void signalNewNext(Figure* NewFig);

protected:
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void timerEvent(QTimerEvent *event) override;
};

#endif // GLASS_H
