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
    const uint timeInterval = 100;
    Q_PROPERTY(uint rows READ rows WRITE setRows)
    Q_PROPERTY(uint columns READ columns WRITE setColumns)
    uint m_rows = 30;
    uint m_columns = 10;
    bool gameOn;
    uint score;
    QVector<QVector<QColor>>glassArray;
    Figure *cur;
    Figure *next;
public:
    explicit glass(QWidget *parent = nullptr);
    ~glass();

    uint rows() const;

    uint columns() const;

public slots:
    void setRows(uint rows);

    void setColumns(uint columns);

    void slotGlassInit();

    void clearGlass();

    void slotNewGame() {
        gameOn = true;
        clearGlass();
        cur ->MakeRandomColors();
        cur->setI(0);
        cur->setJ(0);
        next->MakeRandomColors();
        //repaint example
        startTimer(timeInterval);
        repaint();
    }

    QSize windowSize();
signals:
    void signalGlassInit();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // GLASS_H
